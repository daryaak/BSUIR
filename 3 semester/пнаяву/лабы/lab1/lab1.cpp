#include "hlab1.h"

int main()
{
	rewind(stdin);
	setlocale(LC_ALL, "ru");
	system("cls");
	int repeat;                                                //���������� ��� ������������ ���������
	do
	{
		int size1, size2;
		cout << "������� ������ ������� �������" << endl;
		cin >> size1;
		array1 arr1(size1);                                     //���������� ������� �������
		cout << "������� ������ ������" << endl;           
		arr1.input();                                           //���� ������� �������
		cout << "������ ������:" << endl;
		arr1.output();                                          //����� ������� �������

		cout << "������� ������ ������� �������" << endl;
		cin >> size2;
		array1 arr2(size2);                                     //���������� ������� �������
		cout << "������� ������ ������" << endl;
		arr2.input();                                           //���� ������� �������
		cout << "������ ������:" << endl;
		arr2.output();                                          //����� ������� �������
		cout << "��������� ����������� ���� ��������" << endl;
		//array1 result = arr1.concatenation(arr2);               //����������� � ������� ���������� ������
		//array1 result = arr1 + arr2+ arr1 + arr2+ arr1 + arr2;                          //����������� � ������� ���������� ���������

		arr1 + arr2;
		arr2.output();
		arr1 + arr2 + arr1;
		

		cout << "������� ����������?1-��" << endl;              //������ �� ������ ���������
		cin >> repeat;
		if (repeat != 1)return 0;
	} while (repeat == 1);
}