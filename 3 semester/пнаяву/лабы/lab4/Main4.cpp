//#include "Interface.h"
//#include "MyQueue.cpp"
//#include <Windows.h>
//
//int main() {
//
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//
//	Interface inter;
//
//	inter.menu_pick_class();
//
//
//
//	return 0;
//}

#include "Interface.h"

using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Interface <char> T;
	T.menu_of_class();

	return 0;
}
