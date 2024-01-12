#include "InputExeption.h"

int InputInt(int min, int max)
{
	int Temp = 0;
	while (true)
	{
		try
		{
			cin >> Temp;
			if (cin.fail() || cin.peek() != '\n')
				throw InputExeption(111, "������ ������� ������", "������� ����� �����");
			if (Temp > max || Temp < min) throw InputExeption(112, "������ ������ �� �������", "������� ����� � ��������� ���������");
			return Temp;
		}
		catch (InputExeption obj)
		{
			cin.clear();
			cin.ignore(Len, '\n');
			obj.ShowError();
			cout << "������� ����� ����� � �������� �� " << min << " �� " << max << endl;
		}
	}

}
double InputDouble(int min, int max)
{
	int Temp = 0;
	while (true)
	{
		try
		{
			cin >> Temp;
			if (cin.fail() || cin.peek() != '\n') throw InputExeption(111, "������ ������� ������", "������� ������������ �����");
			if (Temp > max || Temp < min) throw InputExeption(112, "������ ������ �� �������", "������� ����� � ��������� ���������");
			return Temp;
		}

		catch (InputExeption obj)
		{
			cin.clear();
			cin.ignore(Len, '\n');
			obj.ShowError();
			cout << "������� ����� ����� � �������� �� " << min << " �� " << max << endl;
		}
	}
}
char* InputRussian()
{

	while (true)
	{
		try
		{
			char* Temp = new char[Len];
			rewind(stdin);
			cin.getline(Temp, Len);
			if (cin.fail())throw InputExeption(121, "������ ������ �� �������", "������� ������ ������ 80 �������� ");
			for (int i = 0; i < strlen(Temp); i++)
			{
				if ((Temp[i] < '�' or Temp[i] > '�') and (Temp[i] < '�' or Temp[i] > '�') and Temp[i] != ' ' and Temp[i] != ',' and Temp[i] != '.' and Temp[i] != '-')
					throw InputExeption(122, "������ ����� ���������� ������", "������� ������ ����������");
			}
			return Temp;
		}
		catch (bad_alloc ex)
		{
			cout << "������ ��������� ������ ��� ������ �� " << Len << "��������" << std::endl;
			exit(1);
		}
		catch (InputExeption obj)
		{
			cin.clear();
			obj.ShowError();
		}
	}
}
char* InputDate()
{
	char* str = new char[11];
	while (true)
	{
		rewind(stdin);
		try
		{
			cin.clear();
			cin.getline(str, Len);
			if (strlen(str) != 10)
				throw InputExeption(121, "������ ������ �� �������", "������� ������ � 11 �������� ");
				if (str[2] != '.' || str[5] != '.')
					throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				if(str[0]<'0'||str[0]>'3') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				if (str[0] == '3')
				{
					if (str[1] < '0'||str[1]>'1') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				}
				else
				{
					if (str[1] < '1' || str[1]>'9') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				}
				if(str[3]<'0'||str[3]>'1') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				if (str[3] == '1')
				{
					if(str[4]<'1'||str[4]>'2') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				}
				else 
				{ if (str[4] < '0' || str[4]>'9') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������"); }
				if(str[6]!='2'&&str[6]!='0'&&str[6]!='2') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
				if(str[9]<'2'||str[9]>'9') throw InputExeption(122, "������ ����� ����", "������� � ���������� �������");
			return str;
		}
		catch (bad_alloc ex)
		{
			cout << "������ ��������� ������ ��� ������ �� " << Len << "��������" << endl;
			exit(1);
		}
		catch (InputExeption obj)
		{
			cin.clear();
			obj.ShowError();
		}
	}
}


char* InputPhone()
{
	while (true)
	{
		rewind(stdin);
		try
		{
			char* str = new char[Len];
			cin.clear();
			cin.getline(str, Len);
			if (strlen(str) != 13) throw InputExeption(121, "������ ������ �� �������", "������� ����� �������� � 13 �������� ");
			if (str[0]!='+')
				throw InputExeption(122, "������ ����� ������ ��������", "������� � ���������� �������");
			if(str[1]!='3') throw InputExeption(122, "������ ����� ������ ��������", "������� � ���������� �������");
			if (str[2]!='7') throw InputExeption(122, "������ ����� ������ ��������", "������� � ���������� �������");
			if(str[3]!='5') throw InputExeption(122, "������ ����� ������ ��������", "������� � ���������� �������");
			for (int i = 4; i < 13; i++)
			{
				if(str[i]<'0'||str[i]>'9') throw InputExeption(122, "������ ����� ������ ��������", "������� � ���������� �������");
			}
			return str;
		}
		catch (bad_alloc ex)
		{
			cout << "������ ��������� ������ ��� ������ �� " << Len << "��������" << endl;
			exit(1);
		}
		catch (InputExeption obj)
		{
			cin.clear();
			obj.ShowError();
		}
	}

}

void InputExeption::ShowError()
{
	cout << "��� ������:" << Code << endl;
	cout << Type << endl;
	cout << Message << endl;
}