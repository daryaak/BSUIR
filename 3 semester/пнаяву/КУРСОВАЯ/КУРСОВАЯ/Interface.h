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
 //��������� ����� ���������
template <typename T> 
class Interface
{
public:
	Interface() {};                          //����������� ��-���������
	~Interface() {};                         //����������
	void MainMenu();                         //�������� ����
	void menu(int p);                        //���� ������ �������� � ��������
	//���� ��� ��������������
	void Menu(Queue<T>& obj, string filename,string bfilename);
	//���� ��� �����
	void MenuForGuest(Queue<T>& q, string filename,string bfilename);
   //���� ��� ��������������� �����
	void MenuForReserved(Queue<T>& res, string bfilename);
};

