#include <iostream>
#include <iomanip>
using namespace std;

class array1
{
private:
	int* arr;                                              //��������� �� ������
	int size;                                              //������ �������

public:

	array1(int size)                                       //����������� � ����������
	{
		this->size = size;                                 //���������� �������� ���������� �������� �������
		arr = new int[size];                               //��������� ������
	}

	array1()                                               //����������� �� ���������
	{
		size = 0;                                          //��������� �������
		arr = nullptr;                                     //��������� ���������
	}

	~array1()                                               //����������
	{
		delete[] arr;                                       //�������� ������
	}
	
	array1(const array1& other)                             //����������� �����������
	{
		this->size = other.size;                            //�������� �������
		this->arr = new int[other.size];                    //��������� ������

		for (int i = 0; i < other.size; i++)                //���� �� ����������� ��������
		{
			this->arr[i] = other.arr[i];
		}
	}

	void input();                                           //����� ����� �������

	void output();                                          //����� ������ �������

	array1 concatenation(array1& my_arr2);                  //����� ����������� ��������
	
	//array1 operator +(const array1& other);                 //���������� ��������� +

	void operator +(array1& other);                 //���������� ��������� +
	//void operator +(const array1& arr1, const array1& arr2);
};  
