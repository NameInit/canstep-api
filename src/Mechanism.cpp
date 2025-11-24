#include "Mechanism.h"

void MechCallback(USBCANFrame* _USBCANFrame)
{
}

std::vector<uint8_t> Mechanism::StructToVector(const USBHIDFrame& frame)
{
    std::vector<uint8_t> data(sizeof(USBHIDFrame));
    memcpy(data.data(), &frame, sizeof(USBHIDFrame));
    return data;
}

Mechanism::~Mechanism() {
    pthread_mutex_destroy(&hMutex);
}

Mechanism::Mechanism(uint8_t _NumBoard, uint8_t _Group) {
    NumBoard = _NumBoard;
    Group = _Group;
    CANInputConfLoc = std::make_unique<CAN_input_conf>();
    CanInLoc = std::make_unique<CAN_input_contr>();
    
    pthread_mutex_init(&hMutex, nullptr);
    
    MaxAskSize = MAX_ASK_SIZE;
    AskNumBoard.resize(MaxAskSize, 0);
    AskNumEnum.resize(MaxAskSize, 0);
    NumAsks = 0;
    AskOneTaskNumBoard.resize(MaxAskSize, 0);
    AskOneTaskNumEnum.resize(MaxAskSize, 0);
    NumOneTaskAsks = 0;
    AutosenderDelay = 50;
    u16StageAsk = 0;
    Updater = eCANUpdaterOff;
    u32NumHIDOkParam = 0;
    u32NumHIDOkControl = 0;
    u32NumHIDOkAsk = 0;
}

void Mechanism::SetMaxAskSize(uint16_t _MaxAskSize) {
    MaxAskSize = _MaxAskSize;
}

void Mechanism::SetHidDevice(HidDevice* hidDevice) { pHidDevice = hidDevice; }

void Mechanism::SetUpdater(_CANUpdater _Updater) {
    Updater = _Updater;
}

uint8_t Mechanism::GetUpdater() {
    return static_cast<uint8_t>(Updater);
}

bool Mechanism::AddAsk(uint8_t _NumBoard, _AskEnum _Ask) {
    if (NumAsks >= MaxAskSize)
    {
        return false;
    }
    AskNumBoard[NumAsks] = _NumBoard;
    AskNumEnum[NumAsks] = (uint8_t)_Ask;
    NumAsks++;
    return true;
}

void Mechanism::SetAsk(_AskEnum _SetAsk)
{
    AddAsk(NumBoard, _SetAsk);
    setAutosender(254, 20, _SetAsk);
}

void Mechanism::ClrAsks()
{
    std::fill(AskNumBoard.begin(), AskNumBoard.end(), 0);
    std::fill(AskNumEnum.begin(), AskNumEnum.end(), 0);
    NumAsks = 0;
    setAutosender(253, 20, 0);
}

bool Mechanism::AddOneTaskAsk(uint8_t _NumBoard, _AskEnum _Ask) {
    if (NumOneTaskAsks >= MaxAskSize)
    {
        return false;
    }
    AskOneTaskNumBoard[NumOneTaskAsks] = _NumBoard;
    AskOneTaskNumEnum[NumOneTaskAsks] = (uint8_t)_Ask;
    NumOneTaskAsks++;
    return true;
}

bool Mechanism::SetOneTaskAsk(_AskEnum _SetAsk)
{
    if (NumOneTaskAsks >= MaxAskSize)
    {
        return false;
    }
    AskOneTaskNumBoard[NumOneTaskAsks] = NumBoard;
    AskOneTaskNumEnum[NumOneTaskAsks] = (uint8_t)_SetAsk;
    NumOneTaskAsks++;
    return true;
}

void Mechanism::setUpdateType(bool _UpdateType) {
    UpdateType = _UpdateType;
}

bool Mechanism::getUpdateType() {
    return UpdateType;
}

void Mechanism::UpdateCode()
{
    if (UpdateType)
    {
        AutosenderSetTest();
    }
    else
    {
        if (NumAsks)
        {
            AskCANStep(AskNumBoard[u16StageAsk], (_AskEnum)AskNumEnum[u16StageAsk]);
            if (u16StageAsk)
            {
                u16StageAsk--;
            }
            else
            {
                u16StageAsk = NumAsks - 1;
            }
        }
    }
    if (NumOneTaskAsks)
    {
        NumOneTaskAsks--;
        AskCANStep(AskOneTaskNumBoard[NumOneTaskAsks], (_AskEnum)AskOneTaskNumEnum[NumOneTaskAsks]);
        AskOneTaskNumBoard[NumOneTaskAsks] = 0;
        AskOneTaskNumEnum[NumOneTaskAsks] = 0;
    }
}

void Mechanism::AutosenderSetTest() {
    USBCANFrame NewUSBCANFrame = { 0 };
    NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
    NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
    NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_ASK;
    NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = this->getNumBoard();
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)AskTest;

    Byte64BitMask tmpCurrentOUT = { 0 };
    tmpCurrentOUT.raw = u32AutosenderTestNum;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = tmpCurrentOUT.u8Mask[0];
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = tmpCurrentOUT.u8Mask[1];
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = tmpCurrentOUT.u8Mask[2];
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = tmpCurrentOUT.u8Mask[3];
    if (u32AutosenderTestNum < 4294967295) { u32AutosenderTestNum++; }
    else { u32AutosenderTestNum = 0; }
    
    if (pthread_mutex_lock(&hMutex) == 0) {
        USBHIDFrame TmpUSBHIDFrameTS = { 0 };
        pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
        std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
        bool iRet = pHidDevice->SendData(data);
        if (iRet) {
            u32NumHIDOkAsk++;
        }
        pthread_mutex_unlock(&hMutex);
    } else {
        perror("pthread_mutex_lock failed");
    }
}

void Mechanism::addPossibleLostFrame() {
    if (Updater == eCANUpdaterCentral) {
        PossibleLostFrame = u32NumHIDOkAsk + u32NumHIDOkEmergancy + u32NumHIDOkParam + 
            u32NumHIDOkControl - u32NumHIDOkRead;
    }
    else
    {
        PossibleLostFrame = 0;
    }
    if (UpdateType) {
        PossibleLostFrame = 0;
    }
}

uint32_t Mechanism::getOkFrame() {
    if (UpdateType) {
        return u32NumHIDOkRead;
    }
    else {
        return u32NumHIDOkAsk;
    }
}

uint32_t Mechanism::getPossibleLostFrame() {
    return PossibleLostFrame;
}

void Mechanism::clrPossibleLostFrame() {
    PossibleLostFrame = 0;
    u32NumHIDOkAsk = 0;
    u32NumHIDOkEmergancy = 0;
    u32NumHIDOkParam = 0;
    u32NumHIDOkControl = 0;
    u32NumHIDOkRead = 0;
}

