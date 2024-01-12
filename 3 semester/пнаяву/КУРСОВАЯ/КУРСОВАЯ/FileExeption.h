#pragma once
#include "Exeption.h"
#include <iostream>
#include <fstream>
class FileExeption: public Exeption   //класс исключения файла
{
private:
	char Message[Len];                //сообщение об ошибке
public:
	FileExeption() :                  //конструктор по-умолчанию
		Exeption()
	{
		Message[0] = '\0';
	}
	 //конструктор с параметрами
	FileExeption(int a, const char* T, const char* M) :
		Exeption(a, T)
	{
		strcpy_s(Message, Len, M);
	}
	~FileExeption() {}                 //деструктор
	void ShowError() override;         //вывод сообщения об ошибке
};
bool exist_file(string name_file);      //функция проверки

