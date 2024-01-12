#include "hlab1.h"


void array1::input()                                 //метод ввода массива
{
	for (int i = 0; i < size; i++)
	{
		while ((cin >> arr[i]).fail())               //проверка на ввод
		{
			cout << "Неверный ввод. Повторите" << endl;
			rewind(stdin);
			cin.clear();
		}
	}
}

void array1:: output()                                  //метод вывода массива
{
	for (int i = 0; i < size; i++)
		cout << setw(5)<< arr[i];
	cout << endl;
}




array1 array1::concatenation( array1& arr2)                  //метод объединения массивов
{
	int size1 = this->size;
	int size2 = arr2.size;
	int newsize = size1 + size2;
	array1 arr3(newsize);
	
	for (int i = 0; i < size1; i++) arr3.arr[i] = arr[i];

	int flag;
	int l = size1;
	for (int j = 0; j < size2; j++)
	{
		for (int k = 0; k < size1; k++)
		{
			if (arr3.arr[k] == arr2.arr[j])
			{
				flag = 0;
				break;
			}
			else flag = 1;
		}
		if (flag == 1)
		{
			arr3.arr[l++] = arr2.arr[j];
			arr3.size = l;
		}
	}
	return arr3;
}


//array1 array1:: operator +(const array1& other)         //перегрузка оператора
//{
//	int size1 = this->size;
//	int size2 = other.size;
//	int newsize = size1 + size2;                        //макимальный размер
//	array1 arr3(newsize);                               //создание объекта с выделением памяти на максимальный размер
//
//	for (int i = 0; i < size1; i++) arr3.arr[i] = arr[i]; //копирование первого массива в новый
//
//	int flag;
//	int l = size1;
//	for (int j = 0; j < size2; j++)                       //копирование второго массива с проверкой на повторение
//	{
//		for (int k = 0; k < size1; k++)
//		{
//			if (arr3.arr[k] == other.arr[j])              //если элементы совпадают
//			{
//				flag = 0;
//				break;                                    //выход из цикла
//			}
//			else flag = 1;
//		}
//		if (flag == 1)                                    //если повторения не было
//		{
//			arr3.arr[l++] = other.arr[j];                 //запись числа в новый массив
//			arr3.size = l;                                //новый размер массива
//		}
//	}
//	return arr3;
//}

void array1:: operator +( array1& other)         //перегрузка оператора
{
	int size1 = this->size;
	int size2 = other.size;
	int newsize = size1 + size2;                        //макимальный размер
	array1 arr3(newsize);                              //создание объекта с выделением памяти на максимальный размер

	for (int i = 0; i < size1; i++) arr3.arr[i] = arr[i]; //копирование первого массива в новый

	int flag;
	int l = size1;
	for (int j = 0; j < size2; j++)                       //копирование второго массива с проверкой на повторение
	{
		for (int k = 0; k < size1; k++)
		{
			if (arr3.arr[k] == other.arr[j])              //если элементы совпадают
			{
				flag = 0;
				break;                                    //выход из цикла
			}
			else flag = 1;
		}
		if (flag == 1)                                    //если повторения не было
		{
			arr3.arr[l++] = other.arr[j];                 //запись числа в новый массив
			arr3.size = l;                                //новый размер массива
		}
	}
	other.arr = (int*)realloc((other.arr),( l * sizeof(int)));
	other.size = arr3.size;
	for (int k = 0; k < l; k++) other.arr[k] = arr3.arr[k];
	//other.output();
	
}



//void array1:: operator +(const array1& arr1, const array1& arr2)
//{
//
//	int size1 = arr1.size;
//	int size2 = arr2.size;
//	int newsize = size1 + size2;
//	array1 arr3(newsize);
//
//	for (int i = 0; i < size1; i++) arr3.arr[i] = arr[i];
//
//	int flag;
//	int l = size1;
//	for (int j = 0; j < size2; j++)
//	{
//		for (int k = 0; k < size1; k++)
//		{
//			if (arr3.arr[k] == other.arr[j])
//			{
//				flag = 0;
//				break;
//			}
//			else flag = 1;
//		}
//		if (flag == 1)
//		{
//			arr3.arr[l++] = other.arr[j];
//			arr3.size = l;
//		}
//	}
//
//}


