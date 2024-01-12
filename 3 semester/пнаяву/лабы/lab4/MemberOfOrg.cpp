#include "MemberOfOrg.h"

char* MemberOfOrg:: getNameOfOrganization() { return NameOfOrganization; }
int MemberOfOrg:: getYearOfEnter() { return YearOfEnter; }
char** MemberOfOrg:: getAutobiography() { return (char**)Autobiography; }

void MemberOfOrg:: setNameOfOrganization(char* a) { strcpy_s(this->NameOfOrganization, 20, a); }
void MemberOfOrg:: setYearOfEnter(int a) { this->YearOfEnter = a; }
void MemberOfOrg:: setAutobiography(char** a)
{
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], 20, a[i]);
	}
}

MemberOfOrg MemberOfOrg:: operator=(const MemberOfOrg& obj)
{
	*((Man*)this) = (Man&)obj;
	this->YearOfEnter = obj.YearOfEnter;
	strcpy_s(this->NameOfOrganization, 20, obj.NameOfOrganization);
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], 20, obj.Autobiography[i]);
	}
	return *this;
}

istream& operator>>(istream& is, MemberOfOrg& obj)
{
	rewind(stdin);
	is >> (Man&)obj;
	cout << "������� �������� �����������: ";
	is >> obj.NameOfOrganization;
	cout << "������� ��� ����������: ";
	is >> obj.YearOfEnter;
	cout << "������� �������������: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.Autobiography[i];
	}
	return is;
}

ostream& operator<<(ostream& out, MemberOfOrg& obj)
{
	
	out << (Man&)obj;
	out.setf(ios::left);
	out << setw(20) << obj.NameOfOrganization << setw(20) << obj.YearOfEnter;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.Autobiography[i] << setw(20) << endl;
			continue;
		}
		out << setw(100) << " " << obj.Autobiography[i] << setw(20) << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void MemberOfOrg:: HeadOfSheet()
{
	
	cout.setf(ios::left);
	cout << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������";
	cout << setw(15) << "����.�����." << setw(15) << "��� ����������" << setw(15) << "�������������"<<endl;
	cout.unsetf(ios::left);
}