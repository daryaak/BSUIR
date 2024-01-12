
#include "Inteface.h"


template <typename T>
void myInterface<T>::menu()
{

	int Type;

	string tfilename;
	string bfilename;
	bool fl = true;
	while (fl) {
		//SetColor(4, 0);
		cout << "Введите: " << endl << "1. Профессор" << endl
			<< "2. Член организации" << endl << "3. Профессор-член организации" << endl << "4. Выход" << endl;
		//SetColor(7, 0);
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

//void SetColor(int text, int background)
//{
//	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
//}

template <typename T>
void myInterface<T>::Menu(Queue<T>& obj,string tname,string bname)
{
	int v;
	bool flag = true;
	do {
		//SetColor(6, 0);
		cout << endl << "Введите действие: " << endl << "1. Добавление элемента" << endl << "2. Удаление " << endl
			<< "3. Просмотр очереди" << endl << "4. Поиск по параметрам" << endl;
		cout << "5.Прочитать из тектового файла " << endl << "6. Прочитать из бинарного файла" << endl;
		cout << "7.Записать в текстовый файл " << endl << "8. Записать в бинарный файл" << endl;
		cout << "9.Выход " << endl;
		//SetColor(7, 0);
		v = InputInt(1, 9);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			cout << "Ввод информации:" << endl;
			T a;
			cin >> a;
			obj.PushTail(a);
			break;
		}
		case 2:
		{
			//SetColor(6, 0);
			cout << endl << "Введите действие: " << endl << "1. Удаление из головы" << endl << "2. Удаление из хвоста" << endl
				<< "3. Удаление по индексу" << endl << "4. Выход из работы" << endl;
			//SetColor(7, 0);
			int pick;
			pick = InputInt(1, 4);
			//T temp;
			switch (pick)
			{
			case 1:
			{
				
				obj.DeleteFromHead();
				break;
			}
			case 2:
			{

				obj.DeleteFromTail();
				break;
			}
			case 3:
			{
				cout << "Введите номер элемента для удаления: ";
				int num = InputInt(0, obj.size());
				obj.Delete_(num);
				break;
			}
			case 4:
			{
				break;
			}
			}
			break;
		}
		case 3:
		{

			cout << "Очередь: " << endl;
			//SetColor(5, 0);
			obj.HeadTable();
			//SetColor(2, 0);
			obj.output();
			cout << endl;
			break;
		}
		case 4:
		{
			T f;
			f.Find();
			Queue<T> Temp = obj.Poisk(f);

			cout << "Результат:" << endl;
			if (Temp.QueueEmpty())
			{
				cout << "Не найдено";
			}
			else
			{
				Temp.HeadTable();
				Temp.output();
			}

			break;
		}
		case 5:
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
		}case 6:
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
		}case 7:
		{
			
			TextFile<T> fl_txt(tname);
			fl_txt.openWriteFile();
			int i = 0;
			while (i<obj.size())
			{
				fl_txt.writeFile(obj[i]);
				i++;
			}
			
			break;
		}case 8:
		{
			
			BinFile<T> fl_bin(bname);
			fl_bin.openWriteFile();
			int i=0;
			
			while (i<obj.size())
			{
				
				fl_bin.writeFile(obj[i++]);
			}
			
			break;
		}case 9:
		{
			flag = false;
		}
		}
	} while (flag);
}
