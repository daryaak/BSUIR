#include"Man.h"
#include "Professor.h"
#include "MemberOfOrg.h"
#include "ProfMember.h"
#include<Windows.h>
#include "conio.h"

int main()
{	
	int repeat;
	do
	{
		system("Color 7D");
		rewind(stdin);
		system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "������� ���������� ������ �����������: ";
	int kol;                                                                   //���������� ������ �����������
	cin >> kol;
	MemberOfOrg* b;
	b=  new MemberOfOrg[kol];
	rewind(stdin);
	cout << "������� ���������� � ������ �����������" << endl;
	for (int i = 0; i < kol; i++)                                              //���� ������ �����������
	{
		cin >> b[i];
	}
	b[0].HeadOfSheet();                                                        //����� ����� �������
	for (int i = 0; i < kol; i++)                                              //����� ������ �����������
	{
		cout << b[i];
	}

	//cout << "������� ���������� � �����������-������ ����������� " << endl;
	//ProfMember c;                                                              //������ ������ ���������-���� �����������
	//cin >> c;                                                                  //���� �������
	//c.HeadOfSheet();                                                           //����� �������
	//cout << c;                                                                 //����� �������
	//ProfMember s;                                                              //������ ������ ���������-���� ���
	//s = c;                                                                     //�������� ������������
	//cout << "������� ����� �������: ";
	//char line[20];                                                             //����� �������
	//cin >> line;
	//s.setSurname(line);                                                        //��������� ����� �������
	//cout << s;                                                                 //����� ������� � ����� ��������

	delete[] b;                                                                //������������ ������

	cout << "������� ����������?1-��" << endl;              //������ �� ������ ���������
	cin >> repeat;
	if (repeat != 1)
	{
		system("pause");
		return 0;
	}
	} while (repeat == 1);
}