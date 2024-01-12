#include "Interface.h"
#include "Algorithm.cpp"



template <typename T>
void Interface<T>::menu(int p)
{
	int Type;
	int TType;
	string filename;
	string bfilename;
	bool fl = true;
	do
	{
		system("cls");
		cout <<endl<< "�������� ��� ������: " << endl<< "1. �����������" <<endl<< "2. ���������� �����" <<endl<<"3.�����" <<endl;
		Type = InputInt(1, 3);
		switch (Type)
		{
			
		case 1:
			{
			    system("cls");
				cout << "�������� ��� �����������: " << endl <<"1. ������������� �������" << endl << "2. ����� �� ����" << endl <<"3.�����" << endl;
				TType = InputInt(1, 3);
				switch (TType)
				{
				case 1:
				{
					Interface<Turism> obj;
					Queue<Turism> q;
					filename = "turism.txt";
					bfilename = "bronturism.txt";
					if (p == 1)
					{
						obj.MenuForGuest(q, filename, bfilename);
					}
					if (p == 2)
					{
						obj.Menu(q, filename, bfilename);
					}
					break;
				}
				case 2:
				{
					Interface<Sea> obj;
					Queue<Sea> q;
					filename = "sea.txt";
					bfilename = "bronsea.txt";
					if (p == 1)
					{
						obj.MenuForGuest(q, filename, bfilename);
					}
					if (p == 2)
					{
						obj.Menu(q, filename, bfilename);
					}
					break;
				}
				case 3:
				{
					return;
				}
				}
				break;
			}
		
			case 2:
			{
				system("cls");
				cout << "�������� ��� ������������� ������: " << endl << "1.���� ������" << endl << "2. ���������" << endl <<"3.�����" << endl;
				TType = InputInt(1, 3);
				switch (TType)
				{
				case 1:
				{
					Interface<Relax> obj;
					Queue<Relax> q;
					filename = "relax.txt";
					bfilename = "bronrelax.txt";
					if (p == 1)
					{
						obj.MenuForGuest(q, filename, bfilename);
					}
					if (p == 2)
					{
						obj.Menu(q, filename, bfilename);
					}
					break;
				}
				case 2:
				{
					Interface<Therapy> obj;
					Queue<Therapy> q;
					filename = "therapy.txt";
					bfilename = "brontherapy.txt";
					if (p == 1)
					{
						obj.MenuForGuest(q, filename, bfilename);
					}
					if (p == 2)
					{
						obj.Menu(q, filename, bfilename);
					}
					break;
				}
				case 3:
				{
					return;
				}
			break;
			}
			 case 3:
			{
				return;
		    }
			}
		}
	} while (fl);
	return;
};

