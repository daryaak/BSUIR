#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class File              //����� ����
{ 
protected:
	string file_name;   //�������� �����
	ifstream file_i;    //������ ������ ifstream
	ofstream file_o;    //������ ����� ofstream
public:
	File(string _name)  //����������� � �����������
	{
		file_name = _name;
	}
};
