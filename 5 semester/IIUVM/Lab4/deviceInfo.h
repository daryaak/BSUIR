#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <setupapi.h>
#include <devguid.h>
#include <cwchar>

using namespace std;

class deviceInfo
{
private:
    WCHAR devType[255];
    WCHAR friendlyName[255];
    WCHAR deviceDesc[255];
    WCHAR mfg[255];
    WCHAR hardwareID[255];
    WCHAR instanseID[255];

public:

    deviceInfo() {
        this->deviceDesc[0] = L'\0';
        this->devType[0] = L'\0';
        this->friendlyName[0] = L'\0';
        this->mfg[0] = L'\0';
        this->hardwareID[0] = L'\0';
        this->instanseID[0] = L'\0';
    }

    void initialize() {
        HDEVINFO hDevInfo;
        SP_DEVINFO_DATA DeviceInfoData;

        WCHAR temp_devType[255];
        WCHAR temp_friendlyName[255];
        WCHAR temp_deviceDesc[255];
        WCHAR temp_mfg[255];
        WCHAR temp_hardwareID[255];
        WCHAR temp_instanseID[255];

        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        hDevInfo = SetupDiGetClassDevsW(&GUID_DEVCLASS_CAMERA, 0, 0, DIGCF_PRESENT);
        SetupDiEnumDeviceInfo(hDevInfo, 0, &DeviceInfoData);

        if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData,
            SPDRP_DEVTYPE, NULL, (PBYTE)temp_devType, 255, NULL)) {        
            wcscpy_s(this->devType, temp_devType);
        }

        if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData,
            SPDRP_FRIENDLYNAME, NULL, (PBYTE)temp_friendlyName, 255, NULL)) {
            wcscpy_s(this->friendlyName, temp_friendlyName);
        }

        if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData,
            SPDRP_DEVICEDESC, NULL, (PBYTE)temp_deviceDesc, 255, NULL)) {
            wcscpy_s(this->deviceDesc, temp_deviceDesc);
        }

        if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData,
            SPDRP_MFG, NULL, (PBYTE)temp_mfg, 255, NULL)) {
            wcscpy_s(this->mfg, temp_mfg);
        }

        if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData,
            SPDRP_HARDWAREID, NULL, (PBYTE)temp_hardwareID, 255, NULL)) {
            wcscpy_s(this->hardwareID, temp_hardwareID);
        }

        if (SetupDiGetDeviceInstanceIdW(hDevInfo, &DeviceInfoData,
            (PWSTR)temp_instanseID, 255, NULL)) {
            wcscpy_s(this->instanseID, temp_instanseID);
        }

        SetupDiDestroyDeviceInfoList(hDevInfo);
    };

    friend wostream& operator<<(std::wostream& os, const deviceInfo& obj) {
        if (obj.devType[0] != L'\0') os << L"Тип устройства: " << obj.devType << endl;
        if (obj.friendlyName[0] != L'\0') os << L"Название: " << obj.friendlyName << endl;
        if (obj.deviceDesc[0] != L'\0') os << L"Описание устройства: " << obj.deviceDesc << endl;
        if (obj.mfg[0] != L'\0') os << L"Производитель: " << obj.mfg << endl;
        if (obj.hardwareID[0] != L'\0') os << L"Hardware ID: " << obj.hardwareID << endl;
        if (obj.instanseID[0] != L'\0') os << L"Instanse ID: " << obj.instanseID << endl;
        return os;
    };

};