template <typename T>
void Interface<T>::MenuForReserved(Queue<T>& res, string bfilename)
{
	system("cls");
	vector<T> LastAction;
	vector<int> ActionPos;
	vector<int> Position;
	Iterator<T> it;
	int v;
	bool flag = true;
	do
	{
		cout << endl << "������� ��������: " << endl <<"1. ���������� �����" << endl <<"2. �������� �����" << endl
			<< "3. �������� ���� ��������������� �����" << endl <<"4. ����� ����� �� ����������" << endl <<"5. �������������� �����" << endl <<"6. ���������� �����" << endl;
		cout <<"7.�������� ����� � ���� " << endl << "8.������ ����� �� �����" << endl << "9.������ ���������� ��������" << endl;
		cout <<"10.����� �� ������ " << endl;
		v = InputInt(1, 10);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			system("cls");
			cout << "���� ����������:" << endl << endl;
			T a;
			cin >> a;
			SetColor(2);
			Algorithm<T>::Add(a, res,LastAction, ActionPos, Position);
			SetColor(5);
			break;
		}
		case 2:
		{
			system("cls");
			SetColor(2);
			res.HeadTable();
			SetColor(1);
			res.output();
			SetColor(5);
			cout << endl;
			int num;
			cout << "������� ����� ����� ��� ��������: " << endl;
			cin >> num;
			Algorithm<T>::Delete_Element(num,res, LastAction, ActionPos, Position);
			break;
		}
		case 3:
		{
			system("cls");
			cout << endl;
			SetColor(2);
			res.HeadTable();
			SetColor(1);
			res.output();
			SetColor(5);
			cout << endl;
			break;
		}
		case 4:
		{
			system("cls");
			cout << endl;
			SetColor(2);
			res.HeadTable();
			SetColor(1);
			res.output();
			SetColor(5);
			cout << endl;
			T f;
			f.Find();
			Queue<T> result = Algorithm<T>::Search(res.begin(), res.end(), f);
			SetColor(2);
			result.HeadTable();
			SetColor(1);
			result.output();
			SetColor(5);
			break;
		}
		case 5:
		{
			system("cls");
			cout << endl;
			SetColor(2);
			res.HeadTable();
			SetColor(1);
			res.output();
			SetColor(5);
			cout << endl;
			Algorithm<T>::update(res,LastAction, ActionPos, Position);
			break;
		}
		case 6:
		{
			system("cls");
			cout << "����������: �� �������� - 1, �� ����������� - 0: ";
			int s = InputInt(0, 1);
			cout << endl;
			if (s == 1)
			{
				Algorithm<T>::SortFromMax(res.begin(), res.end());
			}
			else Algorithm<T>::SortFromMin(res.begin(), res.end());
			SetColor(2);
			res.HeadTable();
			SetColor(1);
			res.output();
			SetColor(5);
			break;
		}
		case 7:
		{
			system("cls");
			if (exist_file(bfilename))
			{
				res.file_out1(bfilename);
			}
		}break;
		case 8:
		{
			system("cls");
			if (exist_file(bfilename))
				res.file_in(bfilename);
			SetColor(2);
			res.HeadTable();
			SetColor(1);
			res.output();
			SetColor(5);

		}break;
		case 9:
		{
			system("cls");
			if (!LastAction.empty())
			{
				Algorithm<T>::Cancel(res, LastAction, ActionPos, Position);
			}
			else cout <<endl<< " ������ �������� "<<endl;
			break;
		}
		case 10:
		{
			flag = false;
		}
		}
	} while (flag);
}


template <typename T>
void Interface<T>::Menu(Queue<T>& q, string filename,string bfilename)
{
	system("cls");
	vector<T> LastAction;
	vector<int> ActionPos;
	vector<int> Position;
	Iterator<T> it;
	int v;
	bool flag = true;
	do
	{
		cout << endl << "������� ��������: " <<endl <<"1. ���������� ����" << endl<<"2. �������� ���� " <<endl
			<< "3. �������� ���� �����" << endl <<"4. ����� ���� �� ����������" << endl<< "5. �������������� ����" << endl<<"6. ���������� �����" << endl;
		cout <<"7.�������� ���� � ���� " << endl<<"8.������ ���� �� �����" <<endl<<"9.�������� � ���������������� ������" <<endl<<"10.������ ���������� ��������" << endl;
		cout << "11.����� �� ������ " << endl;
		v = InputInt(1, 11);
		cout << endl;
		switch (v)
		{
		case 1:
		{
			system("cls");
			cout << "���� ����������:" <<endl<< endl;
			T a;
			cin >> a;
			SetColor(2);
			Algorithm<T>::Add(a, q, LastAction, ActionPos, Position);
			SetColor(5);
			break;
		}
		case 2:
		{
			system("cls");
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);
			cout << endl;
			int num;
			cout << "������� ����� ����� ��� ��������: " << endl;
			cin >> num;
			Algorithm<T>::Delete_Element(num,q, LastAction, ActionPos, Position);
			break;
		}
		case 3:
		{
			system("cls");
			cout << endl;
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);
			cout << endl;
			break;
		}
		case 4:
		{
			system("cls");
			cout << endl;
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);
			cout << endl;
			T f;
			f.Find();
			Queue<T> res = Algorithm<T>::Search(q.begin(), q.end(), f);
			if (res.isEmpty())
			{
				cout << "������ �� �������" << endl;
			}
			else 
			{
				SetColor(2);
				res.HeadTable();
				SetColor(1);
				res.output();
				SetColor(5);
			}
			break;
		}
		case 5:
		{
			system("cls");
			cout << endl;
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);
			cout << endl;
			Algorithm<T>::update(q, LastAction, ActionPos, Position);
			system("cls");
			cout << endl;
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);
			cout << endl;
			break;
		}
		case 6:
		{
			system("cls");
			cout << "����������: �� �������� - 1, �� ����������� - 0: ";
			int s = InputInt(0, 1);
			cout << endl;
			if (s == 1)
			{
				Algorithm<T>::SortFromMax(q.begin(), q.end());
			}
			else Algorithm<T>::SortFromMin(q.begin(), q.end());
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);
			break;
		}
		case 7:
		{
			system("cls");
			if (exist_file(filename))
			{
				q.file_out1(filename);
			}
		}break;
		case 8:
		{
			system("cls");
			if (exist_file(filename))
			q.file_in(filename);
			SetColor(2);
			q.HeadTable();
			SetColor(1);
			q.output();
			SetColor(5);

		}break;
		case 9:
		{
			Interface<Reserve> ob;
			Queue<Reserve> reserv;
			ob.MenuForReserved(reserv, bfilename);
			break;
		}
		case 10:
		{
			if (LastAction.empty())
			{
				cout << "������ ��������";
			}
		    else Algorithm<T>::Cancel(q, LastAction, ActionPos, Position);
			break;
		}
		case 11:
		{
			flag = false;
		}
		}
	} while (flag);
}

