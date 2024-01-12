#include "Sanatorium.h"

Sanatorium Sanatorium::operator=(const Sanatorium& obj)
{
    *((Voucher*)this) = (Voucher&)obj;
    strcpy_s(this->NameOfSanat, LEN, obj.NameOfSanat);

    return *this;
}

void Sanatorium::SetNameOfSanat(const char* a) { strcpy_s(this->NameOfSanat, LEN, a); }

char* Sanatorium::GetNameOfSanat() { return this->NameOfSanat; }

istream& operator>>(istream& is, Sanatorium& obj)
{
    rewind(stdin);
    is >> dynamic_cast<Voucher&>(obj);
    cout << "Введите название санатория: ";
    rewind(stdin);
    char* tmp;
    tmp = InputRussian();
    strcpy_s(obj.NameOfSanat, LEN, tmp);

    delete tmp;
    return is;
}

ostream& operator<<(ostream& out, Sanatorium& obj)
{
    out << dynamic_cast<Voucher&>(obj);
    out.setf(ios::left);
    out << setw(20) << obj.NameOfSanat;
    out.unsetf(ios::left);
    return out;
}

void Sanatorium::HeadOfSheet()
{
    cout.setf(ios::left);
    cout << setw(20) << "Страна" << setw(20) << "Город" << setw(20) << "Дата отправления" << setw(20) << "Количество дней"<< setw(20) << "Кол-во своб. мест";
    cout << setw(20) << "Цена" << setw(20) << "Название санатория" << endl;
    cout.unsetf(ios::left);
}

ifstream& operator>>(ifstream& in, Sanatorium& obj)
{
    in >> dynamic_cast<Voucher&>(obj);
    in.ignore(80, '|');
    in.getline(obj.NameOfSanat, 80, '|');
    in.clear();
    return in;
}
ofstream& operator<<(ofstream& out, Sanatorium& obj)
{
    out << dynamic_cast<Voucher&>(obj);
    out.setf(ios::left);
    out << setw(20) << obj.NameOfSanat<<'|';
    out.unsetf(ios::left);
    return out;
}

