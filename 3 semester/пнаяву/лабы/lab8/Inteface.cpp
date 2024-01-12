#include "Inteface.h"
#include "Altorithm.cpp"




template <typename T>
void myInterface<T>::MenuStart()
{
	bool f=true;
	while (f)
	{
		cout << "�������� � ��� ��������" << endl << "0-���� ���������" << endl << "1-STL deque" << endl << "2-�����" << endl;
		int a;
		myInterface<char> ob;
		a = InputInt(0, 2);
		switch (a)
		{
		case 0:
		{
			ob.menu();
			break;
		}
		case 1:
		{
			ob.menudeque();
			break;
		}
		case 2:
		{
			f = false;
		}
		}
	}
}

template <typename T>
void myInterface<T>::menudeque()
{

	int Type;

	string tfilename;
	string bfilename;
	bool fl = true;
	while (fl) {
		
		cout << "�������: " << endl << "1. ���������" << endl
			<< "2. ���� �����������" << endl << "3. ���������-���� �����������" << endl << "4. �����" << endl;
		
		Type = InputInt(1, 5);
		cout << endl;
		switch (Type)
		{
		case 1:
		{
			myInterface<Professor> obj;
			deque<Professor> q;
			tfilename = "tProfessor.txt";
			bfilename = "bProfessor.bin";
			obj.Menufordeque(q, tfilename, bfilename);
			break;
		}
		case 2:
		{
			myInterface<MemberOfOrg> obj;
			deque<MemberOfOrg> q;
			tfilename = "tMemberOfOrg.txt";
			bfilename = "bMemberOfOrg.bin";
			obj.Menufordeque(q, tfilename, bfilename);
			break;
		}
		case 3:
		{
			myInterface<ProfMember> obj;
			deque<ProfMember> q;
			tfilename = "tProfMember.txt";
			bfilename = "bProfMember.bin";
			obj.Menufordeque(q, tfilename, bfilename);
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
void myInterface<T>::Menufordeque(deque<T>& obj, string tname, string bname)
{
	int v;
	bool flag = true;

	do 
	{
		cout << endl << "������� ��������: " << endl << "1. ���������� ��������" << endl << "2. �������� " << endl
			<< "3. �������� �������" <<  endl << "4. ��������������" << endl ;
		cout << "5.��������� �� ��������� ����� " << endl << "6. ��������� �� ��������� �����" << endl;
		cout << "7.�������� � ��������� ���� " << endl << "8. �������� � �������� ����" << endl;
		cout << "9.����� " << endl;
		
		v = InputInt(1, 9);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			cout << "���� ����������:" << endl << endl;
			T a;
			cin >> a;
			system("cls");
			cout << endl << "������� ��������: " << endl << "1. �������� � ������" << endl << "2. �������� � ����� " << endl
				<< "3. �������� � �������" << endl;
			int s;
			s = InputInt(1, 3);
			switch (s)
			{
			case 1:
			{
				obj.push_front(a);
				break;
			}
			case 2:
			{
				obj.push_back(a);
				break;
			}
			case 3:
			{
				cout << "������� �������: ";
				int w;
				w = InputInt(1, obj.size());
				auto iter1 = obj.begin();
				obj.insert(iter1 + w - 1, a);
				break;
			}
			}
			break;
		}
		case 2:
		{
			
			cout << endl << "������� ��������: " << endl << "1. �������� ������� ��������" << endl << "2. �������� ���������� ��������" << endl
				<< "3. �������� �� ������" << endl << "4. �������� ���� �������" << endl << "5. �������� ���������" << endl;
			
			int pick;
			pick = InputInt(1, 5);
			switch (pick)
			{
			case 1:
			{
				obj.pop_front();
				break;
			}
			case 2:
			{
				obj.pop_back();
				break;
			}
			case 3:
			{
				cout << "������� �������: ";
				int ww;
				ww = InputInt(1, obj.size());
				auto iter2 = obj.begin();
				obj.erase(iter2 + ww - 1);
				break;
			}
			case 4:
			{
				obj.clear();
				break;
			}
			case 5:
			{
				auto iter3 = obj.begin();
				cout << "������� ������� ������ ���������: ";
				int ww1;
				ww1 = InputInt(1, obj.size());
				cout << "������� ������� ����� ���������: ";
				int ww2;
				ww2 = InputInt(ww1, obj.size());
				obj.erase(iter3 + ww1-1 , iter3 + ww2);
				break;
			}
			}
			break;
		}
		case 3:
		{
			system("cls");
			cout << endl;
			if (obj.empty())
			{
				cout << "������� �����" << endl;
			}
			else {
				obj[0].HeadOfSheet();
				auto begin = obj.begin();
				auto end = obj.end();
				int i = 1;
				for (; begin != end; ++begin)
				{
					cout.setf(ios::left);
					cout << setw(5) << i++ << *begin;
				}
				cout.unsetf(ios::left);
				cout << endl;
			}
			break;
		}
		case 4:
		{
			if (obj.empty())
			{
				cout << "������� �����" << endl;
			}
			else {
				
				cout << "������� ����� ����������� �������� : ";
				int tempNum = InputInt(1, obj.size());
				obj[tempNum - 1].Change();
				cout << endl;
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
					obj.push_back(temp);
				}
			}
		}	break;
		case 6:
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
					obj.push_back(temp);
				}
			}
			break;
		}
		case 7:
		{

			TextFile<T> fl_txt(tname);
			fl_txt.openWriteFile();
			auto begin = obj.begin();
			auto end = obj.end();
			int i = 1;
			for (; begin != end; ++begin)
			{
				fl_txt.writeFile(*begin);
			}

			break;
		}
		case 8:
		{
			BinFile<T> fl_txt(bname);
			fl_txt.openWriteFile();
			auto begin = obj.begin();
			auto end = obj.end();
			int i = 1;
			for (; begin != end; ++begin)
			{
				fl_txt.writeFile(*begin);
			}

			break;
		}
		case 9:
		{
			flag = false;
		}
		}
	} while (flag);
	
}

