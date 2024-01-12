
#include<cstring>
#include<iostream>
using namespace std;

class String
{
private:
	char* str;
	int size;

public:

	String()                                        //конструктор по умолчанию
	{
		size = 0;
		str = nullptr;
	}

	String(const char* str1)                       //конструктор с параметром
	{
		this->size = strlen(str1);
		strcpy_s(this->str, strlen(str1), str1);
	}

	String(const String& other)                    //конструктор копирования
	{
		this->str = new char[other.size + 1];
		strcpy_s(this->str, other.size + 1, other.str);
		this->size = strlen(str);
	}
	 
	String(String&& other)                         //конструктор перемещения
	{
		this->str = other.str;
		this->size = other.size;

		other.str = nullptr;
		other.size = 0;
	}
	
	~String()                                      //деструктор
	{
		if (str)
			delete[] str;
	}

	// string=string
	String& operator=(const String& s);
	
	//string=*char
	String& operator=(const char* s);



	//obj+obj 
	String operator+(const String& s);

	//obj+*char
	String operator+(const char* s);

	//obj+char
	String operator+(const char s);

	//char*+obj
	friend String operator+(const char* s, String& s1);

	//перегрузка вывода
	friend ostream& operator<< (ostream& os, String& s);

	//перегрузка ввода
	friend istream& operator>> (istream& is, String& s);

	//obj+=obj
	String operator +=(const String& s);

	//obj+=*char
	String operator +=(const char* s);

	//obj==obj
	bool operator == (const String& s);

	//obj==*char
	bool operator == (const char* s);

	//obj!=obj
	bool operator != (const String& s);

	//obj!=*char
	bool operator != (const char* s);

	//s(int,int)
	String operator()(int beg, int end);

	//obj[int]
	char& operator[](int pos);
};
