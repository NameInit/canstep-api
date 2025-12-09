#pragma once

#ifndef __BOOTLOADER_H_
#define __BOOTLOADER_H_

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <cstring>
#include <thread>
#include <functional>
#include <memory>
#include "Typedefs.h"
#include "Defs.h"
#include "TypesBoot.h"
#include "HidDevice.h"
#include "TypesCANStep.h"
#include "CRC.h"

class Bootloader {
private:
    // Params
    uint8_t NumBoard;
    TypeCMDBootMod CMDBootMod;
    uint8_t u8NumData;
    uint8_t u8CRCData;
    uint8_t u8Errors;
    CANBootloaderSetData* pBootloaderSetData;
    TypeCMDBootMod CMDENDBootMod;
    uint8_t NumBoardIn;
    TypeCMDBootMod CMDBootModIn;
    uint8_t u8NumDataIn;
    uint8_t u8CRCDataIn;
    uint8_t u8ErrorsIn;
    CANBootloaderAnswer* pBootloaderAnswer;
    
    TypeBoard BoardType;
    TypeBoard InBoardType;

    bool bFlagCorrectDataSet;
    bool bErrorFlagCRCNorm;
    bool bErrorFlagCRC32;
    bool bErrorFlagLostCRC8;
    bool bErrorFlagLostCRC32;
    bool bErrorFlagTypeBoard;
    bool bBootloaderNeedOut;
    
    uint32_t u32SizeFirmware;
    uint32_t u32PositionFirmware;
    float fPositionFirmwareFloat;
    TypeBootState bootState;
    
    std::chrono::microseconds UploadTime;
    std::chrono::microseconds RealDelayTime;

    bool bNameFirmwarePresents;
    bool bVersionFirmwarePresents;
    bool bDateFirmwarePresents;
    std::vector<uint8_t> NameFirmwarePresents;
    std::vector<uint8_t> VersionFirmwarePresents;
    std::vector<uint8_t> DateFirmwarePresents;

    std::shared_ptr<HidDevice> pHidDevice;
    
    // Callback type
    using BootloaderCallback = std::function<void(uint8_t*, TypeCMDBootMod*, uint8_t*, uint8_t*, uint8_t*)>;
    BootloaderCallback callbackBootloaderAnswer;

public:
    Bootloader(uint8_t _NumBoard) {
        NumBoard = _NumBoard;
        CMDBootMod = eOFFCMDBootMod;
        u8NumData = 0;
        u8CRCData = 0;
        u8Errors = 0;
        pBootloaderSetData = new CANBootloaderSetData();
        CMDENDBootMod = eOFFCMDBootMod;
        NumBoardIn = 0;
        CMDBootModIn = eOFFCMDBootMod;
        u8NumDataIn = 0;
        u8CRCDataIn = 0;
        u8ErrorsIn = 0;
        pBootloaderAnswer = new CANBootloaderAnswer();
        
        bFlagCorrectDataSet = false;
        bErrorFlagCRCNorm = false;
        bErrorFlagCRC32 = false;
        bBootloaderNeedOut = false;
        
        u32SizeFirmware = 0;
        u32PositionFirmware = 0;
        fPositionFirmwareFloat = 0;
        bootState = eNoBoot;
        
        bNameFirmwarePresents = false;
        bVersionFirmwarePresents = false;
        bDateFirmwarePresents = false;
        
        UploadTime = std::chrono::microseconds(0);
        RealDelayTime = std::chrono::microseconds(0);
        BoardType = eNoTypeBoard;
    }

    ~Bootloader() {
        delete pBootloaderSetData;
        delete pBootloaderAnswer;
    }

    void SetFlagCorrectDataSet(bool bData) { 
        if (bData) {
            bFlagCorrectDataSet = true;
        }
    }
    
    bool GetFlagCorrectData(void) { return bFlagCorrectDataSet; }
    void ClrlagCorrectData(void) { bFlagCorrectDataSet = false; }
    
