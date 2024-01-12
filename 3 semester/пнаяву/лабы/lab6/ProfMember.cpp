#include "ProfMember.h"


double ProfMember::getContributionPerMonth() { return ContributionPerMonth; }
void ProfMember::setContributionPerMonth(int temp) { this->ContributionPerMonth = temp; }

ProfMember ProfMember:: operator=(ProfMember& obj)
{
	*((Professor*)this) = (Professor&)obj;
	*((MemberOfOrg*)this) = (MemberOfOrg&)obj;
	this->ContributionPerMonth = obj.ContributionPerMonth;
	return *this;
}

bool ProfMember:: operator==(const ProfMember& obj)
{
	if (!(*((Professor*)this) == (Professor&)obj)) return false;
	if (!(*((MemberOfOrg*)this) == (MemberOfOrg&)obj)) return false;
	


	if (obj.ContributionPerMonth != 0)
	{
		if (ContributionPerMonth != obj.ContributionPerMonth) return false;
	}


	return true;
}

istream& operator>>(istream& is, ProfMember& obj)
{
	rewind(stdin);
	is >> dynamic_cast<Man&>(obj);
	std::cout << "������� ���������: ";
	rewind(stdin);
	char* tmp = InputRussian();
	strcpy_s(obj.Occupation, LEN, tmp);

	std::cout << "������� �������������: ";
	rewind(stdin);
	tmp = InputRussian();
	strcpy_s(obj.Specialization, LEN, tmp);

	std::cout << "������� ������� ������: ";
	for (int i = 0; i < 3; i++)
	{
		rewind(stdin);
		tmp = InputRussian();
		strcpy_s(obj.ScienceWork[i], LEN, tmp);
	}
	std::cout << "������� �������� �����������: ";
	rewind(stdin);
	tmp = InputRussian();
	strcpy_s(obj.NameOfOrganization, LEN, tmp);
	std::cout << "������� ��� ����������: ";
	rewind(stdin);
	obj.YearOfEnter = InputInt(1900, 2022);
	std::cout << "������� �������������: ";
	for (int i = 0; i < 3; i++)
	{
		rewind(stdin);
		tmp = InputRussian();
		strcpy_s(obj.Autobiography[i], LEN, tmp);
	}
	delete tmp;
	cout << "������� ����������� �����: ";
	rewind(stdin);
	obj.ContributionPerMonth = InputDouble(-1, 10000);
	return is;
}

ifstream& operator>>(ifstream& in, ProfMember& obj)
{
	in >> dynamic_cast<Man&>(obj);
	in.ignore(80, '|');
	in.getline(obj.Occupation, 80, '|');
	//in.clear();
	in.getline(obj.Specialization, 80, '|');
	//in.clear();
	in.getline(obj.NameOfOrganization, 80, '|');
	//in.clear();
	in >> obj.YearOfEnter;
	in >> obj.ContributionPerMonth;
	in.ignore(80, '|');
	for (int i = 0; i < 3; i++)
	{
		if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.ScienceWork[i], 80, '|');
		//if (i != 2)in.clear();
		//if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.Autobiography[i], 80, '|');
		//if (i != 2)in.clear();
	}
	in.unsetf(ios::left);
	return in;
}

