#pragma once
#include "Exeption.h"

class InputExeption :public Exeption
{
private:
	char Message[Len];
public:

	InputExeption() :
		Exeption()
	{
		Message[0] = '\0';
	}

	InputExeption(int a, const char* T, const char* M) :
		Exeption(a, T)
	{
		strcpy_s(Message, Len, M);
	}
	~InputExeption() {}

	void ShowError() override;
};

int InputInt(int min, int max);
double InputDouble(int min, int max);
char* InputRussian();
char* InputEnglish();