void Mechanism::SetCanInputControl(_CAN_input_control* pCan_In, uint8_t* pDevID, uint8_t* pGroup, uint8_t* pNumCMD,
    bool* pbRun, bool* pbStop, bool* pbDir, bool* pbMoveMode, bool* pbSteps, bool* pbVeloc, bool* pbAccel, bool* pbDecel, Byte32BitMask* u32Cmd)
{
    pCan_In->devID = *pDevID;
    pCan_In->group = *pGroup;
    pCan_In->numCommand = *pNumCMD;
    pCan_In->setups = 0;
    pCan_In->Data0 = 0;
    pCan_In->Data1 = 0;
    pCan_In->Data2 = 0;
    pCan_In->Data3 = 0;
    if (pCan_In->numCommand == curr_position)
    {
        pCan_In->setups = 0;
        pCan_In->Data0 = u32Cmd->u8Mask[3];
        pCan_In->Data1 = u32Cmd->u8Mask[2];
        pCan_In->Data2 = u32Cmd->u8Mask[1];
        pCan_In->Data3 = u32Cmd->u8Mask[0];
    }
    else if (pCan_In->numCommand == cantrol_command)
    {
        Byte8BitMask b8Tmp;
        b8Tmp.raw = 0;
        b8Tmp.b.b_0 = *pbRun;
        b8Tmp.b.b_1 = *pbStop;
        b8Tmp.b.b_2 = *pbDir;
        b8Tmp.b.b_3 = *pbMoveMode;
        b8Tmp.b.b_4 = *pbSteps;
        b8Tmp.b.b_5 = *pbVeloc;
        b8Tmp.b.b_6 = *pbAccel;
        b8Tmp.b.b_7 = *pbDecel;
        pCan_In->setups = b8Tmp.raw;
        if (*pbSteps)
        {
            pCan_In->Data0 = u32Cmd->u8Mask[3];
            pCan_In->Data1 = u32Cmd->u8Mask[2];
            pCan_In->Data2 = u32Cmd->u8Mask[1];
            pCan_In->Data3 = u32Cmd->u8Mask[0];
        }
        else if (*pbVeloc)
        {
            pCan_In->Data0 = u32Cmd->u8Mask[3];
            pCan_In->Data1 = u32Cmd->u8Mask[2];
            pCan_In->Data2 = u32Cmd->u8Mask[1];
            pCan_In->Data3 = u32Cmd->u8Mask[0];
        }
        else if (*pbAccel)
        {
            pCan_In->Data0 = u32Cmd->u8Mask[3];
            pCan_In->Data1 = u32Cmd->u8Mask[2];
            pCan_In->Data2 = u32Cmd->u8Mask[1];
            pCan_In->Data3 = u32Cmd->u8Mask[0];
        }
        else if (*pbDecel)
        {
            pCan_In->Data0 = u32Cmd->u8Mask[3];
            pCan_In->Data1 = u32Cmd->u8Mask[2];
            pCan_In->Data2 = u32Cmd->u8Mask[1];
            pCan_In->Data3 = u32Cmd->u8Mask[0];
        }
    }
    else
    {
        pCan_In->setups = 0;
    }
}

void Mechanism::SetCANControl(const CAN_input_contr& pCan_In)
{
    USBCANFrame NewUSBCANFrame = { 0 };
    NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
    NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
    NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_CENTRAL_CONTROL;
    NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pCan_In.devID;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)pCan_In.setups;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = pCan_In.group;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = pCan_In.numCommand;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pCan_In.Data0;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pCan_In.Data1;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pCan_In.Data2;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pCan_In.Data3;
    
    if (pthread_mutex_lock(&hMutex) == 0) {
        USBHIDFrame TmpUSBHIDFrameTS = { 0 };
        pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
        std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
        bool iRet = pHidDevice->SendData(data);
        if (iRet) {
            u32NumHIDOkControl++;
        }
        pthread_mutex_unlock(&hMutex);
    } else {
        perror("pthread_mutex_lock failed");
    }
}

void Mechanism::AskCANStep(uint8_t u8NumBoard, _AskEnum Ask)
{
    USBCANFrame NewUSBCANFrame = { 0 };
    NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
    NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
    NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_ASK;
    NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = u8NumBoard;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)Ask;

    if (pthread_mutex_lock(&hMutex) == 0) {
        USBHIDFrame TmpUSBHIDFrameTS = { 0 };
        pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
        std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
        bool iRet = pHidDevice->SendData(data);
        if (iRet) {
            u32NumHIDOkAsk++;
        }
        pthread_mutex_unlock(&hMutex);
    } else {
        perror("pthread_mutex_lock failed");
    }
}

void Mechanism::SetCANParam(const CAN_input_conf& pCANInputConf)
{
    USBCANFrame NewUSBCANFrame = { 0 };
    NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
    NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
    NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_CENTRAL_CONFIG;
    NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pCANInputConf.devID;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = (uint8_t)pCANInputConf.set_param;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = 0;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = 0;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pCANInputConf.Data0;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pCANInputConf.Data1;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pCANInputConf.Data2;
    NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pCANInputConf.Data3;

    if (pthread_mutex_lock(&hMutex) == 0) {
        USBHIDFrame TmpUSBHIDFrameTS = { 0 };
        pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
        std::vector<uint8_t> data = StructToVector(TmpUSBHIDFrameTS);
        bool iRet = pHidDevice->SendData(data);
        if (iRet) {
            u32NumHIDOkParam++;
        }
        pthread_mutex_unlock(&hMutex);
    } else {
        fprintf(stderr, "pthread_mutex_lock failed\n");
    }
}

void Mechanism::CAN_Parsing_Callback_ANSWER_CONTROL(uint8_t* pNumBoardParse, uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* pCmdInWork, uint8_t* ptmpErrors) {
    if (callbackAnswerControl) {
        callbackAnswerControl(pNumBoardParse, pRescCMD, pNumCMD, pStartMotor, pCmdInWork, ptmpErrors);
    }
};

void Mechanism::CAN_Parsing_Callback_ANSWER_CONFIG(uint8_t* pNumBoardParse) {
    if (callbackAnswerConfig) {
        callbackAnswerConfig(pNumBoardParse);
    }
};

void Mechanism::CAN_Parsing_Callback_ANSWER(uint8_t* pNumBoardParse, uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3) {
    if (callbackAnswer) {
        callbackAnswer(pNumBoardParse, pStatus, pNumAnswer, p8Data, p32Data, pfData, p8Data1, p8Data2, p8Data3);
    }
};

void Mechanism::SetCallbackAnswerControl(const CAN_Parsing_Callback_ANSWER_CONTROL_Delegate& callback) {
    callbackAnswerControl = callback;
}

void Mechanism::SetCallbackAnswerConfig(const CAN_Parsing_Callback_ANSWER_CONFIG_Delegate& callback) {
    callbackAnswerConfig = callback;
}

void Mechanism::SetCallbackAnswer(const CAN_Parsing_Callback_ANSWER_Delegate& callback) {
    callbackAnswer = callback;
}

uint32_t Mechanism::u32AutosenderTestNum = 0;
uint32_t Mechanism::u32AutosenderTestCheck = 0;
uint32_t Mechanism::u32AutosenderTestErrNum = 0;
bool Mechanism::bTestError = false;

