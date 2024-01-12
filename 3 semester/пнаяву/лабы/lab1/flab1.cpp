#include "hlab1.h"


void array1::input()                                 //����� ����� �������
{
	for (int i = 0; i < size; i++)
	{
		while ((cin >> arr[i]).fail())               //�������� �� ����
		{
			cout << "�������� ����. ���������" << endl;
			rewind(stdin);
			cin.clear();
		}
	}
}

void array1:: output()                                  //����� ������ �������
{
	for (int i = 0; i < size; i++)
		cout << setw(5)<< arr[i];
	cout << endl;
}




array1 array1::concatenation( array1& arr2)                  //����� ����������� ��������
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


//array1 array1:: operator +(const array1& other)         //���������� ���������
//{
//	int size1 = this->size;
//	int size2 = other.size;
//	int newsize = size1 + size2;                        //����������� ������
//	array1 arr3(newsize);                               //�������� ������� � ���������� ������ �� ������������ ������
//
//	for (int i = 0; i < size1; i++) arr3.arr[i] = arr[i]; //����������� ������� ������� � �����
//
//	int flag;
//	int l = size1;
//	for (int j = 0; j < size2; j++)                       //����������� ������� ������� � ��������� �� ����������
//	{
//		for (int k = 0; k < size1; k++)
//		{
//			if (arr3.arr[k] == other.arr[j])              //���� �������� ���������
//			{
//				flag = 0;
//				break;                                    //����� �� �����
//			}
//			else flag = 1;
//		}
//		if (flag == 1)                                    //���� ���������� �� ����
//		{
//			arr3.arr[l++] = other.arr[j];                 //������ ����� � ����� ������
//			arr3.size = l;                                //����� ������ �������
//		}
//	}
//	return arr3;
//}

void array1:: operator +( array1& other)         //���������� ���������
{
	int size1 = this->size;
	int size2 = other.size;
	int newsize = size1 + size2;                        //����������� ������
	array1 arr3(newsize);                              //�������� ������� � ���������� ������ �� ������������ ������

	for (int i = 0; i < size1; i++) arr3.arr[i] = arr[i]; //����������� ������� ������� � �����

	int flag;
	int l = size1;
	for (int j = 0; j < size2; j++)                       //����������� ������� ������� � ��������� �� ����������
	{
		for (int k = 0; k < size1; k++)
		{
			if (arr3.arr[k] == other.arr[j])              //���� �������� ���������
			{
				flag = 0;
				break;                                    //����� �� �����
			}
			else flag = 1;
		}
		if (flag == 1)                                    //���� ���������� �� ����
		{
			arr3.arr[l++] = other.arr[j];                 //������ ����� � ����� ������
			arr3.size = l;                                //����� ������ �������
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


