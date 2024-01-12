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
char* InputEnglish()
{
	while (true)
	{
		try
		{
			char* Temp = new char[Len];
			rewind(stdin);
			cin.clear();
			cin.getline(Temp, Len);
			if (cin.fail())throw InputExeption(121, "Ошибка выхода за границы", "Введите строку меньше 80 символов ");
			for (int i = 0; i < strlen(Temp); i++)
			{
				if ((Temp[i] < 'A' or Temp[i] > 'Z') and (Temp[i] < 'a' or Temp[i] > 'z') and Temp[i] != ' ' and Temp[i] != ',' and Temp[i] != '.' and Temp[i] != '-')
					throw InputExeption(122, "Ошибка ввода символьных данных", "Введите строку латиницей");
			}
			return Temp;
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