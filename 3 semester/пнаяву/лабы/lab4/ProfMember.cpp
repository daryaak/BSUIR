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
	cout << "Введите должность: ";
	is >> obj.Occupation;
	cout << "Введите специализацию: ";
	is >> obj.Specialization;
	cout << "Введите научные работы: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.ScienceWork[i];
	}
	cout << "Введите название организации: ";
	is >> obj.NameOfOrganization;
	cout << "Введите год вступления: ";
	is >> obj.YearOfEnter;
	cout << "Введите автобиографию: ";
	for (int i = 0; i < 3; i++)
	{
		is >> obj.Autobiography[i];
	}
	cout << "Введите ежемесячный взнос: ";
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
	cout << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(15) << "Отчество" << setw(15) << "Год рождения";
	cout << setw(15) << "Должность" << setw(15) << "Специализация" << setw(20) << "Научная работа";
	cout << setw(15) << "Назв.орган." << setw(15) << "Год вступления" << setw(20) << "Автобиография" <<setw(20)<<"Ежемес.вклад" << endl;
	cout.unsetf(ios::left);
}