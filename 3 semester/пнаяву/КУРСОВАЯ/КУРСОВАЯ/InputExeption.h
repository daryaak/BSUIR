#pragma once
#include "Exeption.h"
class InputExeption :public Exeption   //класс исключений при вводе
{
private:
	char Message[Len];                 //сообщение об ошибке
public:

	InputExeption() :                  //конструктор по умолчанию
		Exeption()
	{
		Message[0] = '\0';
	}

	//конструктор с параметрами
	InputExeption(int a, const char* T, const char* M) :
		Exeption(a, T)
	{
		strcpy_s(Message, Len, M);
	}
	~InputExeption() {}                  //деструктор

	void ShowError() override;           //вывод сообщения об ошибке
};
int InputInt(int min, int max);          //проверка на ввод целого числа
double InputDouble(int min, int max);    //проверка на вывод вещественного числа
char* InputRussian();                    //проверка на ввод строки кириллицей
char* InputDate();                       //проверка на ввод даты
char* InputPhone();                      //проверка на ввод номера телефона