template <typename T>
void Interface<T>::MenuForGuest(Queue<T>& q, string filename,string bfilename)
{
	system("cls");
	Iterator<T> it;
	int v;
	bool flag = true;
	do
	{
		cout << endl << "������� ��������: " << endl<<"1.�������� �����" <<endl<< "2. ����� ����� �� ����������" << endl
			<< "3. ���������� �����" << endl<<"4.������������� ��� " << endl<<"5. ����� �� ������" << endl;
			v = InputInt(1, 5);
			cout << endl;
			switch (v)
			{
			case 1:
			{
				q.deleteQueue();
				if (exist_file(filename))
					q.file_in(filename);
				SetColor(2);
				q.HeadTable();
				SetColor(1);
				q.output();
				SetColor(5);
				cout << endl;
				break;
			}
			case 2:
			{
				system("cls");
				cout << endl;
				SetColor(2);
				q.HeadTable();
				SetColor(1);
				q.output();
				SetColor(5);
				cout << endl;
				T f;
				f.Find();
				Queue<T> res = Algorithm<T>::Search(q.begin(), q.end(), f);
				SetColor(2);
				res.HeadTable();
				SetColor(1);
				res.output();
				SetColor(5);
				break;
			}
			case 3:
			{
				system("cls");
				cout << "����������: �� �������� - 1, �� ����������� - 0: ";
				int s = InputInt(0, 1);
				cout << endl;
				if (s == 1)
				{
					Algorithm<T>::SortFromMax(q.begin(), q.end());
				}else Algorithm<T>::SortFromMin(q.begin(), q.end());
				SetColor(2);
				q.HeadTable();
				SetColor(1);
				q.output();
				SetColor(5);
				break;
			}
			case 4:
			{
				system("cls");
				SetColor(2);
				q.HeadTable();
				SetColor(1);
				q.output();
				SetColor(5);
				Algorithm<T>::reserve_tour(q,filename,bfilename);
				break;
			}
			case 5:
			{
				flag = false;
			}
			}
			
	} while (flag);
}
template <typename T>
void Interface<T>::MainMenu()
{
	bool check = true;
	int pick;
	do
	{
		system("cls");
		SetColor(5);
		cout << "_____________________________________________________________________________________" << endl;
		cout << "*************************************************************************************" << endl;
		cout << "_____________________________________________________________________________________" << endl;
		cout << "|*|           ����� ���������� � ������������� �������� '������ �����'            |*|" << endl;
		cout << "|*|           �������� ������ ����������� � �������:                              |*|" << endl;
		cout << "|*|           1. ����� ��� �����                                                  |*|" << endl;
		cout << "|*|           2. ����� ��� �������������                                          |*|" << endl;
		cout << "|*|           3. ����� �� ������                                                  |*|" << endl;
		cout << "_____________________________________________________________________________________" << endl;
		cout << "*************************************************************************************" << endl;
		cout << "_____________________________________________________________________________________" << endl;
		pick = InputInt(1, 3);
		switch (pick)
		{
		case 1:
		{
			Interface<T>::menu(1);
			break;
		}
		case  2:
		{
			bool fl;
			fl = Algorithm<T>::authotization();
			if (fl)
			{
				Interface<T>::menu(2);
			}
			break;
		}
		case 3:
		{
			check = false;
		}
		}
	} while (check);

	return;
}