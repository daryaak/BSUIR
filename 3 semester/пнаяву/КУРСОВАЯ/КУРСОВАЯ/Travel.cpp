#include "Travel.h"

Travel Travel:: operator=(const Travel& obj)
{
	*((Voucher*)this) = (Voucher&)obj;
	strcpy_s(this->NameOfHotel, LEN, obj.NameOfHotel);

	return *this;
}

void Travel::SetNameOfHotel(char* a)
{
	strcpy_s(this->NameOfHotel, LEN, a);
}

char* Travel::GetNameOfHotel() { return this->NameOfHotel; }

istream& operator>>(istream& is, Travel& obj)
{
	rewind(stdin);
	is >> dynamic_cast<Voucher&>(obj);
	cout << "Введите название отеля: ";
	rewind(stdin);
	char* tmp = InputRussian();
	strcpy_s(obj.NameOfHotel, LEN, tmp);
	delete tmp;
	return is;
}
ostream& operator<<(ostream& out, Travel& obj)
{
	out << dynamic_cast<Voucher&>(obj);
	out.setf(ios::left);
	out << setw(20) << obj.NameOfHotel;
	out.unsetf(ios::left);
	return out;
}

void Travel::HeadOfSheet()
{
	cout.setf(ios::left);
	cout << setw(5) << "№" << setw(20) << "Страна" << setw(20) << "Город" << setw(20) << "Дата отправления" << setw(20) << "Количество дней" << setw(20) << "Кол-во свобод. мест";
	cout << setw(20) << "Цена" << setw(20) << "Название отеля" << endl;
	cout.unsetf(ios::left);
}


ifstream& operator>>(ifstream& in, Travel& obj)
{
	in >> dynamic_cast<Voucher&>(obj);
	in.ignore(80, '|');
	in.getline(obj.NameOfHotel, 80, '|');
	in.clear();
	return in;

}
ofstream& operator<<(ofstream& out, Travel& obj)
{
	out << dynamic_cast<Voucher&>(obj);
	out.setf(ios::left);
	out << setw(20) << obj.NameOfHotel<<'|';
	out.unsetf(ios::left);
	return out;
}

