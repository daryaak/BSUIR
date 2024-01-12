#include<iostream>
#include<Windows.h>
#include"mystring.h"
#include <string>

using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int repeat;
	do
	{ 
		rewind(stdin);
		system("cls");
	String a;
	cout << "¬ведите a:";
	cin >> a;
	String b;
	cout << "¬ведите b:";
	cin >> b;
	String g;
	cout << "¬ведите g:";
	cin >> g;
	String c;
	char* line;
	cout << "¬ведите line:";
	line = new char[80];
	cin.getline(line,80);
	b += line + a + " " + "hello" + " " + a(2, 6) + " " + g[3];
	cout << g << endl;
	cout << b << endl;
	cout << "∆елаете продолжить?1-да" << endl;              //запрос на повтор программы
	cin >> repeat;
	if (repeat != 1)
	{
		system("pause");
		return 0;
	}
	} while (repeat == 1);
}