template <typename T>
void myInterface<T>::menu()
{

	int Type;

	string tfilename;
	string bfilename;
	bool fl = true;
	while (fl) {
		cout << "�������: " << endl << "1. ���������" << endl
			<< "2. ���� �����������" << endl << "3. ���������-���� �����������" << endl << "4. �����" << endl;
		
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
		cout << endl << "������� ��������: " << endl << "1. ���������� ��������" << endl << "2. �������� " << endl
			<< "3. �������� �������" << endl << "4. ����� �� ����������" << endl << "5. ��������������" << endl << "6. ����������" << endl;
		cout << "7.��������� �� ��������� ����� " << endl << "8. ��������� �� ��������� �����" << endl;
		cout << "9.�������� � ��������� ���� " << endl << "10. �������� � �������� ����" << endl;
		cout << "11.����� " << endl;
		v = InputInt(1, 11);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			system("cls");
			cout << "���� ����������:" << endl << endl;
			T a;
			cin >> a;
			Algorithm<T>::Add(a, obj);
			break;
		}
		case 2:
		{
			cout << endl << "������� ��������: " << endl << "1. �������� �� ������" << endl << "2. �������� �� ������" << endl
				<< "3. �������� �� ������" << endl << "4. ����� �� ������" << endl;
		
			int pick;
			pick = InputInt(1, 4);
			if (pick == 3)
			{
				cout << "������� ����� �������� ��� ��������: ";
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
				cout << "������ �� �������" << endl;
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
				cout << "������� �����" << endl;
			}
			else {
				system("cls");
				cout << endl;
				obj.HeadTable();
				obj.output();
				cout << endl;
				cout << "������� ����� ����������� �������� : ";
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
			cout << "����������: �� �������� - 1, �� ����������� - 0: ";
			int s = InputInt(0, 1);
			cout << endl;
			T f;
			f.Pick();
			if (s == 1)
			{
				Algorithm<T>::SortFromMax(obj.begin(), obj.end(), f);
			}
			else Algorithm<T>::SortFromMin(obj.begin(), obj.end(), f);
			obj.HeadTable();
			obj.output();
			break;
		}
		case 7:
		{
			if (check_file(tname))
			{
				obj.textfile_in(tname);
			}
			break;
		}case 8:
		{
			if (check_file(bname))
			{
				obj.binfile_in(bname);
			}
			break;
		}case 9:
		{
			obj.textfile_out(tname);
			break;
		}case 10:
		{
			obj.binfile_out(bname);
			break;
		}case 11:
		{
			flag = false;
		}
		}
	} while (flag);
}