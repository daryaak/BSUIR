#include "Algorithm.h"

inline void SetColor(int text);

void SetColor(int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((14 << 4) | text));
}

template<typename T>
bool Algorithm<T>::authotization()
{
	 Queue<Admin> admins;
	 admins.file_in("admins.txt");
	 char BUFFER[80], c;
	 char username[80];
     char password[80];
	 rewind(stdin);
	 cout << "������� �����: ";
	 cin >> username;
	 rewind(stdin);
	 cout << "������� ������: ";
	 int i = 0;
	 while ((c = _getch()) != '\r') {
		 _putch('*');
		 BUFFER[i] = c;
		 i++;
	 }
	 BUFFER[i] = '\0';
	 strcpy_s(password, L, BUFFER);
	 cout << endl;
	 for (int i = 0; i < admins.size(); i++) {
		 if ((strcmp(admins[i].GetUsername(),username)==0) && (strcmp(admins[i].GetPassword(),password)==0))
		 {
			 return true;
		 }
	 }
	 cout << "�������� ������������ ��� ������!" << endl;
	 return false;

}

template <typename T>
void Algorithm<T>::SortFromMin(Iterator<T> Begin, Iterator<T> End)
{   
	T Min, Temp;
	Min = Temp = (*Begin).PickField();
	Iterator<T>  minimal;
	Iterator<T> j;
	for(; Begin != End;++Begin)
	{
		minimal = Begin;
		j = Begin;
		for(;j!=End;++j)
		{
			Min.ReplaceField(*minimal);
			Temp.ReplaceField(*j);
			if (Temp < Min)
				minimal = j;
		}
		if (minimal != Begin)
		{
			T tmp = *minimal;
			*minimal = *Begin;
			*Begin = tmp;
		}
	}
};

template <typename T>
void Algorithm<T>::SortFromMax(Iterator<T> Begin, Iterator<T> End)
{
	T Min, Temp;
	Min = Temp = (*Begin).PickField();
	Iterator<T>  minimal;
	Iterator<T> j;
	for (; Begin != End; ++Begin)
	{
		minimal = Begin;
		j = Begin;
		for (; j != End; ++j)
		{
			Min.ReplaceField(*minimal);
			Temp.ReplaceField(*j);
			if (Temp > Min)
				minimal = j;
		}
		if (minimal != Begin)
		{
			T tmp = *minimal;
			*minimal = *Begin;
			*Begin = tmp;
		}
	}
};


template <class T>
Queue<T> Algorithm<T>::Search(Iterator<T> Begin, Iterator<T> End, T Temp)
{
	Queue<T> Queue;
	++End;
	for (; Begin != End; ++Begin)
	{
		if (*Begin == Temp) Queue.pushTail(*Begin);
	}
	return Queue;
}


template <class T>
void Algorithm<T>::Add(T Elem, Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position)
{
	obj.pushHead(Elem);
	LastAction.push_back(Elem);
	Position.insert(Position.end(), obj.size());
	ActionPos.push_back(1);
	return;
}

template <class T>
void Algorithm<T>::Delete_Element(int num,Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position)
{
		T temp = obj.pop(num);
		LastAction.push_back(temp);
		ActionPos.push_back(2);
		Position.push_back(num);
}

template <class T>
void Algorithm<T>:: reserve_tour(Queue<T>& q,string filename, string bfilename)
{
	Queue<Reserve> queue;
	cout << "������� ����� ���� ��� �����: ";
	int num = InputInt(1, q.size());
	cout << endl;
	char* sur = new char[LEN];
	char* phone = new char[LEN];
	int n;
	cout << "������� ���� �������: ";
	sur = InputRussian();
	cout << "������� ��� ����� ��������: ";
	rewind(stdin);
	phone = InputPhone();
	cout << "������� ���������� �������: ";
	n = InputInt(1, MAX_PLACES);
	if (n > q[num - 1].GetAmountOfPlaces())
	{
		cout << "��� ������ ���������� ��������� ����";
		return;
	}else 
	{
		Reserve obj(sur, phone, q[num - 1].GetID(), n, q[num - 1].GetPrice() * n);
		cout << "��������� ����: " << obj.GetFinalPrice() << endl;
		cout << "�� �������� � ������� �������������? ������� 1 - ��, 0 - ���" << endl;
		int k = InputInt(0, 1);
		if (k == 1)
		{
			
			queue.pushHead(obj);
			if (exist_file(bfilename))
				queue.file_out2(bfilename);
			q[num - 1].SetAmountOfPlaces(q[num - 1].GetAmountOfPlaces() - n);
			q.file_out1(filename);
			cout << "��� ������� ������������!" << endl;
		}
		
	}
}


template<class T>
void Algorithm<T>::Cancel(Queue<T>& obj, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position) {
	switch (ActionPos.back()) {
	case 1: 
	{
		obj.pop(Position.back());
		ActionPos.pop_back();
		LastAction.pop_back();
		Position.pop_back();
		break;
	}
	case 2: 
	{
		obj.push(LastAction.back(), Position.back());
		Position.pop_back();
		ActionPos.pop_back();
		LastAction.pop_back();
		break;
	}
	case 3:
	{
		obj[Position.back() - 1] = LastAction.back();
		Position.pop_back();
		ActionPos.pop_back();
		LastAction.pop_back();
		break;
	}
	}
}

template<class T>
void Algorithm<T>::update(Queue<T>& q, vector<T>& LastAction, vector<int>& ActionPos, vector<int>& Position)
{
	if (q.isEmpty())
	{
		cout << "������� �����" << endl;
		return ;
	}
	cout << endl;
	cout << "������� ����� ����������� �������� : ";
	int tempNum = InputInt(1,q.size());
	LastAction.push_back(q[tempNum - 1]);
	ActionPos.push_back(3);
	Position.push_back(tempNum);
	q[tempNum - 1].Change();
	SetColor(2);
	q.HeadTable();
	SetColor(1);
	q.output();
	SetColor(5);
}

