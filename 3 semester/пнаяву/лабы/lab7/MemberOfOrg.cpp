#include "MemberOfOrg.h"


char* MemberOfOrg::getNameOfOrganization() { return NameOfOrganization; }
int MemberOfOrg::getYearOfEnter() { return YearOfEnter; }
char** MemberOfOrg::getAutobiography() { return (char**)Autobiography; }

void MemberOfOrg::setNameOfOrganization(char* a) { strcpy_s(this->NameOfOrganization, LEN, a); }
void MemberOfOrg::setYearOfEnter(int a) { this->YearOfEnter = a; }
void MemberOfOrg::setAutobiography(char** a)
{
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], LEN, a[i]);
	}
}

bool MemberOfOrg:: operator==(const MemberOfOrg& obj)
{
	if (!(*((Man*)this) == (Man&)obj)) return false;
	if (strlen(obj.NameOfOrganization))
	{
		if (strncmp(NameOfOrganization, obj.NameOfOrganization, strlen(obj.NameOfOrganization)))return false;
	}

	if (obj.YearOfEnter != 0)
	{
		if (YearOfEnter != obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strncmp(Autobiography[i], obj.Autobiography[i], strlen(obj.Autobiography[i])))return false;
		}
	}

	return true;
}
bool MemberOfOrg:: operator<(const MemberOfOrg& obj)
{
	if (strlen(obj.Name))
	{
		if (strcmp(Name, obj.Name) > 0) return false;
	}

	if (strlen(obj.MiddleName))
	{
		if (strcmp(MiddleName, obj.MiddleName) > 0) return false;
	}

	if (strlen(obj.Surname))
	{
		if (strcmp(Surname, obj.Surname) > 0)return false;
	}

	if (obj.YearOfBirth != 0)
	{
		if (YearOfBirth > obj.YearOfBirth) return false;
	}
	if (strlen(obj.NameOfOrganization))
	{
		if (strcmp(NameOfOrganization, obj.NameOfOrganization)>0)return false;
	}

	if (obj.YearOfEnter != 0)
	{
		if (YearOfEnter > obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strcmp(Autobiography[i], obj.Autobiography[i])>0)return false;
		}
	}

	return true;
}
bool MemberOfOrg:: operator>(const MemberOfOrg& obj)
{
	if (strlen(obj.Name))
	{
		if (strcmp(Name, obj.Name) < 0) return false;
	}

	if (strlen(obj.MiddleName))
	{
		if (strcmp(MiddleName, obj.MiddleName) < 0) return false;
	}

	if (strlen(obj.Surname))
	{
		if (strcmp(Surname, obj.Surname) < 0)return false;
	}

	if (obj.YearOfBirth != 0)
	{
		if (YearOfBirth < obj.YearOfBirth) return false;
	}
	if (strlen(obj.NameOfOrganization))
	{
		if (strcmp(NameOfOrganization, obj.NameOfOrganization)<0)return false;
	}

	if (obj.YearOfEnter != 0)
	{
		if (YearOfEnter < obj.YearOfEnter) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (strlen(obj.Autobiography[i]))
		{
			if (strcmp(Autobiography[i], obj.Autobiography[i])<0)return false;
		}
	}

	return true;
}

MemberOfOrg MemberOfOrg:: operator=(const MemberOfOrg& obj)
{
	*((Man*)this) = (Man&)obj;
	this->YearOfEnter = obj.YearOfEnter;
	strcpy_s(this->NameOfOrganization, LEN, obj.NameOfOrganization);
	for (int i = 0; i < 3; i++)
	{
		strcpy_s(this->Autobiography[i], LEN, obj.Autobiography[i]);
	}
	return *this;
}

fstream& operator<<(fstream& in, MemberOfOrg& ob)
{
	in << dynamic_cast<Man&>(ob);
	in.write(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	in.write(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	for (int i = 0; i < 3; i++)
	{
		in.write(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}

	return in;
}

fstream& operator>>(fstream& out, MemberOfOrg& ob)
{
	out >> dynamic_cast<Man&>(ob);
	out.read(reinterpret_cast<char*> (&ob.NameOfOrganization), sizeof(ob.NameOfOrganization));
	out.read(reinterpret_cast<char*> (&ob.YearOfEnter), sizeof(ob.YearOfEnter));
	for (int i = 0; i < 3; i++)
	{
		out.read(reinterpret_cast<char*> (&ob.Autobiography[i]), sizeof(ob.Autobiography[i]));
	}
	return out;
}

istream& operator>>(istream& is, MemberOfOrg& obj)
{
	rewind(stdin);
	is >> dynamic_cast<Man&>(obj);
	std::cout << "������� �������� �����������: ";
	rewind(stdin);
	char* tmp = InputRussian();
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
	return is;
}
ifstream& operator>>(ifstream& in, MemberOfOrg& obj)
{
	in >> dynamic_cast<Man&>(obj);
	in.ignore(80, '|');
	in.getline(obj.NameOfOrganization, 80, '|');
	in.clear();
	in >> obj.YearOfEnter;
	in.ignore(80, '|');
	for (int i = 0; i < 3; i++)
	{
		if (i != 0) in.ignore(1000000, '|');
		in.getline(obj.Autobiography[i], 80, '|');
		//if (i != 2)in.clear();
	}
	return in;
}

ostream& operator<<(ostream& out, const MemberOfOrg& obj)
{

	out << static_cast<const Man&>(obj);
	out.setf(ios::left);
	out << setw(20) << obj.NameOfOrganization << setw(20) << obj.YearOfEnter;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.Autobiography[i] << setw(20) << endl;
			continue;
		}
		out << setw(105) << " " << obj.Autobiography[i] << setw(20) << endl;
	}
	out.unsetf(ios::left);
	return out;
}

ofstream& operator<<(ofstream& out, MemberOfOrg& obj)
{
	out << dynamic_cast<Man&>(obj);
	out.setf(ios::left);
	out << setw(20) << obj.NameOfOrganization << '|' << setw(20) << obj.YearOfEnter << '|';
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			out << setw(20) << obj.Autobiography[i] << '|' << setw(20) << endl;
			continue;
		}
		out << setw(105) << " " << "|" << obj.Autobiography[i] << '|' << setw(20) << endl;
	}
	out.unsetf(ios::left);
	return out;
}

