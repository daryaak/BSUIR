#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#define L 80                                  //константа для установки длины строки
using namespace std;

class Admin                                   //класс Администратор
{
protected:
	char username[L];                         //Имя пользователя
	char password[L];                         //Пароль
public:
	Admin()                                   //конструктор по умолчанию
	{
		this->username[0] = '\0';
		this->password[0] = '\0';
	}
	Admin(const char* u, const char* p)       //конструктор с параметрами
	{
		strcpy_s(this->username, L, u);
		strcpy_s(this->password, L, u);
	}
	Admin(const Admin& obj)                   //конструктор копирования
	{
		strcpy_s(this->username, L, obj.username);
		strcpy_s(this->password, L, obj.password);
	}
	~Admin() {}
	//методы для получени доступа к полям класса(геттеры и сеттеры)_
	void SetUsername(const char* a);          
	void Setpassword(const char* a);
	char* GetUsername();
	char* GetPassword();
	Admin operator=(const Admin& user);           //перегрженный оператор = 
	friend ostream& operator << (ostream& os, const Admin& obj); //перегрузка вывода
	friend istream& operator >> (istream& in, Admin& obj);       //перегрузка ввода
	friend ifstream& operator>>(ifstream& in, Admin& obj);       //перегрзука чтения из файла
	friend ofstream& operator<<(ofstream& out, Admin& obj);      //перегрузка записи в файл
};