    void SetFlagsErrors(uint8_t bData) { 
        Byte8BitMask b8ErrorFlags = { 0 };
        b8ErrorFlags.raw = bData;
        bErrorFlagCRCNorm = b8ErrorFlags.b.B_CRC8_ERROR;
        bErrorFlagCRC32 = b8ErrorFlags.b.B_CRC32_ERROR;
        bErrorFlagLostCRC8 = b8ErrorFlags.b.B_LOST_BYTES_CRC8;
        bErrorFlagLostCRC32 = b8ErrorFlags.b.B_LOST_BYTES_CRC32;
        bErrorFlagTypeBoard = b8ErrorFlags.b.B_TYPE_BOARD_ERROR;
    }
    
    void CLRFlagsErrors(void) {
        bErrorFlagCRCNorm = false;
        bErrorFlagCRC32 = false;
        bErrorFlagLostCRC8 = false;
        bErrorFlagLostCRC32 = false;
        bErrorFlagTypeBoard = false;
    }
    
    bool GetFlagErrorCRC8(void) { return bErrorFlagCRCNorm; }
    bool GetFlagErrorCRC32(void) { return bErrorFlagCRC32; }
    bool GetFlagErrorLostCRC8(void) { return bErrorFlagLostCRC8; }
    bool GetFlagErrorLostCRC32(void) { return bErrorFlagLostCRC32; }
    bool GetFlagErrorTypeBoard(void) { return bErrorFlagTypeBoard; }
    
    void SetSizeFirmware(uint32_t u32Data) { u32SizeFirmware = u32Data; }
    uint32_t GetSizeFirmware(void) { return u32SizeFirmware; }
    
    void SetPositionFirmware(uint32_t u32Data) { u32PositionFirmware = u32Data; }
    uint32_t GetPositionFirmware(void) { return u32PositionFirmware; }
    
    float GetPositionFirmwareFloat(void) { 
        fPositionFirmwareFloat = (((float)u32PositionFirmware) * 100.0f) / ((float)u32SizeFirmware);
        if (fPositionFirmwareFloat < 0.01f) { fPositionFirmwareFloat = 0.0f; }
        return fPositionFirmwareFloat; 
    }
    
    TypeBootState GetBootState(void) { return bootState; }
    
    TypeBoard GetTypeBoard(void) { return BoardType; }
    void SetTypeBoard(TypeBoard _BoardType) { BoardType = _BoardType; }
    TypeBoard GetInTypeBoard(void) { return InBoardType; }
    void SetInTypeBoard(TypeBoard _InBoardType) { InBoardType = _InBoardType; }
    
    void SaveTypeBoard(void) {
        uint8_t u8TmpCRCBuff[8] = { 0 };
        pBootloaderSetData->NumBoard = NumBoard;
        pBootloaderSetData->TypeBootMod = eBoardType;
        pBootloaderSetData->NumData = 0;

        Byte32BitMask tmpCurrentOUT = { 0 };
        tmpCurrentOUT.raw = (uint32_t)BoardType;
        pBootloaderSetData->Data0 = tmpCurrentOUT.u8Mask[0];
        pBootloaderSetData->Data1 = tmpCurrentOUT.u8Mask[1];
        pBootloaderSetData->Data2 = tmpCurrentOUT.u8Mask[2];
        pBootloaderSetData->Data3 = tmpCurrentOUT.u8Mask[3];
        
        u8TmpCRCBuff[0] = pBootloaderSetData->NumBoard;
        u8TmpCRCBuff[1] = pBootloaderSetData->TypeBootMod;
        u8TmpCRCBuff[2] = pBootloaderSetData->NumData;
        u8TmpCRCBuff[3] = pBootloaderSetData->Data0;
        u8TmpCRCBuff[4] = pBootloaderSetData->Data1;
        u8TmpCRCBuff[5] = pBootloaderSetData->Data2;
        u8TmpCRCBuff[6] = pBootloaderSetData->Data3;
        
        pBootloaderSetData->CRCData = crc8(u8TmpCRCBuff, 7);
        SetCANBootloaderSetData(pBootloaderSetData);
    }
    
