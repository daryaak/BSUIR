#include "Algorithm.cpp"
#include "Inteface.h"


template <typename T>
void myInterface<T>::menu()
{

	int Type;

	string tfilename;
	string bfilename;
	bool fl = true;
	while (fl) {
		
		cout << "Введите: " << endl << "1. Профессор" << endl
			<< "2. Член организации" << endl << "3. Профессор-член организации" << endl << "4. Выход" << endl;
		
		Type = InputInt(1, 5);
		cout << endl;
		switch (Type)
		{
		case 1:
		{
			myInterface<Professor> obj;
			Queue<Professor> q;
			tfilename = "tProfessor.txt";
			bfilename = "bProfessor.bin";
			obj.Menu(q, tfilename, bfilename);
			break;
		}
		case 2:
		{
			myInterface<MemberOfOrg> obj;
			Queue<MemberOfOrg> q;
			tfilename = "tMemberOfOrg.txt";
			bfilename = "bMemberOfOrg.bin";
			obj.Menu(q, tfilename, bfilename);
			break;
		}
		case 3:
		{
			myInterface<ProfMember> obj;
			Queue<ProfMember> q;
			tfilename = "tProfMember.txt";
			bfilename = "bProfMember.bin";
			obj.Menu(q, tfilename, bfilename);
			break;
		}
		case 4:
		{
			fl = false;
		}
		}
	}

};


template <typename T>
void myInterface<T>::Menu(Queue<T>& obj, string tname, string bname)
{
	int v;
	bool flag = true;
	do {
		
		cout << endl << "Введите действие: " << endl << "1. Добавление элемента" << endl << "2. Удаление " << endl
			<< "3. Просмотр очереди" << endl << "4. Поиск по параметрам" << endl << "5. Редактирование" << endl << "6. Сортировка" << endl;
		cout << "7.Прочитать из тектового файла " << endl << "8. Прочитать из бинарного файла" << endl;
		cout << "9.Записать в текстовый файл " << endl << "10. Записать в бинарный файл" << endl;
		cout << "11.Выход " << endl;
		
		v = InputInt(1, 11);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			system("cls");
			cout << "Ввод информации:" << endl << endl;
			T a;
			cin >> a;
			
			Algorithm<T>::Add(a, obj);
			
			break;
		}
		case 2:
		{
			
			cout << endl << "Введите действие: " << endl << "1. Удаление из головы" << endl << "2. Удаление из хвоста" << endl
				<< "3. Удаление по номеру" << endl << "4. Выход из работы" << endl;
			
			int pick;
			pick = InputInt(1, 4);
			if (pick == 3)
			{
				cout << "Введите номер элемента для удаления: ";
				int num = InputInt(0, obj.size());
				Algorithm<T>::Delete_Element(num, obj, pick);
			}
			else(Algorithm<T>::Delete_Element(0, obj, pick));
			
			break;
		}
		case 3:
		{
			system("cls");
			cout << endl;
			obj.HeadTable();
			obj.output();
			cout << endl;
			break;
		}
		case 4:
		{
			system("cls");
			cout << endl;
			
			obj.HeadTable();
			
			obj.output();
			
			cout << endl;
			T f;
			f.Find();
			Queue<T> res = Algorithm<T>::Search(obj.begin(), obj.end(), f);
			if (res.QueueEmpty())
			{
				cout << "Ничего не найдено" << endl;
			}
			else
			{
				res.HeadTable();
				res.output();
			}
			break;
		}
		case 5:
		{
			if (obj.QueueEmpty())
			{
				cout << "Очередь пуста" << endl;
			}
			else {
				system("cls");
				cout << endl;
				obj.HeadTable();
				obj.output();
				cout << endl;
				cout << "Введите номер изменяемого элемента : ";
				int tempNum = InputInt(1, obj.size());
				Algorithm<T>::update(obj, tempNum);
				system("cls");
				cout << endl;
				obj.HeadTable();
				obj.output();
				cout << endl;
			}
			break;
		}
		case 6:
		{
			system("cls");
			cout << "Сортировка: по убыванию - 1, по возрастанию - 0: ";
			int s = InputInt(0, 1);
			cout << endl;
			T f;
			f.Pick();
			if (s == 1)
			{
				Algorithm<T>::SortFromMax(obj.begin(), obj.end(),f);
			}
			else Algorithm<T>::SortFromMin(obj.begin(), obj.end(),f);
			obj.HeadTable();
			obj.output();
			break;
		}
		case 7:
		{
			if (check_file(tname))
			{
				TextFile<T> fl_txt(tname);
				fl_txt.openReadFile();
				T temp;
				while (1)
				{
					fl_txt.readFile(temp);
					if (fl_txt.feof()) break;
					obj.PushTail(temp);
				}
			}
			break;
		}case 8:
		{
			if (check_file(bname))
			{
				
				BinFile<T> fl_bin(bname);
				fl_bin.openReadFile();
				T temp;
				while (1)
				{
					fl_bin.readFile(temp);
					if (fl_bin.feof()) break;
					obj.PushTail(temp);
				}
			}
			break;
		}case 9:
		{
			TextFile<T> fl_txt(tname);
			fl_txt.openWriteFile();
			Iterator<T> begin = obj.begin();
			Iterator<T> end = obj.end();
			int i = 1;
			for (; begin != end; ++begin)
			{
				fl_txt.writeFile(*begin);
			}
			break;
		}case 10:
		{
			BinFile<T> fl_txt(bname);
			fl_txt.openWriteFile();
			Iterator<T> begin = obj.begin();
			Iterator<T> end = obj.end();
			int i = 1;
			for (; begin != end; ++begin)
			{
				fl_txt.writeFile(*begin);
			}
			break;
		}case 11:
		{
			flag = false;
		}
		}
	} while (flag);
}
