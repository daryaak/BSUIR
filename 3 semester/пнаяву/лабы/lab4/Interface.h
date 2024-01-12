#pragma once
#include "Man.h"
#include "MemberOfOrg.h"
#include "Professor.h"
#include "ProfMember.h"
#include "Header1.h"

template<class T>
class Interface {
public:
	void menu_of_class();							//Меню для выбора класса 
	void menu(Queue<T>& queue);						//Меню для выбора действия
};

template<class T>
void Interface<T>::menu_of_class() {
	int q = 0;
	cout << "Выберите с каким классом хотите работать:" << endl;
	cout << "1 - Человек " << endl;
	cout << "2 - Профессор" << endl;
	cout << "3 - Член организации" << endl;
	cin >> q;
	switch (q)
	{
	case 1: {
		Interface <Man> obj;
		Queue<Man> queue;
		obj.menu(queue);
	}break;
	case 2: {
		Interface <Professor> obj;
		Queue<Professor> queue;
		obj.menu(queue);
	}break;
	case 3: {
		Interface <MemberOfOrg> obj;
		Queue<MemberOfOrg> queue;
		obj.menu(queue);
	}break;
	}
}

template<class T>
void Interface<T>::menu(Queue<T>& st) {

	int select;
	do {
		system("cls");
		SetColor(5, 0);
		cout << setw(20) << "МЕНЮ:" << endl;
		SetColor(7, 0);
		cout << "Выберите действие, которое хотите совершить:" << endl;
		cout << "1. Добавить элемент в очередь" << endl;
		cout << "2. Удалить из очереди" << endl;
		cout << "3. Вывод таблицы" << endl;
		cout << "4. Поиск в очереди" << endl;
		cout << "5. Изменить поле определенного элемента в очереди" << endl;
		cout << "6. Выход из программы" << endl;
		cin >> select;
		switch (select)
		{
		case 1: {
			Algoritm<T> k;
			k.add(st);
		}break;

		case 2: {
			Algoritm<T> k;
			k.delete_el(st);
		}break;

		case 3: {
			if (st.size() == 0)
			{
				SetColor(4, 0);
				cout << "Очередь пуста" << endl;
				system("pause");
				SetColor(15, 0);
			}
			else {
				T n;
				SetColor(5, 0);
				n.HeadOfSheet();
				SetColor(15, 0);
				st.output1();
				system("pause");
			}
		}break;

		case 4: {
			Queue<T> h;
			int k;
			T m;
			SetColor(3, 0);
			cout << "Производится поиск по определенным полям(на месте тех полей, которыя являются необязательными, поставьте '0')" << endl;
			SetColor(7, 0);
			cin >> m;
			h = st.poisk(m);
			k = h.size();
			if (k == 0) {
				SetColor(12, 0);
				cout << "НУЖНЫХ ЭЛЕМЕНТОВ НЕ НАЙДЕНО" << endl;
				system("pause");
				SetColor(7, 0);
			}
			else {
				SetColor(5, 0);
				m.HeadOfSheet();
				SetColor(15, 0);
				h.output1();
				system("pause");
			}
		}break;

		case 5: {
			int k, count, p;
			k = st.size();
			T m;
			if (k == 0) {
				SetColor(12, 0);
				cout << "Очередь пуста";
				system("pause");
				SetColor(7, 0);
			}
			else {
				SetColor(3, 0);
				cout << "В очереди " << k << " элемента(ов). Поля какого желаете изменить???" << endl;
				SetColor(7, 0);
				cin >> count;
				m = st.perem(count);
				m.menu();
				st.returnback(m, count);
			}
		}break;

		case 6: {
		}break;
		}
	} while (select != 6);


}



//#pragma once
//#include "Interface.h"
//#include "Man.h"
//#include "MemberOfOrg.h"
//#include "Professor.h"
//#include "ProfMember.h"
//
//using namespace std;
//
//
//class Interface {
//public:
//	Interface() {};
//
//	~Interface() {};
//
//	void menu_pick_class();
//	
//};