    void SetCallbackBootloaderAnswer(BootloaderCallback callback) {
        callbackBootloaderAnswer = callback;
    }
    
    void CallbackBootloaderAnswer(uint8_t* pNumBoard, TypeCMDBootMod* pCmd, 
                                  uint8_t* pNumData, uint8_t* pCRCData, uint8_t* pErrors) {
        if (callbackBootloaderAnswer) {
            callbackBootloaderAnswer(pNumBoard, pCmd, pNumData, pCRCData, pErrors);
        }
    }
    
    void SetBootloaderNeedOut(bool _bBootloaderNeedOut) {
        bBootloaderNeedOut = _bBootloaderNeedOut;
    }
    
    bool GetBootloaderNeedOut(void) {
        return bBootloaderNeedOut;
    }
    
    void SetHidDevice(std::shared_ptr<HidDevice> hidDevice) { pHidDevice = hidDevice; }
    
    void SetNumBoard(uint8_t _NumBoard) { NumBoard = _NumBoard; }
    uint8_t GetNumBoard(void) { return NumBoard; }
    
    void SetTypeCMDBootMod(TypeCMDBootMod BootMod) {
        CMDBootMod = BootMod; 
        CMDENDBootMod = (TypeCMDBootMod)((uint8_t)CMDBootMod + 1);
    }
    
    bool GetNameFirmwarePresents() { return bNameFirmwarePresents; }
    bool GetVersionFirmwarePresents() { return bVersionFirmwarePresents; }
    bool GetDateFirmwarePresents() { return bDateFirmwarePresents; }
    
    std::string GetNameFirmware() {
        return std::string(NameFirmwarePresents.begin(), NameFirmwarePresents.end());
    }
    
    std::string GetVersionFirmware() {
        return std::string(VersionFirmwarePresents.begin(), VersionFirmwarePresents.end());
    }
    
    std::string GetDateFirmware() {
        return std::string(DateFirmwarePresents.begin(), DateFirmwarePresents.end());
    }
    
    void ClearNameFirmware() {
        NameFirmwarePresents.clear();
        bNameFirmwarePresents = false;
    }
    
    void ClearVersionFirmware() {
        VersionFirmwarePresents.clear();
        bVersionFirmwarePresents = false;
    }
    
    void ClearDateFirmware() {
        DateFirmwarePresents.clear();
        bDateFirmwarePresents = false;
    }
    
    void BootloaderParsing(USBCANFrame* pUSBCANFrame) {
        USBCANFrame NewUSBCANFrame = { 0 };
        memcpy(&NewUSBCANFrame.b128USBCANFrame.u8Mask[0], pUSBCANFrame, USB_CAN_FRAME_Num);
        
        if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_BOOTLOADER_ANSWER_GLOBAL) {
            if (NumBoard != NewUSBCANFrame.USB_CAN_Frame.eFrameData[0]) {
                return;
            }

            NumBoardIn = NewUSBCANFrame.USB_CAN_Frame.eFrameData[0];
            CMDBootModIn = (TypeCMDBootMod)NewUSBCANFrame.USB_CAN_Frame.eFrameData[1];
            u8NumDataIn = NewUSBCANFrame.USB_CAN_Frame.eFrameData[2];
            u8CRCDataIn = NewUSBCANFrame.USB_CAN_Frame.eFrameData[3];
            u8ErrorsIn = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];

            bool bCorrectDataSet = false;
            if ((NumBoardIn == NumBoard) && (CMDBootModIn == CMDBootMod)) {
                bCorrectDataSet = true;
            }
            
            SetFlagCorrectDataSet(bCorrectDataSet);
            SetFlagsErrors(u8ErrorsIn);
            
