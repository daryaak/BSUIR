#include "Voucher.h"


void Voucher::SetCountry(const char* a) { strcpy_s(this->Country, LEN, a); }
void Voucher::SetDate(char* d) { strcpy_s(this->DateOfDeparture, LEN, d); }
void Voucher::SetCity(const char* a) { strcpy_s(this->City, LEN, a); }
void Voucher::SetAmountOfDays(int a) { this->AmountOfDays = a; }
void Voucher::SetAmountOfPlaces(int a) { this->AmountOfPlaces = a; }
void Voucher::SetPrice(int a) { this->Price = a; }
void Voucher::SetID(int d) { this->ID = d; }
void  Voucher::SetTransCom(char* a) { strcpy_s(this->TransCom, LEN, a); }
char* Voucher::GetTransCom() { return this->TransCom; }
char* Voucher::GetCountry() { return this->Country; }
char* Voucher::GetCity() { return this->City; }
char* Voucher::GetDateOfDeparture() { return this->DateOfDeparture; }
int Voucher::GetAmountOfDays() { return this->AmountOfDays; }
int Voucher::GetAmountOfPlaces() { return this->AmountOfPlaces; }
int Voucher::GetPrice() { return this->Price; }
int Voucher::GetID() { return this->ID; }

Voucher Voucher:: operator=(const Voucher& obj)
{
	strcpy_s(this->Country, LEN, obj.Country);
	strcpy_s(this->City, LEN, obj.City);
	strcpy_s(this->DateOfDeparture, LEN, obj.DateOfDeparture);
	strcpy_s(this->TransCom, LEN, obj.TransCom);
	this->AmountOfDays = obj.AmountOfDays;
	this->AmountOfPlaces = obj.AmountOfPlaces;
	this->Price = obj.Price;
	this->ID = obj.ID;
	return *this;
}
bool Voucher:: operator==(const Voucher& obj)
{
	if (strlen(obj.Country))
	{
		if (strcmp(Country, obj.Country)) return false;
	}
	if (strlen(obj.City))
	{
		if (strcmp(City, obj.City)) return false;
	}
	if (strlen(obj.DateOfDeparture))
	{
		if (strcmp(DateOfDeparture, obj.DateOfDeparture)) return false;
	}
	if (strlen(obj.TransCom))
	{
		if (strcmp(TransCom, obj.TransCom)) return false;
	}
	if (obj.AmountOfDays != 0)
	{
		if (AmountOfDays != obj.AmountOfDays) return false;
	}
	if (obj.AmountOfPlaces != 0)
	{
		if (AmountOfPlaces != obj.AmountOfPlaces) return false;
	}
	if (obj.Price != 0)
	{
		if (Price != obj.Price) return false;
	}
	if (obj.ID != 0)
	{
		if (ID != obj.ID) return false;
	}
	return true;
}

istream& operator>>(istream& is, Voucher& obj)
{
	rewind(stdin);
	cout << "Страна: ";
	char* tmp = InputRussian();
	strcpy_s(obj.Country, LEN, tmp);
	rewind(stdin);
	cout << "Город: ";
	tmp = InputRussian();
	strcpy_s(obj.City, LEN, tmp);
	rewind(stdin);
	cout << "Дата отправления: ";
	tmp = InputDate();
	strcpy_s(obj.DateOfDeparture, LEN, tmp);
	rewind(stdin);
	cout << "Транспортная компания: ";
	tmp = InputRussian();
	strcpy_s(obj.TransCom, LEN, tmp);
	rewind(stdin);
	cout << "Количество дней: ";
	obj.AmountOfDays = InputInt(1, MAX_DAYS);
	cout << "Количество свободных мест: ";
	obj.AmountOfPlaces = InputInt(1, MAX_PLACES);
	cout << "Цена: ";
	obj.Price = InputInt(1, MAX_PRICE);
	cout << "ID: ";
	obj.ID = InputInt(1, 10000);
	delete tmp;
	return is;

}

ostream& operator<<(ostream& out, const Voucher& obj)
{
	out.setf(ios::left);
	out <<setw(20) << obj.Country << setw(20) << obj.City << setw(20) << obj.DateOfDeparture<< setw(20) << obj.TransCom;
	out << setw(20) << obj.AmountOfDays;
	out << setw(20) << obj.AmountOfPlaces;
	out << setw(20) << obj.Price;
	//out << setw(20) << obj.ID;
	out.unsetf(ios::left);
	return out;
}

void Voucher::HeadOfSheet()
{
	cout.setf(ios::left);
	cout << setw(20) << "Страна" << setw(20) << "Город" << setw(20) << "Дата отправления" << setw(20) << "Трансп. компания" << setw(20) << "Кол-во дней"<< setw(20) << "Кол-во свободн. мест" << setw(20) << "Цена"<< setw(20) << "ID";
	cout.unsetf(ios::left);
}



ifstream& operator>>(ifstream& in, Voucher& obj)
{
	in.ignore(10000, '\n');
	in.getline(obj.Country, 80, '|');
	in.clear();
	in.getline(obj.City, 80, '|');
	in.clear();
	in.getline(obj.DateOfDeparture, 80, '|');
	in.clear();
	in.getline(obj.TransCom, 80, '|');
	in.clear();
	in >> obj.AmountOfDays;
	in >> obj.AmountOfPlaces;
	in >> obj.Price;
	return in;
}

ofstream& operator<<(ofstream& out, Voucher& obj)
{
	out.setf(ios::left);
	out << setw(20) << obj.Country<<'|' << setw(20) << obj.City <<'|'<< setw(20) << obj.DateOfDeparture<<'|' << setw(20) << obj.TransCom << '|';
	out << setw(20) << obj.AmountOfDays;
	out << setw(20) << obj.AmountOfPlaces;
	out << setw(20) << obj.Price<<'|';
	out.unsetf(ios::left);
	return out;
}




























