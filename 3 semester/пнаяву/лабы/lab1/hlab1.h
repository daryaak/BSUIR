#include <iostream>
#include <iomanip>
using namespace std;

class array1
{
private:
	int* arr;                                              //указатель на массив
	int size;                                              //размер массива

public:

	array1(int size)                                       //конструктор с параметром
	{
		this->size = size;                                 //переданный параметр становится размером массива
		arr = new int[size];                               //выделение памяти
	}

	array1()                                               //конструктор по умолчанию
	{
		size = 0;                                          //зануление размера
		arr = nullptr;                                     //зануление указателя
	}

	~array1()                                               //деструктор
	{
		delete[] arr;                                       //очищение памяти
	}
	
	array1(const array1& other)                             //конструктор копирования
	{
		this->size = other.size;                            //передача размера
		this->arr = new int[other.size];                    //выделение памяти

		for (int i = 0; i < other.size; i++)                //цикл по копированию массивов
		{
			this->arr[i] = other.arr[i];
		}
	}

	void input();                                           //метод ввода массива

	void output();                                          //метод вывода массива

	array1 concatenation(array1& my_arr2);                  //метод объединения массивов
	
	//array1 operator +(const array1& other);                 //перегрузка оператора +

	void operator +(array1& other);                 //перегрузка оператора +
	//void operator +(const array1& arr1, const array1& arr2);
};  
