#pragma once
#include "Exeption.h"
#include <iostream>
#include <fstream>
class FileExeption: public Exeption   //����� ���������� �����
{
private:
	char Message[Len];                //��������� �� ������
public:
	FileExeption() :                  //����������� ��-���������
		Exeption()
	{
		Message[0] = '\0';
	}
	 //����������� � �����������
	FileExeption(int a, const char* T, const char* M) :
		Exeption(a, T)
	{
		strcpy_s(Message, Len, M);
	}
	~FileExeption() {}                 //����������
	void ShowError() override;         //����� ��������� �� ������
};
bool exist_file(string name_file);      //������� ��������

