#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class File              //класс файл
{ 
protected:
	string file_name;   //название файла
	ifstream file_i;    //объект потока ifstream
	ofstream file_o;    //объект поток ofstream
public:
	File(string _name)  //конструктор с параметрами
	{
		file_name = _name;
	}
};