void Mechanism::CAN_Parsing_Out(uint8_t* data)
{
    static Byte32BitMask tmpCurrentOUT;
    tmpCurrentOUT.raw = 0;
    int32_t tmpInt32 = 0;
    USBCANFrame NewUSBCANFrame = { 0 };
    memcpy(&NewUSBCANFrame.b128USBCANFrame.u8Mask[0], data, USB_CAN_FRAME_Num);
    uint8_t u8NumBoardParse = 0;
    uint8_t u8RescCMD = 0;
    uint8_t u8NumCMD = 0;
    uint8_t u8CmdInWork;
    uint8_t u8StartMotor = 0;
    Byte8BitMask u8tmpErrors = { 0 };
    u8NumBoardParse = NewUSBCANFrame.USB_CAN_Frame.eFrameData[1];

    if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER_CONTROL)
    {
        if (true)
        {
            u8RescCMD = NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
            u8NumCMD = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            u8CmdInWork = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            u8StartMotor = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            u8tmpErrors.raw = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER_CONTROL(&u8NumBoardParse, &u8RescCMD, &u8NumCMD, &u8StartMotor, &u8CmdInWork, &u8tmpErrors.raw);
        }
    }
    else if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER_CONFIG)
    {
        CAN_Parsing_Callback_ANSWER_CONFIG(&u8NumBoardParse);
    }
    else if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER)
    {
        Byte8BitMask b8TmpStatus = { 0 };
        Byte8BitMask b8TmpData = { 0 };

        b8TmpStatus.raw = NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
        uint8_t u8NumAnswer = NewUSBCANFrame.USB_CAN_Frame.eFrameData[2];

        Emergency = b8TmpStatus.b.b_0;
        InWork = b8TmpStatus.b.b_1;
        HomingA = b8TmpStatus.b.b_2;
        HomingB = b8TmpStatus.b.b_3;
        HomingC = b8TmpStatus.b.b_4;
        HomingD = b8TmpStatus.b.b_5;

        switch (NewUSBCANFrame.USB_CAN_Frame.eFrameData[2])
        {
        case OutPosition:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutLimitSwitchesCondition:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
            break;
        case OutStartPoint:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutEndPoint:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutRange:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutInputs:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
            break;
        case OutMotorTorque:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutMotorSpeed:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutAbsolutePositionRotorUint:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutAbsolutePositionRotorGrad:
            break;
        case OutAlarmCode:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutEncoder:
            break;
        case OutCurrSpeed:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        case OutCurrAccel:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        case OutCurrDecel:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        case OutCurrDir:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutCurrOutputs:
            Byte8BitMask b8OutputsState;
            b8OutputsState.raw = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingAPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingBPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingCPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingDPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutTimeAccel:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutAccel:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutDecel:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingADirection:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingBDirection:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingCDirection:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutHomingDDirection:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutmaxSpeed:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        case OutSavedSpeed:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        case OutDeltaPosition:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutSRVRDYPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutINPOSPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutFAULTPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutBRAKEPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutEnPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutAL_CLRPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutOBRAKEPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutOReservPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutDIRPolarity:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutGroup:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutOuts0_7:
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
            break;
        case OutInputs0_11:
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], 0, 0);
            break;
        case OutPullUpDwnInputs0_11:
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
            break;
        case OutEncoderActive:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutIholdIrun:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
            break;
        case OutTPWMTHRS:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutSteps:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutCOOLCONF:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutStallGuard2Result:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutEncoderPolarityDeltaTurn:
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[5], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[6], &NewUSBCANFrame.USB_CAN_Frame.eFrameData[7]);
            break;
        case OutGLOBAL_SCALER:
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, &NewUSBCANFrame.USB_CAN_Frame.eFrameData[4], 0, 0, 0, 0, 0);
            break;
        case OutEncoderRaw:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            tmpInt32 = (int32_t)tmpCurrentOUT.raw;
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, &tmpCurrentOUT.raw, 0, 0, 0, 0);
            break;
        case OutVActual:
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        case OutTest:
            tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
            tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
            tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
            tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];

            u32AutosenderTestNum = tmpCurrentOUT.raw;
            if (u32AutosenderTestNum != u32AutosenderTestCheck)
            {
                bTestError = true;
                u32AutosenderTestCheck = u32AutosenderTestNum;
            }
            else
            {
                bTestError = false;
            }
            u32AutosenderTestCheck++;
            if (bTestError)
            {
                u32AutosenderTestErrNum++;
                fprintf(stderr, "Read CAN-USB immediate error: %u (0x%X)\n", u32AutosenderTestErrNum, u32AutosenderTestErrNum);
            }
            else
            {
                if (!(tmpCurrentOUT.raw % 1000))
                {
                    fprintf(stdout, "Read CAN-USB Frames: %u (0x%X)\n", tmpCurrentOUT.raw, tmpCurrentOUT.raw);
                }
            }
            tmpCurrentOUT.raw = 0;
            CAN_Parsing_Callback_ANSWER(&u8NumBoardParse, &b8TmpStatus.raw, &u8NumAnswer, 0, 0, &tmpCurrentOUT.fraw, 0, 0, 0);
            break;
        default:
            break;
        }
    }
}

void Mechanism::saveParam(_MenuLVConfig Param, uint8_t data, uint32_t u32data, float fdata) {
    Byte32BitMask b32TmpParamSave = { 0 };
    switch (Param)
    {
    case mNumBoard:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mNumBoard;
        CANInputConfLoc->Data0 = data;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingAPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingAPolarity;
        CANInputConfLoc->Data0 = HomingAPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingBPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingBPolarity;
        CANInputConfLoc->Data0 = HomingBPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingCPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingCPolarity;
        CANInputConfLoc->Data0 = HomingCPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingDPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingDPolarity;
        CANInputConfLoc->Data0 = HomingDPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mStartPosition:
        b32TmpParamSave.raw = StartPosition;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mStartPosition;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mEndPosition:
        b32TmpParamSave.raw = EndPosition;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mEndPosition;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mAccelMem:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mAccelMem;
        CANInputConfLoc->Data0 = Accel;
        SetCANParam(*CANInputConfLoc);
        break;
    case mDecelMem:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mDecelMem;
        CANInputConfLoc->Data0 = Decel;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingADirection:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingADirection;
        CANInputConfLoc->Data0 = HomingADirection;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingBDirection:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingBDirection;
        CANInputConfLoc->Data0 = HomingBDirection;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingCDirection:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingCDirection;
        CANInputConfLoc->Data0 = HomingCDirection;
        SetCANParam(*CANInputConfLoc);
        break;
    case mHomingDDirection:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mHomingDDirection;
        CANInputConfLoc->Data0 = HomingDDirection;
        SetCANParam(*CANInputConfLoc);
        break;
    case mMaxSpeed:
        b32TmpParamSave.fraw = maxSpeed;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mMaxSpeed;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mCurrSpeed:
        b32TmpParamSave.fraw = CurrSpeed;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mCurrSpeed;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mDeltaPosition:
        b32TmpParamSave.raw = DeltaPosition;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mDeltaPosition;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mEnPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mEnPolarity;
        CANInputConfLoc->Data0 = EnPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mAL_CLRPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mAL_CLRPolarity;
        CANInputConfLoc->Data0 = AL_CLRPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mOBRAKEPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mOBRAKEPolarity;
        CANInputConfLoc->Data0 = OBRAKEPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mOReservPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mOReservPolarity;
        CANInputConfLoc->Data0 = OReservPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mSRVRDYPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSRVRDYPolarity;
        CANInputConfLoc->Data0 = SRVRDYPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mINPOSPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mINPOSPolarity;
        CANInputConfLoc->Data0 = INPOSPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mFAULTPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mFAULTPolarity;
        CANInputConfLoc->Data0 = FAULTPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mBRAKEPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mBRAKEPolarity;
        CANInputConfLoc->Data0 = BRAKEPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mDIRPolarity:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mDIRPolarity;
        CANInputConfLoc->Data0 = DIRPolarity;
        SetCANParam(*CANInputConfLoc);
        break;
    case mSaveGroup:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSaveGroup;
        CANInputConfLoc->Data0 = data;
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetMicrostepsToStep:
        CANInputConfLoc->devID = NumBoard;
        b32TmpParamSave.raw = u32data;
        CANInputConfLoc->set_param = mSetMicrostepsToStep;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetStepsToTurn:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetStepsToTurn;
        b32TmpParamSave.raw = u32data;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetInputsToVccGND:
        b32TmpParamSave.u16Mask[0] = NumInPullDown;
        b32TmpParamSave.u16Mask[1] = NumInPullUp;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetInputsToVccGND;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetEncoderActive:
        b32TmpParamSave.u8Mask[0] = data;
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetEncoderActive;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[3];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[0];
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetTMC_IHOLD:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetTMC_IHOLD;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[0];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data3 = 0;
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetTMC_TPWMTHRS:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetTMC_TPWMTHRS;
        CANInputConfLoc->Data0 = data;
        CANInputConfLoc->Data1 = 0;
        CANInputConfLoc->Data2 = 0;
        CANInputConfLoc->Data3 = 0;
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetTMC_COOLCONF:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetTMC_COOLCONF;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[0];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[3];
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetEncoderPolarityDeltaTurn:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetEncoderPolarityDeltaTurn;
        CANInputConfLoc->Data0 = b32TmpParamSave.u8Mask[0];
        CANInputConfLoc->Data1 = b32TmpParamSave.u8Mask[1];
        CANInputConfLoc->Data2 = b32TmpParamSave.u8Mask[2];
        CANInputConfLoc->Data3 = b32TmpParamSave.u8Mask[3];
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetGLOBAL_SCALER:
        CANInputConfLoc->devID = NumBoard;
        CANInputConfLoc->set_param = mSetGLOBAL_SCALER;
        CANInputConfLoc->Data0 = data;
        CANInputConfLoc->Data1 = 0;
        CANInputConfLoc->Data2 = 0;
        CANInputConfLoc->Data3 = 0;
        SetCANParam(*CANInputConfLoc);
        break;
    case mSetFreewheel:
        break;
    default:
        break;
    }
}

