
#include<cstring>
#include<iostream>
using namespace std;

class String
{
private:
	char* str;
	int size;

public:

	String()                                        //����������� �� ���������
	{
		size = 0;
		str = nullptr;
	}

	String(const char* str1)                       //����������� � ����������
	{
		this->size = strlen(str1);
		strcpy_s(this->str, strlen(str1), str1);
	}

	String(const String& other)                    //����������� �����������
	{
		this->str = new char[other.size + 1];
		strcpy_s(this->str, other.size + 1, other.str);
		this->size = strlen(str);
	}
	 
	String(String&& other)                         //����������� �����������
	{
		this->str = other.str;
		this->size = other.size;

		other.str = nullptr;
		other.size = 0;
	}
	
	~String()                                      //����������
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

	//���������� ������
	friend ostream& operator<< (ostream& os, String& s);

	//���������� �����
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