            CallbackBootloaderAnswer(&NumBoardIn, &CMDBootModIn, &u8NumDataIn, 
                                    &u8CRCDataIn, &u8ErrorsIn);
        }
        
        if (NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID == CAN_ID_ANSWER) {
            switch (NewUSBCANFrame.USB_CAN_Frame.eFrameData[2]) {
                case OutNameFirmware:
                    ProcessFirmwareData(NewUSBCANFrame, NameFirmwarePresents, bNameFirmwarePresents);
                    break;
                case OutVersionFirmware:
                    ProcessFirmwareData(NewUSBCANFrame, VersionFirmwarePresents, bVersionFirmwarePresents);
                    break;
                case OutDateFirmware:
                    ProcessFirmwareData(NewUSBCANFrame, DateFirmwarePresents, bDateFirmwarePresents);
                    break;
                case OutBoardType: {
                    Byte32BitMask tmpCurrentOUT;
                    tmpCurrentOUT.u8Mask[0] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[4];
                    tmpCurrentOUT.u8Mask[1] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[5];
                    tmpCurrentOUT.u8Mask[2] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[6];
                    tmpCurrentOUT.u8Mask[3] = NewUSBCANFrame.USB_CAN_Frame.eFrameData[7];
                    SetInTypeBoard((TypeBoard)tmpCurrentOUT.raw);
                    break;
                }
                default:
                    break;
            }
        }
    }
    
    void SetBootloaderData(uint32_t pData) {
        uint8_t u8TmpCRCBuff[8] = {0};
        pBootloaderSetData->NumBoard = NumBoard;
        pBootloaderSetData->TypeBootMod = CMDBootMod;
        pBootloaderSetData->NumData = u8NumData;
        u8NumData++;
        
        Byte32BitMask tmpCurrentOUT = { 0 };
        tmpCurrentOUT.raw = pData;
        pBootloaderSetData->Data0 = tmpCurrentOUT.u8Mask[0];
        pBootloaderSetData->Data1 = tmpCurrentOUT.u8Mask[1];
        pBootloaderSetData->Data2 = tmpCurrentOUT.u8Mask[2];
        pBootloaderSetData->Data3 = tmpCurrentOUT.u8Mask[3];
        
        u8TmpCRCBuff[0] = pBootloaderSetData->NumBoard;
        u8TmpCRCBuff[1] = pBootloaderSetData->TypeBootMod;
        u8TmpCRCBuff[2] = pBootloaderSetData->NumData;
        u8TmpCRCBuff[3] = pBootloaderSetData->Data0;
        u8TmpCRCBuff[4] = pBootloaderSetData->Data1;
        u8TmpCRCBuff[5] = pBootloaderSetData->Data2;
        u8TmpCRCBuff[6] = pBootloaderSetData->Data3;
        
        pBootloaderSetData->CRCData = crc8(u8TmpCRCBuff, 7);
        SetCANBootloaderSetData(pBootloaderSetData);
    }
    
    void SetCANBootloaderSetData(CANBootloaderSetData* pBootloaderSetData) {
        if (!pHidDevice) return;
        
        USBCANFrame NewUSBCANFrame = { 0 };
        NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
        NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
        NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_BOOTLOADER_CMD_GLOBAL;
        NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = pBootloaderSetData->NumBoard;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = pBootloaderSetData->TypeBootMod;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = pBootloaderSetData->NumData;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = pBootloaderSetData->CRCData;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = pBootloaderSetData->Data0;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = pBootloaderSetData->Data1;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = pBootloaderSetData->Data2;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = pBootloaderSetData->Data3;

        USBHIDFrame TmpUSBHIDFrameTS = { 0 };
        pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
        
        std::vector<uint8_t> data(sizeof(USBHIDFrame));
        memcpy(data.data(), &TmpUSBHIDFrameTS, sizeof(USBHIDFrame));
        
        if (!pHidDevice->SendData(data)) {
            std::cerr << "Error when Firmware transmit" << std::endl;
        }
    }
    
    void ResetCANBootloader(void) {
        if (!pHidDevice) return;
        
        USBCANFrame NewUSBCANFrame = { 0 };
        NewUSBCANFrame.USB_CAN_Frame.eCMD = CAN_Transmit;
        NewUSBCANFrame.USB_CAN_Frame.eTypeID = CAN_11_Bit;
        NewUSBCANFrame.USB_CAN_Frame.eCAN_DEV_ID = CAN_ID_EMERGENCY_GLOBAL;
        NewUSBCANFrame.USB_CAN_Frame.eSize = 8;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[0] = 0;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[1] = NumBoard;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[2] = 0;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[3] = 1; // 1 - Reset bootloader
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[4] = 0;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[5] = 0;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[6] = 0;
        NewUSBCANFrame.USB_CAN_Frame.eFrameData[7] = 0;

        USBHIDFrame TmpUSBHIDFrameTS = { 0 };
        pHidDevice->ConvertUSBCANToHID(&NewUSBCANFrame, &TmpUSBHIDFrameTS);
        
        std::vector<uint8_t> data(sizeof(USBHIDFrame));
        memcpy(data.data(), &TmpUSBHIDFrameTS, sizeof(USBHIDFrame));
        
        if (!pHidDevice->SendData(data)) {
            std::cerr << "Error when Firmware transmit" << std::endl;
        }
    }
    
    void WaitForConfirmation(void) {
        uint16_t u16TimeoutExit = 1000;
        auto start = std::chrono::steady_clock::now();
        
        while ((!GetFlagCorrectData()) && (u16TimeoutExit)) {
            if (u16TimeoutExit) { u16TimeoutExit--; }
            std::this_thread::sleep_for(std::chrono::microseconds(250));
            
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            if (elapsed.count() > 1000) {
                break;
            }
        }
        
        if (!u16TimeoutExit) {
            std::cerr << "Firmware send timeout: " << u16TimeoutExit << "ms" << std::endl;
        }
    }
    
    void loadBootDataFromFile(const std::string& filename) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        bootState = eNoBoot;
        CLRFlagsErrors();
        
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return;
        }
        
        std::streamsize dataSize = file.tellg();
        file.seekg(0, std::ios::beg);
        
        int remainder = dataSize % PAGE_NUM_BYTES;
        int padBytes = (remainder == 0) ? 0 : (PAGE_NUM_BYTES - remainder);
        
        std::vector<uint8_t> fileData(dataSize + padBytes);
        file.read(reinterpret_cast<char*>(fileData.data()), dataSize);
        
        if (padBytes > 0) {
            std::fill(fileData.begin() + dataSize, fileData.end(), 0xFF);
        }
        
        dataSize = fileData.size();
        uint32_t u32TmpDataSize = dataSize;
        SetSizeFirmware(u32TmpDataSize);
        
        uint8_t u8TmpPageToCRC[PAGE_NUM_BYTES] = { 0 };
        uint32_t u32TmpNumCRCCalc = dataSize / PAGE_NUM_BYTES;
        uint32_t crc = 0;
        
        for (size_t i = 0; i < u32TmpNumCRCCalc; i++) {
            memcpy(u8TmpPageToCRC, fileData.data() + (i * PAGE_NUM_BYTES), PAGE_NUM_BYTES);
            crc = update_crc32(crc, u8TmpPageToCRC, PAGE_NUM_BYTES);
        }
        
        TypeCMDBootMod tmpCMDBootMod = eTestCMDBootMod;
        uint32_t u32ErrorTimeout = 100;
        size_t pos = 0;
        uint32_t u32TmpPos = pos;
        
        bootState = eBootLoading;
        auto startTime = std::chrono::steady_clock::now();
        auto lastTime = startTime;
        
        std::cout << "Start sending firmware, size " << dataSize 
                  << " (0x" << std::hex << dataSize << std::dec << ") Bytes" << std::endl;
        
        while (pos < dataSize) {
            uint8_t buffer[4] = { 0, 0, 0, 0 };
            size_t bytesToCopy = std::min((size_t)4, dataSize - pos);
            
            for (size_t i = 0; i < bytesToCopy; i++) {
                buffer[i] = fileData[pos + i];
            }
            
            pos += bytesToCopy;
            u32TmpPos = pos;
            SetPositionFirmware(u32TmpPos);
            
            uint32_t packedData = (buffer[0]) | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
            
            tmpCMDBootMod = eStartCANStepCMDBootMod;
            SetTypeCMDBootMod(tmpCMDBootMod);
            
            do {
                ClrlagCorrectData();
                SetBootloaderData(packedData);
                WaitForConfirmation();
                
                if (GetFlagErrorCRC8() || GetFlagErrorTypeBoard()) {
                    if (u32ErrorTimeout) { u32ErrorTimeout--; }
                }
                
                if (!u32ErrorTimeout) {
                    if (GetFlagErrorCRC8()) {
                        std::cerr << "Firmware CRC8 Error, Packet number: " << pos << std::endl;
                    } else {
                        std::cerr << "Firmware Type Board Error, Packet number: " << pos << std::endl;
                    }
                    SetBootloaderNeedOut(true);
                }
                
                auto now = std::chrono::steady_clock::now();
                UploadTime = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime);
                RealDelayTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime);
                lastTime = now;
                
            } while ((!GetFlagCorrectData()) || GetFlagErrorCRC8() || GetFlagErrorLostCRC8());
            
            std::cout << "Firmware send data number: " << pos 
                      << " (0x" << std::hex << pos << std::dec << ")" << std::endl;
            
            if (GetFlagErrorCRC8() || GetFlagErrorLostCRC8()) {
                pos -= bytesToCopy;
            }
        }
        
        u32ErrorTimeout = 10;
        tmpCMDBootMod = eEndCANStepCMDBootMod;
        SetTypeCMDBootMod(tmpCMDBootMod);
        
        do {
            ClrlagCorrectData();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            SetBootloaderData(crc);
            WaitForConfirmation();
            
            auto now = std::chrono::steady_clock::now();
            UploadTime = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime);
            
            if (u32ErrorTimeout) { 
                u32ErrorTimeout--; 
            } else { 
                SetBootloaderNeedOut(true); 
            }
        } while (!GetFlagCorrectData());
        
        auto stopTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
        
        if (GetFlagErrorLostCRC8()) {
            bootState = eBootLostCRC8;
            std::cerr << "Firmware Lost CRC8 Error, Elapsed: " << duration.count() << "ms" << std::endl;
        } else if (GetFlagErrorCRC32()) {
            bootState = eBootFault;
            std::cerr << "Firmware CRC32 Error, Elapsed: " << duration.count() << "ms" << std::endl;
        } else if (GetFlagErrorLostCRC32()) {
            bootState = eBootLostCRC32;
            std::cerr << "Firmware Lost Bytes CRC32 Error, Elapsed: " << duration.count() << "ms" << std::endl;
        } else if (GetFlagErrorTypeBoard()) {
            bootState = eBootTypeBoard;
            std::cerr << "Firmware Error Type Board, Elapsed: " << duration.count() << "ms" << std::endl;
        } else {
            bootState = eBootLoaded;
            std::cout << "Firmware sent successfully, Elapsed: " << duration.count() << "ms" << std::endl;
        }
    }

private:
    void ProcessFirmwareData(const USBCANFrame& frame, std::vector<uint8_t>& data, bool& presentFlag) {
        if (frame.USB_CAN_Frame.eFrameData[5] != 0) {
            if (!presentFlag) {
                data.push_back(frame.USB_CAN_Frame.eFrameData[5]);
            }
        } else {
            presentFlag = true;
        }
        
        if (frame.USB_CAN_Frame.eFrameData[6] != 0) {
            if (!presentFlag) {
                data.push_back(frame.USB_CAN_Frame.eFrameData[6]);
            }
        } else {
            presentFlag = true;
        }
        
        if (frame.USB_CAN_Frame.eFrameData[7] != 0) {
            if (!presentFlag) {
                data.push_back(frame.USB_CAN_Frame.eFrameData[7]);
            }
        } else {
            presentFlag = true;
        }
    }
};

#endif //__BOOTLOADER_H_