void Mechanism::loadControl(uint8_t* pRescCMD, uint8_t* pNumCMD, uint8_t* pStartMotor, uint8_t* ptmpErrors) {
    RescCMD = *pRescCMD;
    RescNumCMD = *pNumCMD;
    RescStartMotor = *pStartMotor;
    RescControlErrors = *ptmpErrors;
}
uint8_t Mechanism::GetRescCMD() { return RescCMD; }
uint8_t Mechanism::GetRescNumCMD() { return RescNumCMD; }
uint8_t Mechanism::GetRescStartMotor() { return RescStartMotor; }
uint8_t Mechanism::GetRescControlErrors() { return RescControlErrors; }
void Mechanism::loadParam() {
    bParamLoaded = true;
}
bool Mechanism::GetParamLoaded() { return bParamLoaded; }
void Mechanism::ClrParamLoaded() { bParamLoaded = false; }

void Mechanism::loadAnswer(uint8_t* pStatus, uint8_t* pNumAnswer, uint8_t* p8Data, uint32_t* p32Data, float* pfData, uint8_t* p8Data1, uint8_t* p8Data2, uint8_t* p8Data3) {
    Byte8BitMask b8TmpStatus = { 0 };
    b8TmpStatus.raw = *pStatus;
    Emergency = b8TmpStatus.b.b_0;
    InWork = b8TmpStatus.b.b_1;
    HomingA = b8TmpStatus.b.b_2;
    HomingB = b8TmpStatus.b.b_3;
    HomingC = b8TmpStatus.b.b_4;
    HomingD = b8TmpStatus.b.b_5;
    _OutTypeEnum mParam = (_OutTypeEnum)*pNumAnswer;

    Byte8BitMask b8tmpData = { 0 };

    switch (mParam)
    {
    case OutPosition:
        ReadPosition = *p32Data;
        break;
    case OutLimitSwitchesCondition:
        ReadHomeAState = *p8Data;
        ReadHomeBState = *p8Data1;
        ReadHomeCState = *p8Data2;
        ReadHomeDState = *p8Data3;
        break;
    case OutStartPoint:
        ReadStartPosition = *p32Data;
        break;
    case OutEndPoint:
        ReadEndPosition = *p32Data;
        break;
    case OutRange:
        ReadRange = *p32Data;
        break;
    case OutInputs:
        SRVRDY = *p8Data;
        INPOS = *p8Data1;
        FAULT = *p8Data2;
        BRAKE = *p8Data3;
        break;
    case OutMotorTorque:
        ServoMotorTorque = *p32Data;
        break;
    case OutMotorSpeed:
        ServoMotorSpeed = *p32Data;
        break;
    case OutAbsolutePositionRotorUint:
        ServoAbsolutePositionRotorUint = *p32Data;
        break;
    case OutAlarmCode:
        ServoAlarmCode = *p32Data;
        break;
    case OutCurrSpeed:
        ReadSpeed = *pfData;
        break;
    case OutCurrAccel:
        ReadCurrAccel = *pfData;
        break;
    case OutCurrDecel:
        ReadCurrDecel = *pfData;
        break;
    case OutCurrDir:
        ReadOut_Dir = *p8Data;
        break;
    case OutCurrOutputs:
        b8tmpData.raw = *p8Data;
        ReadOut_EN = b8tmpData.b.B_POS_EN;
        ReadOut_AL_CLR = b8tmpData.b.B_POS_AL_CLR;
        ReadOut_OBRAKE = b8tmpData.b.B_POS_OBRAKE;
        ReadOut_ORESERV = b8tmpData.b.B_POS_ORESERV;
        break;
    case OutHomingAPolarity:
        ReadHomingAPolarity = *p8Data;
        break;
    case OutHomingBPolarity:
        ReadHomingBPolarity = *p8Data;
        break;
    case OutHomingCPolarity:
        ReadHomingCPolarity = *p8Data;
        break;
    case OutHomingDPolarity:
        ReadHomingDPolarity = *p8Data;
        break;
    case OutAccel:
        ReadAccel = *p8Data;
        break;
    case OutDecel:
        ReadDecel = *p8Data;
        break;
    case OutHomingADirection:
        ReadHomingADirection = *p8Data;
        break;
    case OutHomingBDirection:
        ReadHomingBDirection = *p8Data;
        break;
    case OutHomingCDirection:
        ReadHomingCDirection = *p8Data;
        break;
    case OutHomingDDirection:
        ReadHomingDDirection = *p8Data;
        break;
    case OutmaxSpeed:
        ReadmaxSpeed = *pfData;
        break;
    case OutSavedSpeed:
        ReadCurrSpeed = *pfData;
        break;
    case OutDeltaPosition:
        ReadDeltaPosition = *p32Data;
        break;
    case OutSRVRDYPolarity:
        ReadSRVRDYPolarity = *p8Data;
        break;
    case OutINPOSPolarity:
        ReadINPOSPolarity = *p8Data;
        break;
    case OutFAULTPolarity:
        ReadFAULTPolarity = *p8Data;
        break;
    case OutBRAKEPolarity:
        ReadBRAKEPolarity = *p8Data;
        break;
    case OutEnPolarity:
        ReadEnPolarity = *p8Data;
        break;
    case OutAL_CLRPolarity:
        ReadAL_CLRPolarity = *p8Data;
        break;
    case OutOBRAKEPolarity:
        ReadOBRAKEPolarity = *p8Data;
        break;
    case OutOReservPolarity:
        ReadOReservPolarity = *p8Data;
        break;
    case OutDIRPolarity:
        ReadDIRPolarity = *p8Data;
        break;
    case OutGroup:
        ReadGroup = *p8Data;
        break;
    case OutOuts0_7:
    case OutInputs0_11:
    case OutPullUpDwnInputs0_11:
    case OutEncoderActive:
    case OutIholdIrun:
    case OutTPWMTHRS:
    case OutSteps:
    case OutCOOLCONF:
    case OutStallGuard2Result:
    case OutEncoderPolarityDeltaTurn:
    case OutGLOBAL_SCALER:
    case OutEncoderRaw:
    case OutVActual:
    case OutTest:
        break;
    default:
        break;
    }
};

void Mechanism::changeNumBoard(uint8_t _NumBoard) {
    NumBoard = _NumBoard;
}
void Mechanism::setNumBoard(uint8_t _NumBoard) {
    saveParam(mNumBoard, _NumBoard, 0, 0);
    NumBoard = _NumBoard;
};

uint8_t Mechanism::getNumBoard() {
    return NumBoard;
};
void Mechanism::changeGroup(uint8_t _Group) {
    Group = _Group;
}
void Mechanism::setGroup(uint8_t _Group) {
    Group = _Group;
    saveParam(mSaveGroup, Group, 0, 0);
};

