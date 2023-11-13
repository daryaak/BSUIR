/*- � ������ ��������� ������� ���������� ��� �������������; 
- ���������� � ���� �������;
- ������� ������ ������� (%); 
- ������� ����� ����������������;
- ����������� ������� � ������ ����� � ���������� �� �������.
- ������� ����� ������ ������������ ��� ����������� � �������;
- ������� ���������� ����� ������ ������������ ����� ���������� ��������� ����������.
*/
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <thread>
#include <windows.h>
#include <winbase.h>
#include <poclass.h>
#include <powrprof.h>
#include <setupapi.h>
#include <devguid.h>
#include <string>

#pragma comment(lib, "PowrProf.lib")
#pragma comment(lib, "setupapi.lib")

using namespace std;

void menu();
string timeOutput(long secodns);
bool getStateOfPower(SYSTEM_POWER_STATUS status);
double getPercent(SYSTEM_POWER_STATUS status);
bool getStatus(SYSTEM_POWER_STATUS status);
double getWorkingTime(SYSTEM_POWER_STATUS status);
double getRemainingTime(SYSTEM_POWER_STATUS status);
void getBatteryType(SYSTEM_POWER_STATUS status);

int main()
{
	setlocale(LC_ALL, "Russian");
	SYSTEM_POWER_STATUS status;
	char option = 0;
	while (true)
	{
		cout << "\n";

		menu();
		option = _getch();
		cout << option << "\n\n";
		if (GetSystemPowerStatus(&status))
		{
			switch (option)
			{
			case '0':
			{
				if (getStateOfPower(status))
					cout << "��������� � ����";
				else
					cout << "�����������";
				break;
			}
			case '1':
			{
				cout << "��� �������: ";
				getBatteryType(status);
				break;
			}
			case '2':
			{
				if (getPercent(status))
					cout << "������� ������ �������: " << getPercent(status);
				else
					cout << "����������";
				break;
			}
			case '3':
			{
				if (getStatus(status))
					cout << "����� ����������������: �������";
				else
					cout << "����� ����������������: ��������";
				break;
			}
			case '4':
			{
				if (IsPwrSuspendAllowed())
					SetSuspendState(FALSE, FALSE, FALSE);
				break;
			}
			case '5':
			{
				if (IsPwrHibernateAllowed())
					SetSuspendState(TRUE, FALSE, FALSE);
				break;
			}
			case '6':
			{
				if (getWorkingTime(status))
					cout << "����� ������: " << getWorkingTime(status);
				else cout << "����������";
				break;
			}
			case '7':
			{
				if (getRemainingTime(status))
					cout << "���������� ����� ������: " << timeOutput(getRemainingTime(status));
				else cout << "����������";
				break;
			}case '8':
			{
				return 0;
			}
			default:
				break;
			}
		}
	}
	
	return 0;
}

void menu()
{
	cout << "\n";
	cout << "����\n";
	cout << "0 - ��� �������������\n";
	cout << "1 - ��� �������\n";
	cout << "2 - ������� ������ �������\n";
	cout << "3 - ������� ����� ����������������\n";
	cout << "4 - ������� � ������ �����\n";
	cout << "5 - ������� � ����������\n";
	cout << "6 - ����� ������ ������������\n";
	cout << "7 - ���������� ����� ������\n";
	cout << "8 - ����� �� ���������\n";
	cout << "������� ��� �����: ";

}


void getBatteryType(SYSTEM_POWER_STATUS status)
{
	HDEVINFO DeviceInfoSet;
	DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData = { 0 };
	ZeroMemory(&DeviceInterfaceData, sizeof(SP_DEVINFO_DATA));
	DeviceInterfaceData.cbSize = sizeof(SP_DEVINFO_DATA);

	SetupDiEnumDeviceInterfaces(DeviceInfoSet, NULL, &GUID_DEVCLASS_BATTERY, 0, &DeviceInterfaceData);
	DWORD cbRequired = 0;

	SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, NULL, &cbRequired, NULL);
	PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired);
	pdidd->cbSize = sizeof(*pdidd);

	SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, pdidd, cbRequired, &cbRequired, NULL);
	HANDLE hBattery = CreateFile(pdidd->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	BATTERY_QUERY_INFORMATION BatteryQueryInformation = { 0 };
	DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_TAG, NULL, NULL, &BatteryQueryInformation.BatteryTag,
		sizeof(BatteryQueryInformation.BatteryTag), NULL, NULL) && BatteryQueryInformation.BatteryTag;

	BATTERY_INFORMATION BatteryInfo = { 0 };
	BatteryQueryInformation.InformationLevel = BatteryInformation;

	DeviceIoControl(hBattery, IOCTL_BATTERY_QUERY_INFORMATION, &BatteryQueryInformation, sizeof(BatteryQueryInformation),
		&BatteryInfo, sizeof(BatteryInfo), NULL, NULL);

	for (int i = 0; i < 4; i++)
		cout << BatteryInfo.Chemistry[i];
	cout << endl;

	LocalFree(pdidd);
	SetupDiDestroyDeviceInfoList(DeviceInfoSet);

}

string timeOutput(long seconds)
{
	string result = to_string(seconds / 3600)
		+ " ����� " + to_string((seconds / 3600) % 60)
		+ " ����� " + to_string(seconds % 60) + " ������.";

	return result;
}

double getPercent(SYSTEM_POWER_STATUS status)
{
	int percent = static_cast<int>(status.BatteryLifePercent);
	if (percent == 255) return 0;
	return percent;
}

bool getStatus(SYSTEM_POWER_STATUS status)
{
	if (status.SystemStatusFlag == 0) return false;
	else return true;
}

bool getStateOfPower(SYSTEM_POWER_STATUS status)
{
	if (status.ACLineStatus == 0) return false;
	else return true;
}

double getWorkingTime(SYSTEM_POWER_STATUS status)
{
	long time = static_cast<long>(status.BatteryFullLifeTime);
	if (time == -1) return 0;
	return time;
}

double getRemainingTime(SYSTEM_POWER_STATUS status)
{
	long time = static_cast<long>(status.BatteryLifeTime);
	if (time == -1) return 0;
	return time;
}