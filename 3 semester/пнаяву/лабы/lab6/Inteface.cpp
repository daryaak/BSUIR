
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
		cout << "�������: " << endl << "1. ���������" << endl
			<< "2. ���� �����������" << endl << "3. ���������-���� �����������" << endl << "4. �����" << endl;
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
		cout << endl << "������� ��������: " << endl << "1. ���������� ��������" << endl << "2. �������� " << endl
			<< "3. �������� �������" << endl << "4. ����� �� ����������" << endl;
		cout << "5.��������� �� ��������� ����� " << endl << "6. ��������� �� ��������� �����" << endl;
		cout << "7.�������� � ��������� ���� " << endl << "8. �������� � �������� ����" << endl;
		cout << "9.����� " << endl;
		//SetColor(7, 0);
		v = InputInt(1, 9);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			cout << "���� ����������:" << endl;
			T a;
			cin >> a;
			obj.PushTail(a);
			break;
		}
		case 2:
		{
			//SetColor(6, 0);
			cout << endl << "������� ��������: " << endl << "1. �������� �� ������" << endl << "2. �������� �� ������" << endl
				<< "3. �������� �� �������" << endl << "4. ����� �� ������" << endl;
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
				cout << "������� ����� �������� ��� ��������: ";
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

			cout << "�������: " << endl;
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

			cout << "���������:" << endl;
			if (Temp.QueueEmpty())
			{
				cout << "�� �������";
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
