#include "ProfMember.h"

int ProfMember:: getContributionPerMonth() { return ContributionPerMonth; }
void ProfMember:: setContributionPerMonth(int temp) { this->ContributionPerMonth = temp; }

ProfMember ProfMember:: operator=(ProfMember& obj)
{
	*((Professor*)this) = (Professor&)obj;
	*((MemberOfOrg*)this) = (MemberOfOrg&)obj;
	this->ContributionPerMonth = obj.ContributionPerMonth;
	return *this;
}

istream& operator>>(istream& is, ProfMember& obj)
{
	rewind(stdin);
	is >> (Man&)obj;
	cout << "������� ���������: ";
	is >> obj.Occupation;
	cout << "������� �������������: ";
	is >> obj.Specialization;
	cout << "������� ������� ������: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.ScienceWork[i];
	}
	cout << "������� �������� �����������: ";
	is >> obj.NameOfOrganization;
	cout << "������� ��� ����������: ";
	is >> obj.YearOfEnter;
	cout << "������� �������������: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.Autobiography[i];
	}
	cout << "������� ����������� �����: ";
	is >> obj.ContributionPerMonth;
	return is;
}

ostream& operator<<(ostream& out, ProfMember& obj)
{
	
	out << (Man&)obj;
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << setw(15) << obj.Specialization;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << setw(15) << obj.NameOfOrganization << setw(15) << obj.YearOfEnter << setw(20) << obj.Autobiography[i] << setw(15) << obj.ContributionPerMonth << endl;
			continue;
		}
		out << setw(90) << " " << obj.ScienceWork[i];
		out << setw(49) << " " << obj.Autobiography[i] << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void ProfMember:: HeadOfSheet()
{
	
	cout.setf(ios::left);
	cout << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������";
	cout << setw(15) << "���������" << setw(15) << "�������������" << setw(20) << "������� ������";
	cout << setw(15) << "����.�����." << setw(15) << "��� ����������" << setw(20) << "�������������" <<setw(20)<<"������.�����" << endl;
	cout.unsetf(ios::left);
}