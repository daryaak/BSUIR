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
				throw InputExeption(111, "Ошибка формата данных", "Введите целое число");
			if (Temp > max || Temp < min) throw InputExeption(112, "Ошибка выхода за границы", "Введите число в указанном диапазоне");
			return Temp;
		}
		catch (InputExeption obj)
		{
			cin.clear();
			cin.ignore(Len, '\n');
			obj.ShowError();
			cout << "Введите целое число в границах от " << min << " до " << max << endl;
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
			if (cin.fail() || cin.peek() != '\n') throw InputExeption(111, "Ошибка формата данных", "Введите вещественное число");
			if (Temp > max || Temp < min) throw InputExeption(112, "Ошибка выхода за границы", "Введите число в указанном диапазоне");
			return Temp;
		}

		catch (InputExeption obj)
		{
			cin.clear();
			cin.ignore(Len, '\n');
			obj.ShowError();
			cout << "Введите целое число в границах от " << min << " до " << max << endl;
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
			if (cin.fail())throw InputExeption(121, "Ошибка выхода за границы", "Введите строку меньше 80 символов ");
			for (int i = 0; i < strlen(Temp); i++)
			{
				if ((Temp[i] < 'А' or Temp[i] > 'Я') and (Temp[i] < 'а' or Temp[i] > 'я') and Temp[i] != ' ' and Temp[i] != ',' and Temp[i] != '.' and Temp[i] != '-')
					throw InputExeption(122, "Ошибка ввода символьных данных", "Введите строку кириллицей");
			}
			return Temp;
		}
		catch (bad_alloc ex)
		{
			cout << "Ошибка выделения памяти под строку на " << Len << "символов" << std::endl;
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
				throw InputExeption(121, "Ошибка выхода за границы", "Введите строку в 11 символов ");
				if (str[2] != '.' || str[5] != '.')
					throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				if(str[0]<'0'||str[0]>'3') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				if (str[0] == '3')
				{
					if (str[1] < '0'||str[1]>'1') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				}
				else
				{
					if (str[1] < '1' || str[1]>'9') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				}
				if(str[3]<'0'||str[3]>'1') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				if (str[3] == '1')
				{
					if(str[4]<'1'||str[4]>'2') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				}
				else 
				{ if (str[4] < '0' || str[4]>'9') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате"); }
				if(str[6]!='2'&&str[6]!='0'&&str[6]!='2') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
				if(str[9]<'2'||str[9]>'9') throw InputExeption(122, "Ошибка ввода даты", "Введите в правильном формате");
			return str;
		}
		catch (bad_alloc ex)
		{
			cout << "Ошибка выделения памяти под строку на " << Len << "символов" << endl;
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
			if (strlen(str) != 13) throw InputExeption(121, "Ошибка выхода за границы", "Введите номер телефона в 13 символов ");
			if (str[0]!='+')
				throw InputExeption(122, "Ошибка ввода номера телефона", "Введите в правильном формате");
			if(str[1]!='3') throw InputExeption(122, "Ошибка ввода номера телефона", "Введите в правильном формате");
			if (str[2]!='7') throw InputExeption(122, "Ошибка ввода номера телефона", "Введите в правильном формате");
			if(str[3]!='5') throw InputExeption(122, "Ошибка ввода номера телефона", "Введите в правильном формате");
			for (int i = 4; i < 13; i++)
			{
				if(str[i]<'0'||str[i]>'9') throw InputExeption(122, "Ошибка ввода номера телефона", "Введите в правильном формате");
			}
			return str;
		}
		catch (bad_alloc ex)
		{
			cout << "Ошибка выделения памяти под строку на " << Len << "символов" << endl;
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
	cout << "Код ошибки:" << Code << endl;
	cout << Type << endl;
	cout << Message << endl;
}