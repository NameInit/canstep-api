#include "HidDevice.h"

HidDevice::HidDevice()
    : deviceHandle(nullptr), isConnected(false), isReading(false)
{
    hid_init();
}

HidDevice::~HidDevice()
{
    Disconnect();
    hid_exit();
}

bool HidDevice::Connect(uint16_t vendorId, uint16_t productId)
{
    Disconnect();
    deviceHandle = hid_open(vendorId, productId, nullptr);
    if (!deviceHandle)
    {
        std::cerr << "HID device not found: VID=" << std::hex << vendorId
                  << " PID=" << productId << std::dec << std::endl;
        return false;
    }

    isConnected = true;
    StartAsyncRead();
    return true;
}

void HidDevice::Disconnect()
{
    isReading = false;
    if (readThread.joinable())
        readThread.join();

    if (deviceHandle)
    {
        hid_close(deviceHandle);
        deviceHandle = nullptr;
    }

    isConnected = false;
}

bool HidDevice::SendData(const std::vector<uint8_t>& data)
{
    if (!deviceHandle || !isConnected)
        return false;

    // HID отчёты часто требуют ведущий 0x00 байт (Report ID)
    std::vector<uint8_t> report(ReportLength + 1, 0x00);
    size_t copyLen = std::min(data.size(), ReportLength);
    std::memcpy(&report[1], data.data(), copyLen);

    int res = hid_write(deviceHandle, report.data(), report.size());
    if (res < 0)
    {
        std::cerr << "HID write failed: " << hid_error(deviceHandle) << std::endl;
        return false;
    }

    return true;
}

void HidDevice::StartAsyncRead()
{
    isReading = true;
    readThread = std::thread(&HidDevice::ReadLoop, this);
}

void HidDevice::ReadLoop()
{
    std::vector<uint8_t> buffer(ReportLength + 1);

    while (isReading && deviceHandle)
    {
        int res = hid_read(deviceHandle, buffer.data(), buffer.size());
        if (res > 0)
        {
            ProcessReceivedData(buffer.data(), static_cast<size_t>(res));
        }
        else if (res < 0)
        {
            std::cerr << "HID read error: " << hid_error(deviceHandle) << std::endl;
            break;
        }
        else
        {
            // Timeout (0) — просто продолжаем
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void HidDevice::ProcessReceivedData(const uint8_t* buffer, size_t bytesRead)
{
    if (bytesRead <= 1)
        return;

    std::vector<uint8_t> data(buffer + 1, buffer + bytesRead);
    if (onDataReceived)
        onDataReceived(data);
}

void HidDevice::SetDataReceivedHandler(DataReceivedHandler handler)
{
    onDataReceived = std::move(handler);
}

// ────────────────────────────────────────────────
// ↓ Методы CAN/HID конвертации
// ────────────────────────────────────────────────

void HidDevice::ConvertUSBHIDToCAN(USBCANFrame* pTmpUSBCANFrame, USBHIDFrame* pTmpUSBHIDFrame)
{
    static_assert(sizeof(USBCANFrame) == 16, "USBCANFrame must be 16 bytes");
    std::memcpy(pTmpUSBCANFrame, pTmpUSBHIDFrame->eFrameData, sizeof(USBCANFrame));
}

void HidDevice::ConvertUSBCANToHID(USBCANFrame* pTmpUSBCANFrame, USBHIDFrame* pTmpUSBHIDFrame)
{
    static_assert(sizeof(USBCANFrame) == 16, "USBCANFrame must be 16 bytes");
    std::memcpy(pTmpUSBHIDFrame->eFrameData, pTmpUSBCANFrame, sizeof(USBCANFrame));
}

void HidDevice::SetEmergancy(uint8_t* devID, uint8_t* Emergancy, uint8_t* Reload)
{
    USBCANFrame newFrame = {};
    newFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
    newFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
    newFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_EMERGENCY_GLOBAL;
    newFrame.USB_CAN_Frame.eSize = 8;

    newFrame.USB_CAN_Frame.eFrameData[0] = *Emergancy;
    newFrame.USB_CAN_Frame.eFrameData[1] = *devID;
    newFrame.USB_CAN_Frame.eFrameData[2] = *Reload;
    for (int i = 3; i < 8; ++i) newFrame.USB_CAN_Frame.eFrameData[i] = 0;

    USBHIDFrame hidFrame = {};
    ConvertUSBCANToHID(&newFrame, &hidFrame);
    auto data = StructToVector(hidFrame);

    if (!SendData(data))
        std::cerr << "Error: SetEmergancy transmit failed" << std::endl;
}

// ────────────────────────────────────────────────
// ↓ Вспомогательные функции
// ────────────────────────────────────────────────


std::vector<uint8_t> HidDevice::StructToVector(const USBHIDFrame& frame)
{
    std::vector<uint8_t> data(sizeof(USBHIDFrame));
    std::memcpy(data.data(), &frame, sizeof(USBHIDFrame));
    return data;
}

void HidDevice::SetCanControlTensometerData(
    _CAN_Ask* pCan_Ask,
    _CAN_AskType* pAskType,
    _CAN_Ask_Channel* pNumChannel,
    _CMD_Mem* pCMDMess)
{
    pCan_Ask->AskModuleSystem = 10;
    pCan_Ask->AskModuleType = 51;
    pCan_Ask->AskChannelNumber = *pNumChannel;
    pCan_Ask->AskType = *pAskType;
    pCan_Ask->AskModuleAddress = 0;
    pCan_Ask->AskCMD1 = 0;
    pCan_Ask->AskCMDdata1 = 0;
    pCan_Ask->AskCMDdata2 = 0;
}