void MemberOfOrg::HeadOfSheet()
{

	std::cout.setf(ios::left);
	std::cout << setw(5) << "�" << setw(15) << "�������" << setw(15) << "���" << setw(15) << "��������" << setw(15) << "��� ��������";
	std::cout << setw(15) << "����.�����." << setw(15) << "��� ����������" << setw(15) << "�������������" << endl;
	std::cout.unsetf(ios::left);
}

void MemberOfOrg::Find()
{

	int check;
	char* tmp;
	do
	{
		rewind(stdin);
		cout << "�������� ��������" << endl << "1.�������" << endl << "2.���" << endl << "3.��������" << endl << "4.��� ��������" << endl;
		cout << "5.�������� �����������" << endl << "6.��� ����������" << endl << "7.�������������" << endl << "8. �����" << endl;
		int a;
		a = InputInt(1, 8);
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
			this->YearOfBirth = InputInt(1900, 2022);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "������� �������� �����������: ";
			tmp = InputRussian();
			strcpy_s(this->NameOfOrganization, LEN, tmp);
			cout << endl;
			break;
		}
		case 6:
		{
			std::cout << "������� ��� ����������: ";
			this->YearOfEnter = InputInt(1900, 2022);
			cout << endl;
			break;
		}
		case 7:
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
		case 8:
		{
			return;
		}
		}

		std::cout << "�������� ��������� ��� ������? 1 - ��, 0 - ���";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);

	return;
}

void MemberOfOrg::Pick()
{

	
		rewind(stdin);
		cout << "�������� ��������" << endl << "1.�������" << endl << "2.���" << endl << "3.��������" << endl << "4.��� ��������" << endl;
		cout << "5.�������� �����������" << endl << "6.��� ����������" << endl << "7.�������������"<<endl;
		int a;
		a = InputInt(1, 7);
		switch (a)
		{
		case 1:
		{
			strcpy_s(this->Surname, LEN, "a");
			break;
		}
		case 2:
		{
			strcpy_s(this->Name, LEN, "a");
			break;
		}
		case 3:
		{
			strcpy_s(this->MiddleName, LEN, "a");
			break;
		}
		case 4:
		{
			this->YearOfBirth = 1;
			break;
		}
		case 5:
		{
			strcpy_s(this->NameOfOrganization, LEN, "a");
			break;
		}
		case 6:
		{
			
			this->YearOfEnter = 1;
		
			break;
		}
		case 7:
		{
			for (int i = 0; i < 3; i++)
			{
				strcpy_s(this->Autobiography[i], LEN, "a");
				
			}
			break;
		}
		
		}
	return ;
}

void MemberOfOrg::Change()
{

	int check;
	char* tmp;
	do
	{
		rewind(stdin);
		cout << "�������� �������� ��� ��������������" << endl << "1.�������" << endl << "2.���" << endl << "3.��������" << endl << "4.��� ��������" << endl;
		cout << "5.�������� �����������" << endl << "6.��� ����������" << endl << "7.�������������" << endl << "8. �����" << endl;
		int a;
		a = InputInt(1, 8);
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
			this->YearOfBirth = InputInt(1900, 2022);
			std::cout << endl;
			break;
		}
		case 5:
		{
			rewind(stdin);
			std::cout << "������� �������� �����������: ";
			tmp = InputRussian();
			strcpy_s(this->NameOfOrganization, LEN, tmp);
			cout << endl;
			break;
		}
		case 6:
		{
			std::cout << "������� ��� ����������: ";
			this->YearOfEnter = InputInt(1900, 2022);
			cout << endl;
			break;
		}
		case 7:
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
		case 8:
		{
			return;
		}
		}

		std::cout << "�������� ��������� ��� ������? 1 - ��, 0 - ���";

		check = InputInt(0, 1);
		std::cout << endl;

	} while (check == 1);

	return;
}

void MemberOfOrg::ReplaceField(MemberOfOrg& obj)
{
	if (strlen(this->Surname))
		strcpy_s(this->Surname, LEN, obj.Surname);
	if (strlen(this->Name))
		strcpy_s(this->Name, LEN, obj.Name);
	if (strlen(this->MiddleName))
		strcpy_s(this->MiddleName, LEN, obj.MiddleName);
	if (strlen(this->NameOfOrganization))
		strcpy_s(this->NameOfOrganization, LEN, obj.NameOfOrganization);
	if (this->YearOfBirth != 0)
		this->YearOfBirth = obj.YearOfBirth;
	if (this->YearOfEnter != 0)
		this->YearOfEnter = obj.YearOfEnter;
	for (int i = 0; i < 3; i++)
	{
		if (strlen(this->Autobiography[i]))
			strcpy_s(this->Autobiography[i], LEN, obj.Autobiography[i]);
	}
}