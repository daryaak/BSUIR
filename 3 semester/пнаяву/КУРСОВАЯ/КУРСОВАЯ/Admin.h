#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#define L 80                                  //��������� ��� ��������� ����� ������
using namespace std;

class Admin                                   //����� �������������
{
protected:
	char username[L];                         //��� ������������
	char password[L];                         //������
public:
	Admin()                                   //����������� �� ���������
	{
		this->username[0] = '\0';
		this->password[0] = '\0';
	}
	Admin(const char* u, const char* p)       //����������� � �����������
	{
		strcpy_s(this->username, L, u);
		strcpy_s(this->password, L, u);
	}
	Admin(const Admin& obj)                   //����������� �����������
	{
		strcpy_s(this->username, L, obj.username);
		strcpy_s(this->password, L, obj.password);
	}
	~Admin() {}
	//������ ��� �������� ������� � ����� ������(������� � �������)_
	void SetUsername(const char* a);          
	void Setpassword(const char* a);
	char* GetUsername();
	char* GetPassword();
	Admin operator=(const Admin& user);           //������������ �������� = 
	friend ostream& operator << (ostream& os, const Admin& obj); //���������� ������
	friend istream& operator >> (istream& in, Admin& obj);       //���������� �����
	friend ifstream& operator>>(ifstream& in, Admin& obj);       //���������� ������ �� �����
	friend ofstream& operator<<(ofstream& out, Admin& obj);      //���������� ������ � ����
};

