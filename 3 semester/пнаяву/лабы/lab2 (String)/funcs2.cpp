#include"Header2.h"
#include "conio.h"

// char*+obj
String operator+(const char* s, String& s1)
{
	String temp;
	temp.size = s1.size + strlen(s);
	temp.str = new char[temp.size + 1];
	strcpy_s(temp.str, temp.size + 1, s);
	strcat_s(temp.str, temp.size + 1, s1.str);
	return temp;
}

//перегрузка вывода
ostream& operator<< (ostream& os, String& s)
{
	os << s.str << endl;
	return os;
}

//перегрузка вывода
istream& operator>> (istream& is, String& s) // оператор для записи строки из потока ввода
{
	rewind(stdin);
	//if(s.str) delete[] s.str;
	char* buf=new char[80];
	is.getline(buf, 80);
	///s.size = strlen(buf);
	//s.str = new char[s.size + 1];
	//strcpy_s(s.str,s.size+1, buf);
	s = buf;
	delete[] buf;
	return is;
}