uint8_t Mechanism::getGroup(bool R_Wr) {
    if (R_Wr) return ReadGroup;
    else return Group;
};
void Mechanism::setHomingAPolarity(uint8_t _HomingAPolarity) {
    HomingAPolarity = _HomingAPolarity;
    saveParam(mHomingAPolarity, HomingAPolarity, 0, 0);
};
uint8_t Mechanism::getHomingAPolarity(bool R_Wr) {
    if (R_Wr) return ReadHomingAPolarity;
    else return HomingAPolarity;
};
void Mechanism::setHomingBPolarity(uint8_t _HomingBPolarity) {
    HomingBPolarity = _HomingBPolarity;
    saveParam(mHomingBPolarity, HomingBPolarity, 0, 0);
};
uint8_t Mechanism::getHomingBPolarity(bool R_Wr) {
    if (R_Wr) return ReadHomingBPolarity;
    else return HomingBPolarity;
};
void Mechanism::setHomingCPolarity(uint8_t _HomingCPolarity) {
    HomingCPolarity = _HomingCPolarity;
    saveParam(mHomingCPolarity, HomingCPolarity, 0, 0);
};
uint8_t Mechanism::getHomingCPolarity(bool R_Wr) {
    if (R_Wr) return ReadHomingCPolarity;
    else return HomingCPolarity;
};
void Mechanism::setHomingDPolarity(uint8_t _HomingDPolarity) {
    HomingDPolarity = _HomingDPolarity;
    saveParam(mHomingDPolarity, HomingDPolarity, 0, 0);
};
uint8_t Mechanism::getHomingDPolarity(bool R_Wr) {
    if (R_Wr) return ReadHomingDPolarity;
    else return HomingDPolarity;
};
void Mechanism::setStartPosition(uint32_t _StartPosition) {
    StartPosition = _StartPosition;
    saveParam(mStartPosition, 0, StartPosition, 0);
};
uint32_t Mechanism::getStartPosition(bool R_Wr) {
    if (R_Wr) return ReadStartPosition;
    else return StartPosition;
};
void Mechanism::setEndPosition(uint32_t _EndPosition) {
    EndPosition = _EndPosition;
    saveParam(mEndPosition, 0, EndPosition, 0);
};
uint32_t Mechanism::getEndPosition(bool R_Wr) {
    if (R_Wr) return ReadEndPosition;
    else return EndPosition;
};
uint32_t Mechanism::getRange(bool R_Wr) {
    if (R_Wr) return ReadRange;
    else return Range;
};
uint32_t Mechanism::getServoMotorTorque() {
    return ServoMotorTorque;
}
uint32_t Mechanism::getServoMotorSpeed() {
    return ServoMotorSpeed;
}
uint32_t Mechanism::getServoAbsolutePositionRotorUint() {
    return ServoAbsolutePositionRotorUint;
}
uint32_t Mechanism::getServoAlarmCode() {
    return ServoAlarmCode;
}
void Mechanism::setAccel(uint8_t _Accel) {
    Accel = _Accel;
    saveParam(mAccelMem, Accel, 0, 0);
};
uint8_t Mechanism::getAccel(bool R_Wr) {
    if (R_Wr) return ReadAccel;
    else return Accel;
};
void Mechanism::setDecel(uint8_t _Decel) {
    Decel = _Decel;
    saveParam(mDecelMem, Decel, 0, 0);
};
uint8_t Mechanism::getDecel(bool R_Wr) {
    if (R_Wr) return ReadDecel;
    else return Decel;
};
void Mechanism::setHomingADirection(uint8_t _HomingADirection) {
    HomingADirection = _HomingADirection;
    saveParam(mHomingADirection, HomingADirection, 0, 0);
};
uint8_t Mechanism::getHomingADirection(bool R_Wr) {
    if (R_Wr) return ReadHomingADirection;
    else return HomingADirection;
};
void Mechanism::setHomingBDirection(uint8_t _HomingBDirection) {
    HomingBDirection = _HomingBDirection;
    saveParam(mHomingBDirection, HomingBDirection, 0, 0);
};
uint8_t Mechanism::getHomingBDirection(bool R_Wr) {
    if (R_Wr) return ReadHomingBDirection;
    else return HomingBDirection;
};
void Mechanism::setHomingCDirection(uint8_t _HomingCDirection) {
    HomingCDirection = _HomingCDirection;
    saveParam(mHomingCDirection, HomingCDirection, 0, 0);
};
uint8_t Mechanism::getHomingCDirection(bool R_Wr) {
    if (R_Wr) return ReadHomingCDirection;
    else return HomingCDirection;
};
void Mechanism::setHomingDDirection(uint8_t _HomingDDirection) {
    HomingDDirection = _HomingDDirection;
    saveParam(mHomingDDirection, HomingDDirection, 0, 0);
};
uint8_t Mechanism::getHomingDDirection(bool R_Wr) {
    if (R_Wr) return ReadHomingDDirection;
    else return HomingDDirection;
};
void Mechanism::setmaxSpeed(float _maxSpeed) {
    maxSpeed = _maxSpeed;
    saveParam(mMaxSpeed, 0, 0, maxSpeed);
};
float Mechanism::getmaxSpeed(bool R_Wr) {
    if (R_Wr) return ReadmaxSpeed;
    else return maxSpeed;
};
void Mechanism::setCurrSpeed(float _CurrSpeed) {
    CurrSpeed = _CurrSpeed;
    saveParam(mCurrSpeed, 0, 0, CurrSpeed);
};
float Mechanism::getCurrSpeed(bool R_Wr) {
    if (R_Wr) return ReadCurrSpeed;
    else return CurrSpeed;
};
void Mechanism::setDeltaPosition(uint32_t _DeltaPosition) {
    DeltaPosition = _DeltaPosition;
    saveParam(mDeltaPosition, 0, DeltaPosition, 0);
};
uint32_t Mechanism::getDeltaPosition(bool R_Wr) {
    if (R_Wr) return ReadDeltaPosition;
    else return DeltaPosition;
};
void Mechanism::setSRVRDYPolarity(uint8_t _SRVRDYPolarity) {
    SRVRDYPolarity = _SRVRDYPolarity;
    saveParam(mSRVRDYPolarity, SRVRDYPolarity, 0, 0);
};
uint8_t Mechanism::getSRVRDYPolarity(bool R_Wr) {
    if (R_Wr) return ReadSRVRDYPolarity;
    else return SRVRDYPolarity;
};
void Mechanism::setINPOSPolarity(uint8_t _INPOSPolarity) {
    INPOSPolarity = _INPOSPolarity;
    saveParam(mINPOSPolarity, INPOSPolarity, 0, 0);
};
uint8_t Mechanism::getINPOSPolarity(bool R_Wr) {
    if (R_Wr) return ReadINPOSPolarity;
    else return INPOSPolarity;
};
void Mechanism::setFAULTPolarity(uint8_t _FAULTPolarity) {
    FAULTPolarity = _FAULTPolarity;
    saveParam(mFAULTPolarity, FAULTPolarity, 0, 0);
};
uint8_t Mechanism::getFAULTPolarity(bool R_Wr) {
    if (R_Wr) return ReadFAULTPolarity;
    else return FAULTPolarity;
};
void Mechanism::setBRAKEPolarity(uint8_t _BRAKEPolarity) {
    BRAKEPolarity = _BRAKEPolarity;
    saveParam(mBRAKEPolarity, BRAKEPolarity, 0, 0);
};
uint8_t Mechanism::getBRAKEPolarity(bool R_Wr) {
    if (R_Wr) return ReadBRAKEPolarity;
    else return BRAKEPolarity;
};
void Mechanism::setEnPolarity(uint8_t _EnPolarity) {
    EnPolarity = _EnPolarity;
    saveParam(mEnPolarity, EnPolarity, 0, 0);
};
uint8_t Mechanism::getEnPolarity(bool R_Wr) {
    if (R_Wr) return ReadEnPolarity;
    else return EnPolarity;
};
void Mechanism::setAL_CLRPolarity(uint8_t _AL_CLRPolarity) {
    AL_CLRPolarity = _AL_CLRPolarity;
    saveParam(mAL_CLRPolarity, AL_CLRPolarity, 0, 0);
};
uint8_t Mechanism::getAL_CLRPolarity(bool R_Wr) {
    if (R_Wr) return ReadAL_CLRPolarity;
    else return AL_CLRPolarity;
};
void Mechanism::setOBRAKEPolarity(uint8_t _OBRAKEPolarity) {
    OBRAKEPolarity = _OBRAKEPolarity;
    saveParam(mOBRAKEPolarity, OBRAKEPolarity, 0, 0);
};
uint8_t Mechanism::getOBRAKEPolarity(bool R_Wr) {
    if (R_Wr) return ReadOBRAKEPolarity;
    else return OBRAKEPolarity;
};
void Mechanism::setOReservPolarity(uint8_t _OReservPolarity) {
    OReservPolarity = _OReservPolarity;
    saveParam(mOReservPolarity, OReservPolarity, 0, 0);
};
uint8_t Mechanism::getOReservPolarity(bool R_Wr) {
    if (R_Wr) return ReadOReservPolarity;
    else return OReservPolarity;
};
void Mechanism::setDIRPolarity(uint8_t _DIRPolarity) {
    DIRPolarity = _DIRPolarity;
    saveParam(mDIRPolarity, DIRPolarity, 0, 0);
};
uint8_t Mechanism::getDIRPolarity(bool R_Wr) {
    if (R_Wr) return ReadDIRPolarity;
    else return DIRPolarity;
};
void Mechanism::runForward() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_0 = true;
    b8Tmp.b.b_2 = true;
    CanInLoc->setups = b8Tmp.raw;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::runBackward() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_0 = true;
    b8Tmp.b.b_2 = false;
    CanInLoc->setups = b8Tmp.raw;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::stop() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_1 = true;
    CanInLoc->setups = b8Tmp.raw;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::HomingZero() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = homing_zero;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::HomingMax() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = homing_max;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::ResetDRVError() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = reset_drv_err;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::BrakeOn() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = brake_on;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::BrakeOff() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = brake_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::Debug_on() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = debug_on;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::Reset() {
    uint8_t u8Emergancy = 0;
    uint8_t u8Reload = 1;
    uint8_t u8NB = NumBoard;
    pHidDevice->SetEmergancy(&u8NB, &u8Emergancy, &u8Reload);
}
void Mechanism::Mosfet_On() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = tmc_mosfet_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 1;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::Mosfet_Off() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = tmc_mosfet_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
uint32_t Mechanism::GetPosition(bool R_Wr)
{
    if (R_Wr) return ReadPosition;
    else return u32SetPosition;
}
void Mechanism::SetPosition(uint32_t _u32Position)
{
    u32SetPosition = _u32Position;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = curr_position;
    CanInLoc->setups = 0;
    Byte32BitMask u32Cmd;
    u32Cmd.raw = u32SetPosition;
    CanInLoc->Data0 = u32Cmd.u8Mask[3];
    CanInLoc->Data1 = u32Cmd.u8Mask[2];
    CanInLoc->Data2 = u32Cmd.u8Mask[1];
    CanInLoc->Data3 = u32Cmd.u8Mask[0];
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::RezervOn() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = rez_on;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::RezervOff() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = rez_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::AlarmResetOn() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = al_clr_on;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::AlarmResetOff() {
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = al_clr_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}
void Mechanism::setSteps(uint32_t _Steps) {
    Steps = _Steps;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_4 = true;
    CanInLoc->setups = b8Tmp.raw;
    Byte32BitMask u32Cmd;
    u32Cmd.raw = Steps;
    CanInLoc->Data0 = u32Cmd.u8Mask[3];
    CanInLoc->Data1 = u32Cmd.u8Mask[2];
    CanInLoc->Data2 = u32Cmd.u8Mask[1];
    CanInLoc->Data3 = u32Cmd.u8Mask[0];
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
uint32_t Mechanism::getSteps() { return Steps; };
void Mechanism::setSpeed(float _Speed) {
    Speed = _Speed;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_5 = true;
    CanInLoc->setups = b8Tmp.raw;
    Byte32BitMask u32Cmd;
    u32Cmd.fraw = Speed;
    CanInLoc->Data0 = u32Cmd.u8Mask[3];
    CanInLoc->Data1 = u32Cmd.u8Mask[2];
    CanInLoc->Data2 = u32Cmd.u8Mask[1];
    CanInLoc->Data3 = u32Cmd.u8Mask[0];
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
float Mechanism::getSpeed(bool R_Wr) {
    if (R_Wr) return ReadSpeed;
    else return Speed;
};
void Mechanism::setCurrAccel(uint8_t _CurrAccel) {
    CurrAccel = _CurrAccel;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_6 = true;
    CanInLoc->setups = b8Tmp.raw;
    Byte32BitMask u32Cmd;
    u32Cmd.fraw = CurrAccel;
    CanInLoc->Data0 = u32Cmd.u8Mask[3];
    CanInLoc->Data1 = u32Cmd.u8Mask[2];
    CanInLoc->Data2 = u32Cmd.u8Mask[1];
    CanInLoc->Data3 = u32Cmd.u8Mask[0];
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
uint8_t Mechanism::getCurrAccel(bool R_Wr) {
    if (R_Wr) return ReadCurrAccel;
    else return CurrAccel;
};
void Mechanism::setCurrDecel(uint8_t _CurrDecel) {
    CurrDecel = _CurrDecel;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = cantrol_command;
    Byte8BitMask b8Tmp;
    b8Tmp.raw = 0;
    b8Tmp.b.b_7 = true;
    CanInLoc->setups = b8Tmp.raw;
    Byte32BitMask u32Cmd;
    u32Cmd.fraw = CurrDecel;
    CanInLoc->Data0 = u32Cmd.u8Mask[3];
    CanInLoc->Data1 = u32Cmd.u8Mask[2];
    CanInLoc->Data2 = u32Cmd.u8Mask[1];
    CanInLoc->Data3 = u32Cmd.u8Mask[0];
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
uint8_t Mechanism::getCurrDecel(bool R_Wr) {
    if (R_Wr) return ReadCurrDecel;
    else return CurrDecel;
};

bool Mechanism::getEmergency() { return Emergency; };
bool Mechanism::getInWork() { return InWork; };
bool Mechanism::getHomingA(bool Slow_Fast) {
    if (Slow_Fast) return ReadHomeAState;
    else return HomingA;
};
bool Mechanism::getHomingB(bool Slow_Fast) {
    if (Slow_Fast) return ReadHomeBState;
    else return HomingB;
};
bool Mechanism::getHomingC(bool Slow_Fast) {
    if (Slow_Fast) return ReadHomeCState;
    else return HomingC;
};
bool Mechanism::getHomingD(bool Slow_Fast) {
    if (Slow_Fast) return ReadHomeDState;
    else return HomingD;
};
bool Mechanism::getSRVRDY() { return SRVRDY; };
bool Mechanism::getINPOS() { return INPOS; };
bool Mechanism::getFAULT() { return FAULT; };
bool Mechanism::getBRAKE() { return BRAKE; };
bool Mechanism::getOutEn(bool R_Wr) {
    if (R_Wr) return ReadOut_EN;
    else return OutEn;
};
bool Mechanism::getOutDIR(bool R_Wr) {
    if (R_Wr) return ReadOut_Dir;
    else return OutDIR;
};
void Mechanism::setOutAL_CLR(bool _OutAL_CLR) {
    OutAL_CLR = _OutAL_CLR;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    if (OutAL_CLR) CanInLoc->numCommand = al_clr_on;
    else CanInLoc->numCommand = al_clr_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
bool Mechanism::getOutAL_CLR(bool R_Wr) {
    if (R_Wr) return ReadOut_AL_CLR;
    else return OutAL_CLR;
};
void Mechanism::setOutOutBRAKE(bool _OutBRAKE) {
    OutBRAKE = _OutBRAKE;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    if (OutBRAKE) CanInLoc->numCommand = brake_on;
    else CanInLoc->numCommand = brake_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
bool Mechanism::getOutBRAKE(bool R_Wr) {
    if (R_Wr) return ReadOut_OBRAKE;
    else return OutBRAKE;
};
void Mechanism::setOutReserv(bool _OutReserv) {
    OutReserv = _OutReserv;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    if (OutReserv) CanInLoc->numCommand = rez_on;
    else CanInLoc->numCommand = rez_off;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = 0;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
bool Mechanism::getOutReserv(bool R_Wr) {
    if (R_Wr) return ReadOut_ORESERV;
    else return OutReserv;
};
void Mechanism::setMicroSteps(uint32_t _MicrostepsToStep) {
    MicrostepsToStep = _MicrostepsToStep;
    saveParam(mSetMicrostepsToStep, 0, MicrostepsToStep, 0);
}
uint32_t Mechanism::getMicroSteps(bool R_Wr) {
    if (R_Wr) return ReadMicrostepsToStep;
    else return MicrostepsToStep;
}
void Mechanism::setStepsToTurn(uint32_t _StepsToTurn) {
    StepsToTurn = _StepsToTurn;
    saveParam(mSetStepsToTurn, 0, StepsToTurn, 0);
}
uint32_t Mechanism::getStepsToTurn(bool R_Wr) {
    if (R_Wr) return ReadStepsToTurn;
    else return StepsToTurn;
}
uint8_t Mechanism::setOutToZState(uint8_t _NumOut, bool _TrueFalse) {
    Byte8BitMask tmpNumOutZState = { 0 };
    tmpNumOutZState.raw = NumOutZState;
    if (_NumOut < 8) {
        if (_TrueFalse) tmpNumOutZState.raw |= (1 << _NumOut);
        else tmpNumOutZState.raw &= ~(1 << _NumOut);
    }
    NumOutZState = tmpNumOutZState.raw;
    return NumOutZState;
}
uint8_t Mechanism::setOutToHiState(uint8_t _NumOut, bool _TrueFalse) {
    Byte8BitMask tmpNumOutHiState = { 0 };
    tmpNumOutHiState.raw = NumOutHiState;
    if (_NumOut < 8) {
        if (_TrueFalse) tmpNumOutHiState.raw |= (1 << _NumOut);
        else tmpNumOutHiState.raw &= ~(1 << _NumOut);
    }
    NumOutHiState = tmpNumOutHiState.raw;
    return NumOutHiState;
}
uint8_t Mechanism::setOutToLoState(uint8_t _NumOut, bool _TrueFalse) {
    Byte8BitMask tmpNumOutLoState = { 0 };
    tmpNumOutLoState.raw = NumOutLoState;
    if (_NumOut < 8) {
        if (_TrueFalse) tmpNumOutLoState.raw |= (1 << _NumOut);
        else tmpNumOutLoState.raw &= ~(1 << _NumOut);
    }
    NumOutLoState = tmpNumOutLoState.raw;
    return NumOutZState;
}
void Mechanism::setOutToZ(uint8_t _NumOut) {
    setOutToZState(_NumOut, true);
    setOutToHiState(_NumOut, false);
    setOutToLoState(_NumOut, false);
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = out_to_z_state;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = _NumOut;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::setOutToHi(uint8_t _NumOut) {
    setOutToZState(_NumOut, false);
    setOutToHiState(_NumOut, true);
    setOutToLoState(_NumOut, false);
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = out_to_vcc;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = _NumOut;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::setOutToLo(uint8_t _NumOut) {
    setOutToZState(_NumOut, false);
    setOutToHiState(_NumOut, true);
    setOutToLoState(_NumOut, false);
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = out_to_gnd;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = _NumOut;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
_NumOutState Mechanism::getOutState(uint8_t _NumOut, bool R_Wr) {
    Byte8BitMask tmpNumOutZState = { 0 };
    if (R_Wr) { tmpNumOutZState.raw = ReadNumOutZState; }
    else { tmpNumOutZState.raw = NumOutZState; }
    Byte8BitMask tmpNumOutHiState = { 0 };
    if (R_Wr) { tmpNumOutHiState.raw = ReadNumOutHiState; }
    else { tmpNumOutHiState.raw = NumOutHiState; }
    Byte8BitMask tmpNumOutLoState = { 0 };
    if (R_Wr) { tmpNumOutLoState.raw = ReadNumOutLoState; }
    else { tmpNumOutLoState.raw = NumOutHiState; }
    
    if (_NumOut < 8) {
        if ((tmpNumOutZState.raw >> _NumOut) & 1) return eNumOutZState;
        if ((tmpNumOutHiState.raw >> _NumOut) & 1) return eNumOutHiState;
        if ((tmpNumOutLoState.raw >> _NumOut) & 1) return eNumOutLoState;
    }
    return eNumOutUnknownState;
}

uint16_t Mechanism::setInToNoPullupDown(uint16_t _NumIn, bool _TrueFalse) {
    Byte16BitMask tmpNumInNoPullupDown = { 0 };
    tmpNumInNoPullupDown.raw = NumInNoPullupDown;
    if (_NumIn < 12) {
        if (_TrueFalse) tmpNumInNoPullupDown.raw |= (1 << _NumIn);
        else tmpNumInNoPullupDown.raw &= ~(1 << _NumIn);
    }
    NumInNoPullupDown = tmpNumInNoPullupDown.raw;
    return NumInNoPullupDown;
}

uint16_t Mechanism::setInPullUp(uint16_t _NumIn, bool _TrueFalse) {
    Byte16BitMask tmpNumInPullUp = { 0 };
    tmpNumInPullUp.raw = NumInPullUp;
    if (_NumIn < 12) {
        if (_TrueFalse) tmpNumInPullUp.raw |= (1 << _NumIn);
        else tmpNumInPullUp.raw &= ~(1 << _NumIn);
    }
    NumInPullUp = tmpNumInPullUp.raw;
    return NumInPullUp;
}

uint16_t Mechanism::setInPullDown(uint16_t _NumIn, bool _TrueFalse) {
    Byte16BitMask tmpNumInPullDown = { 0 };
    tmpNumInPullDown.raw = NumInPullDown;
    if (_NumIn < 12) {
        if (_TrueFalse) tmpNumInPullDown.raw |= (1 << _NumIn);
        else tmpNumInPullDown.raw &= ~(1 << _NumIn);
    }
    NumInPullDown = tmpNumInPullDown.raw;
    return NumInPullDown;
}

void Mechanism::setInToZ(uint16_t _NumIn) {
    setInToNoPullupDown(_NumIn, true);
    setInPullUp(_NumIn, false);
    setInPullDown(_NumIn, false);
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = input_to_z_state;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = _NumIn;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::setInPullUp(uint16_t _NumIn) {
    setInToNoPullupDown(_NumIn, true);
    setInPullUp(_NumIn, false);
    setInPullDown(_NumIn, false);
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = input_to_vcc;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = _NumIn;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};
void Mechanism::setInPullDown(uint16_t _NumIn) {
    setInToNoPullupDown(_NumIn, true);
    setInPullUp(_NumIn, false);
    setInPullDown(_NumIn, false);
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = input_to_gnd;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = _NumIn;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = 0;
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
};

_NumInPullUpDown Mechanism::getInPullupDown(uint16_t _NumIn, bool R_Wr) {
    Byte16BitMask tmpNumInNoPullupDown = { 0 };
    if (R_Wr) { tmpNumInNoPullupDown.raw = ReadNumInNoPullupDown; }
    else { tmpNumInNoPullupDown.raw = NumInNoPullupDown; }
    Byte16BitMask tmpNumInPullUp = { 0 };
    if (R_Wr) { tmpNumInPullUp.raw = ReadNumInPullUp; }
    else { tmpNumInPullUp.raw = NumInPullUp; }
    Byte16BitMask tmpNumInPullDown = { 0 };
    if (R_Wr) { tmpNumInPullDown.raw = ReadNumInPullDown; }
    else { tmpNumInPullDown.raw = NumInPullDown; }
    
    if (_NumIn < 12) {
        if ((tmpNumInNoPullupDown.raw >> _NumIn) & 1) return eNumInNoPullupDown;
        if ((tmpNumInPullUp.raw >> _NumIn) & 1) return eNumInPullUp;
        if ((tmpNumInPullDown.raw >> _NumIn) & 1) return eNumInPullDown;
    }
    return eNumInUnknownPullupDown;
}
void Mechanism::SetIHOLD(uint8_t _IHOLD, uint8_t _IRUN, uint8_t _IHOLDDELAY) {
    TMC_IHOLD = _IHOLD;
    TMC_IRUN = _IRUN;
    IHOLDDELAY = _IHOLDDELAY;
    Byte32BitMask b32TmpParamSave = { 0 };
    b32TmpParamSave.u8Mask[0] = TMC_IHOLD;
    b32TmpParamSave.u8Mask[1] = TMC_IRUN;
    b32TmpParamSave.u8Mask[2] = IHOLDDELAY;
    saveParam(mSetTMC_IHOLD, 0, StepsToTurn, 0);
}
uint8_t Mechanism::GetIHOLD(bool R_Wr) {
    if (R_Wr) return ReadTMC_IHOLD;
    else return TMC_IHOLD;
}
uint8_t Mechanism::GetIRUN(bool R_Wr) {
    if (R_Wr) return ReadTMC_IRUN;
    else return TMC_IRUN;
}
uint8_t Mechanism::GetIHOLDDELAY(bool R_Wr) {
    if (R_Wr) return ReadIHOLDDELAY;
    else return IHOLDDELAY;
}
void Mechanism::setTPWMTHRS(uint8_t _TPWMTHRS) {
    TMC_TPWMTHRS = _TPWMTHRS;
    saveParam(mSetTMC_TPWMTHRS, TMC_TPWMTHRS, 0, 0);
}
uint8_t Mechanism::getTPWMTHRS(bool R_Wr) {
    if (R_Wr) return ReadTMC_TPWMTHRS;
    else return TMC_TPWMTHRS;
}
void Mechanism::SaveInPullUps() {
    saveParam(mSetInputsToVccGND, 0, 0, 0);
}
void Mechanism::setEncoderActive(bool _set) {
    saveParam(mSetEncoderActive, _set, 0, 0);
}
void Mechanism::setCOOLCONF(uint8_t Seup, uint8_t Sedn, bool Seimin, bool SGFilter, uint8_t Semin, uint8_t Semax, uint8_t SGThreshold) {
    Byte32BitMask b32TmpParamSave = { 0 };
    Byte8BitMask b8TmpData = { 0 };
    b8TmpData.raw = Seup;
    b32TmpParamSave.b.b_0 = b8TmpData.b.b_0;
    b32TmpParamSave.b.b_1 = b8TmpData.b.b_1;
    b8TmpData.raw = Sedn;
    b32TmpParamSave.b.b_2 = b8TmpData.b.b_0;
    b32TmpParamSave.b.b_3 = b8TmpData.b.b_1;
    b32TmpParamSave.b.b_4 = Seimin;
    b32TmpParamSave.b.b_5 = SGFilter;
    b32TmpParamSave.u8Mask[1] = Semin;
    b32TmpParamSave.u8Mask[2] = Semax;
    b32TmpParamSave.u8Mask[3] = SGThreshold;
    saveParam(mSetTMC_COOLCONF, 0, b32TmpParamSave.raw, 0);
}
void Mechanism::setEncoderConfig(uint8_t EncoderPolarity, uint8_t EncoderDelta, uint16_t EncoderToTurnData) {
    Byte32BitMask b32TmpParamSave = { 0 };
    Byte16BitMask b16TmpData = { 0 };
    b32TmpParamSave.u8Mask[0] = EncoderPolarity;
    b32TmpParamSave.u8Mask[1] = EncoderDelta;
    b16TmpData.raw = EncoderToTurnData;
    b32TmpParamSave.u8Mask[2] = b16TmpData.u8Mask[0];
    b32TmpParamSave.u8Mask[3] = b16TmpData.u8Mask[1];
    saveParam(mSetEncoderPolarityDeltaTurn, 0, b32TmpParamSave.raw, 0);
}
void Mechanism::setGLOBAL_SCALER(uint8_t _GLOBAL_SCALER) {
    saveParam(mSetGLOBAL_SCALER, _GLOBAL_SCALER, 0, 0);
}
void Mechanism::setControlPositioning_Velocity(bool Pos_Vel) {
    if (Pos_Vel)
    {
        CanInLoc->devID = NumBoard;
        CanInLoc->group = Group;
        CanInLoc->numCommand = tmc_positioning_velocity;
        CanInLoc->setups = 0;
        CanInLoc->Data0 = 0;
        CanInLoc->Data1 = 0;
        CanInLoc->Data2 = 0;
        CanInLoc->Data3 = 0;
        uint8_t u8tmpCommand = CanInLoc->setups;
        uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
        setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
        SetCANControl(*CanInLoc);
    }
    else
    {
        CanInLoc->devID = NumBoard;
        CanInLoc->group = Group;
        CanInLoc->numCommand = tmc_positioning_velocity;
        CanInLoc->setups = 0;
        CanInLoc->Data0 = 1;
        CanInLoc->Data1 = 0;
        CanInLoc->Data2 = 0;
        CanInLoc->Data3 = 0;
        uint8_t u8tmpCommand = CanInLoc->setups;
        uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
        setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
        SetCANControl(*CanInLoc);
    }
}
uint8_t Mechanism::getAutosenderDelay() {
    return AutosenderDelay;
}
void Mechanism::setAutosender(uint8_t _AutosenderType, uint8_t _AutosenderDelay, uint8_t _AutosenderNum) {
    AutosenderType = _AutosenderType;
    AutosenderDelay = _AutosenderDelay;
    CanInLoc->devID = NumBoard;
    CanInLoc->group = Group;
    CanInLoc->numCommand = autosender;
    CanInLoc->setups = 0;
    CanInLoc->Data0 = AutosenderType;
    CanInLoc->Data1 = 0;
    CanInLoc->Data2 = 0;
    CanInLoc->Data3 = AutosenderDelay;
    if (_AutosenderType == 254)
    {
        CanInLoc->Data1 = _AutosenderNum;
    }
    uint8_t u8tmpCommand = CanInLoc->setups;
    uint8_t u8tmpNum_command = (uint8_t)CanInLoc->numCommand;
    setCmdToMechanism(&u8tmpCommand, &u8tmpNum_command);
    SetCANControl(*CanInLoc);
}

void Mechanism::setCmdToMechanism(uint8_t* Cmd, uint8_t* NumCmd) {
    if (*NumCmd)
    {
        NumCmdTransmitted = *NumCmd;
        CmdTransmitted = 0;
    }
    else
    {
        NumCmdTransmitted = 0;
        CmdTransmitted = *Cmd;
    }
}
void Mechanism::setCmdFromMechanism(uint8_t* Cmd, uint8_t* NumCmd, uint8_t* CmdInWork) {
    if (*NumCmd)
    {
        NumCmdRescived = *NumCmd;
        CmdRescived = 0;
    }
    else
    {
        NumCmdRescived = 0;
        CmdRescived = *Cmd;
    }
    u8CmdInWork = *CmdInWork;
}
bool Mechanism::getCmdInWork() {
    if (NumCmdTransmitted)
    {
        if (NumCmdRescived == NumCmdTransmitted)
        {
            if (u8CmdInWork)
            {
                return true;
            }
        }
    }
    else
    {
        if (CmdTransmitted == CmdRescived)
        {
            if (u8CmdInWork)
            {
                return true;
            }
        }
    }
    return false;
}