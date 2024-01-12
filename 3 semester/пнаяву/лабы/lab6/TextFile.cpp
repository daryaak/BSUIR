#include "TextFile.h"

template<class T>
TextFile<T>::TextFile(string _name) : File(_name) {}

template<class T>
TextFile<T>::~TextFile() {
	file_o.close();
	file_i.close();
}

template <typename T>
bool TextFile<T>::openReadFile()
{
	file_i.open(file_name);
	return true;
}

template <typename T>
bool TextFile<T>::openWriteFile()
{
	file_o.open(file_name, ios_base::out );
	file_o << "\n";
	return true;
}

template<typename T>
bool TextFile<T>::feof()
{
	if (!file_i.eof())
		return false;
	else
		return true;
}

template <typename T>
void TextFile<T>::readFile(T& temp)
{
	file_i >> temp;
}

template <typename T>
void TextFile<T>::writeFile(T& temp)
{
	file_o << temp;
}

