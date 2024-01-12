#pragma once
//#include "Voucher.h"
#include "Travel.h"
#include "Turism.h"
#include "Sea.h"
#include "Sanatorium.h"
#include "Relax.h"
#include "Therapy.h"
#include "Admin.h"
#include "Queue.cpp"
#include "Reserve.h"
#include "FileExeption.h"
#include <Windows.h>

using namespace std;
 //шаблонный класс интерфейс
template <typename T> 
class Interface
{
public:
	Interface() {};                          //конструктор по-умолчанию
	~Interface() {};                         //деструктор
	void MainMenu();                         //основное меню
	void menu(int p);                        //меню выбора действий с очередью
	//меню для администратора
	void Menu(Queue<T>& obj, string filename,string bfilename);
	//меню для гостя
	void MenuForGuest(Queue<T>& q, string filename,string bfilename);
   //меню для забронированных туров
	void MenuForReserved(Queue<T>& res, string bfilename);
};

