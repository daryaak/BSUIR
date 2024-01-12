#include"Man.h"
#include "Professor.h"
#include "MemberOfOrg.h"
#include "ProfMember.h"
#include<Windows.h>
#include "conio.h"

int main()
{	
	int repeat;
	do
	{
		system("Color 7D");
		rewind(stdin);
		system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "¬ведите количество членов огранизации: ";
	int kol;                                                                   //количество членов организации
	cin >> kol;
	MemberOfOrg* b;
	b=  new MemberOfOrg[kol];
	rewind(stdin);
	cout << "¬ведите информацию о членах организаций" << endl;
	for (int i = 0; i < kol; i++)                                              //ввод членов организации
	{
		cin >> b[i];
	}
	b[0].HeadOfSheet();                                                        //вывод шапки таблицы
	for (int i = 0; i < kol; i++)                                              //вывод членов организации
	{
		cout << b[i];
	}

	//cout << "¬ведите информацию о профессорах-членах организаций " << endl;
	//ProfMember c;                                                              //объект класса профессор-член организации
	//cin >> c;                                                                  //ввод объекта
	//c.HeadOfSheet();                                                           //шапка таблицы
	//cout << c;                                                                 //вывод объекта
	//ProfMember s;                                                              //объект класса профессор-член орг
	//s = c;                                                                     //операци€ присваивани€
	//cout << "¬ведите новую фамилию: ";
	//char line[20];                                                             //нова€ фамили€
	//cin >> line;
	//s.setSurname(line);                                                        //установка новой фамилии
	//cout << s;                                                                 //вывод объекта с новой фамилией

	delete[] b;                                                                //освобождение пам€ти

	cout << "∆елаете продолжить?1-да" << endl;              //запрос на повтор программы
	cin >> repeat;
	if (repeat != 1)
	{
		system("pause");
		return 0;
	}
	} while (repeat == 1);
}