#include "Admin.h"
void Admin::SetUsername(const char* a)
{
	strcpy_s(this->username, L, a);
}
void Admin::Setpassword(const char* a)
{
	strcpy_s(this->password, L, a);
}
char* Admin::GetUsername()
{
	return this->username;
}
char* Admin::GetPassword()
{
	return this->password;
}
Admin Admin::operator=(const Admin& a)
{
	strcpy_s(this->username, L, a.username);
	strcpy_s(this->password, L, a.password);
	return *this;
}
ostream& operator << (ostream& out, const Admin& obj)
{
	out.setf(ios::left);
	out << setw(20) << obj.username << setw(20) << obj.password;
	out.unsetf(ios::left);
	return out;
}
istream& operator >> (istream& in, Admin& obj)
{
	rewind(stdin);
	cout << "¬ведите им€ пользовател€:  ";
	in >> obj.username;
	rewind(stdin);
	cout << "¬ведите пароль: ";
	in >> obj.password;
	char BUFFER[L], c;
	int i = 0;
	while ((c = _getch()) != '\r') {
		_putch('*');
		BUFFER[i] = c;
		i++;
	}
	BUFFER[i] = '\0';
	strcpy_s(obj.password, L, BUFFER);
	return in;

}
ifstream& operator>>(ifstream& in, Admin& obj)
{
	in >> obj.username;
	in >> obj.password;
	return in;
}
ofstream& operator<<(ofstream& out, Admin& obj)
{
	out.setf(ios::left);
	out << setw(20) << obj.username << setw(20) << obj.password;
	out.unsetf(ios::left);
	return out;
}
