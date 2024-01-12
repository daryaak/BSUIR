#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include "Interface.cpp"


using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int NotUsed = system("color E7");
	Interface<char> inter;
	inter.MainMenu();
	return 0;
}