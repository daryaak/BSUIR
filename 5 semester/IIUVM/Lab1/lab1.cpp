/*- в режиме реального времени показывать тип энергопитания; 
- информация о типе батареи;
- уровень заряда батареи (%); 
- текущий режим энергосбережения;
- реализовать переход в спящий режим и гибернацию из консоли.
- вывести время работы аккумулятора без подключения к зарядке;
- вывести оставшееся время работы аккумулятора после отключения зарядного устройства.
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
					cout << "Подключен к сети";
				else
					cout << "Аккумулятор";
				break;
			}
			case '1':
			{
				cout << "Тип батареи: ";
				getBatteryType(status);
				break;
			}
			case '2':
			{
				if (getPercent(status))
					cout << "Уровень заряда батареи: " << getPercent(status);
				else
					cout << "Неизвестно";
				break;
			}
			case '3':
			{
				if (getStatus(status))
					cout << "Режим энергосбережения: включен";
				else
					cout << "Режим энергосбережения: отключен";
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
					cout << "Время работы: " << getWorkingTime(status);
				else cout << "Неизвестно";
				break;
			}
			case '7':
			{
				if (getRemainingTime(status))
					cout << "Оставшееся время работы: " << timeOutput(getRemainingTime(status));
				else cout << "Неизвестно";
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
	cout << "Меню\n";
	cout << "0 - тип энергопитания\n";
	cout << "1 - тип батареи\n";
	cout << "2 - уровень заряда батареи\n";
	cout << "3 - текущий режим энергосбережения\n";
	cout << "4 - переход в спящий режим\n";
	cout << "5 - переход в гибернацию\n";
	cout << "6 - время работы аккумулятора\n";
	cout << "7 - оставшееся время работы\n";
	cout << "8 - выход из программы\n";
	cout << "Введите ваш выбор: ";

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
		+ " часов " + to_string((seconds / 3600) % 60)
		+ " минут " + to_string(seconds % 60) + " секунд.";

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