#include "BinFile.h"

template<class T>
BinFile<T>::BinFile(string _name) : File(_name) {}

template<class T>
BinFile<T>::~BinFile() {
	ft.close();
}

template<typename T>
bool BinFile<T>::is_open()
{
	if (!ft.is_open())
		return false;
	else
		return true;
}

template<typename T>
bool BinFile<T>::feof()
{
	if (!ft.eof())
		return false;
	else
		return true;
}

template <typename T>
bool BinFile<T>::openReadFile()
{
	ft.open(file_name, ios::in | ios::binary);
	if (!ft.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
		return false;
	}
	else
		return true;
}

template <typename T>
bool BinFile<T>::openWriteFile()
{
	ft.open(file_name, ios::out | ios::binary);
	if (!ft.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
		return false;
	}
	else
		return true;
}

template <typename T>
void BinFile<T>::readFile(T& temp)
{
	ft >> temp;
}

template <typename T>
void BinFile<T>::writeFile(T& temp)
{
	ft << temp;
}

