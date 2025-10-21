#pragma once

#include <hidapi/hidapi.h>
#include <thread>
#include <atomic>
#include <vector>
#include <functional>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "Defs.h"
#include "TypesTenso.h"

#define USBD_BUF_SIZE 64U

// Класс для работы с HID-устройством
class HidDevice final
{
public:
    using DataReceivedHandler = std::function<void(const std::vector<uint8_t>&)>;

    HidDevice();
    ~HidDevice();

    bool Connect(uint16_t vendorId, uint16_t productId);
    void Disconnect();
    bool SendData(const std::vector<uint8_t>& data);

    bool IsConnected() const { return isConnected.load(); }

    // Установка колбэка для обработки входящих данных
    void SetDataReceivedHandler(DataReceivedHandler handler);

    // Методы, аналогичные USB-CAN
    void SetEmergancy(uint8_t* devID, uint8_t* Emergancy, uint8_t* Reload);

    void ConvertUSBHIDToCAN(USBCANFrame* pTmpUSBCANFrame, USBHIDFrame* pTmpUSBHIDFrame);
    void ConvertUSBCANToHID(USBCANFrame* pTmpUSBCANFrame, USBHIDFrame* pTmpUSBHIDFrame);

private:
    void StartAsyncRead();
    void ReadLoop();
    void ProcessReceivedData(const uint8_t* buffer, size_t bytesRead);

    // Вспомогательные функции
    std::vector<uint8_t> StructToVector(const USBHIDFrame& frame);
    void SetCanControlTensometerData(_CAN_Ask* pCan_Ask,
                                     _CAN_AskType* pAskType,
                                     _CAN_Ask_Channel* pNumChannel,
                                     _CMD_Mem* pCMDMess);

private:
    hid_device* deviceHandle;
    std::atomic<bool> isConnected;
    std::atomic<bool> isReading;
    std::thread readThread;
    DataReceivedHandler onDataReceived;

    static constexpr size_t ReportLength = USBD_BUF_SIZE;
};