fstream& operator<<(fstream& in, ProfMember& ob)
{
	in << dynamic_cast<Man&>(ob);
	in.write(reinterpret_cast<char*> (&ob.Occupation), sizeof(ob.Occupation));
	in.write(reinterpret_cast<char*> (&ob.Specialization), sizeof(ob.Specialization));
	in.write(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	in.write(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	in.write(reinterpret_cast<char*> (&ob.ContributionPerMonth), sizeof(ob.ContributionPerMonth));
	for (int i = 0; i < 3; i++)
	{
		in.write(reinterpret_cast<char*> (&ob.ScienceWork[i]), sizeof(ob.ScienceWork[i]));
		in.write(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}
	return in;
}

fstream& operator>>(fstream& out, ProfMember& ob)
{
	out >> dynamic_cast<Man&>(ob);
	out.read(reinterpret_cast<char*> (&ob.Occupation), sizeof(ob.Occupation));
	out.read(reinterpret_cast<char*> (&ob.Specialization), sizeof(ob.Specialization));
	out.read(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	out.read(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	out.read(reinterpret_cast<char*> (&ob.ContributionPerMonth), sizeof(ob.ContributionPerMonth));
	for (int i = 0; i < 3; i++)
	{
		out.read(reinterpret_cast<char*> (&ob.ScienceWork[i]), sizeof(ob.ScienceWork[i]));
		out.read(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}
	return out;
}

ostream& operator<<(ostream& out, const ProfMember& obj)
{
	out << static_cast<const Man&>(obj);
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << setw(15) << obj.Specialization;
	out << setw(15) << obj.NameOfOrganization << setw(15) << obj.YearOfEnter << setw(15) << obj.ContributionPerMonth;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << setw(20) << obj.Autobiography[i] << endl;
		}
		else out << setw(140) << " " << setw(20) << obj.ScienceWork[i] << setw(20) << obj.Autobiography[i] << endl;
	}
	out.unsetf(ios::left);
	return out;
}

ofstream& operator<<(ofstream& out, ProfMember& obj)
{
	out << dynamic_cast<Man&>(obj);
	out.setf(ios::left);
	out << setw(15) << obj.Occupation << '|' << setw(15) << obj.Specialization << '|';
	out << setw(15) << obj.NameOfOrganization << '|' << setw(15) << obj.YearOfEnter << setw(15) << obj.ContributionPerMonth << '|';
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.ScienceWork[i] << '|' << setw(20) << obj.Autobiography[i] << '|' << endl;
		}
		else out << setw(142) << " " << '|' << setw(20) << obj.ScienceWork[i] << '|' << setw(20) << obj.Autobiography[i] << '|' << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void ProfMember::HeadOfSheet()
{
	cout.setf(ios::left);
	cout << setw(5) << "�" << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������";
	cout << setw(15) << "���������" << setw(15) << "�������������";
	cout << setw(15) << "����.�����." << setw(15) << "��� ����������" << setw(15) << "������.�����" << setw(15) << "������� ������" << setw(20) << "�������������" << endl;
	cout.unsetf(ios::left);
}

void ProfMember::Find()
{
	int check;
	char* tmp;
	do
	{
		rewind(stdin);
		cout << "�������� �������� ��� ������" << endl << "1.�������" << endl << "2.���" << endl << "3.��������" << endl << "4.��� ��������" << endl;
		cout << "5.���������" << endl << "6.�������������" << endl << "7.������� ������" << endl;
		cout << "8.�������� ����������� " << endl << "9.��� ����������" << endl << "10.�������������" << endl;
		cout << "11.����������� ����� " << endl << "12. �����" << endl;
		int a;
		a = InputInt(1, 12);
		switch (a)
		{
		case 1:
		{
			rewind(stdin);
			std::cout << "������� �������: ";
			tmp = InputRussian();
			strcpy_s(this->Surname, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 2:
		{
			rewind(stdin);
			std::cout << "������� ���: ";
			tmp = InputRussian();
			strcpy_s(this->Name, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 3:
		{
			rewind(stdin);
			std::cout << "������� ��������: ";
			tmp = InputRussian();
			strcpy_s(this->MiddleName, LEN, tmp);
			std::cout << endl;
			break;
		}
		case 4:
		{
			rewind(stdin);
			std::cout << "������� ��� ��������: ";
			this->YearOfBirth = InputInt(MIN_YEAR, MAX_YEAR);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "������� ���������: ";
			tmp = InputRussian();
			strcpy_s(this->Occupation, LEN, tmp);
			break;

		}
		case 6:
		{
			rewind(stdin);
			std::cout << "������� �������������: ";
			tmp = InputRussian();
			strcpy_s(this->Specialization, LEN, tmp);
			break;

		}
		case 7:
		{
			rewind(stdin);
			std::cout << "������� ������� ������: ";
			for (int i = 0; i < 3; i++)
			{
				rewind(stdin);
				tmp = InputRussian();
				strcpy_s(this->ScienceWork[i], LEN, tmp);
			}
			break;
		}
		case 8:
		{
			rewind(stdin);
			std::cout << "������� �������� �����������: ";
			tmp = InputRussian();
			strcpy_s(this->NameOfOrganization, LEN, tmp);
			cout << endl;
			break;
		}
		case 9:
		{
			std::cout << "������� ��� ����������: ";
			this->YearOfEnter = InputInt(MIN_YEAR, MAX_YEAR);
			cout << endl;
			break;
		}
		case 10:
		{
			std::cout << "������� �������������: ";
			for (int i = 0; i < 3; i++)
			{
				rewind(stdin);
				tmp = InputRussian();
				strcpy_s(this->Autobiography[i], LEN, tmp);
			}
			break;
		}
		case 11:
		{
			cout << "������� ����������� �����:  ";
			this->ContributionPerMonth = InputDouble(-1, 10000);
			cout << endl;
			break;
		}
		case 12:
		{
			return;
		}
		}
		std::cout << "�������� ��������� ��� ������? 1 - ��, 0 - ���";

		check = InputInt(0, 1);
		std::cout << endl;
	} while (check == 1);
}