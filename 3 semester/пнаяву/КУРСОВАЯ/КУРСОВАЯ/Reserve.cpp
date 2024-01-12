#include "Reserve.h"

int Reserve::GetFinalPrice() { return this->FinalPrice; }
Reserve Reserve::operator=(const Reserve& obj)
{
	strcpy_s(this->Surname, L, obj.Surname);
	strcpy_s(this->PhoneNumber, L, obj.PhoneNumber);
	this->ID_OfTour = obj.ID_OfTour;
	this->AmountOfPeople = obj.AmountOfPeople;
	this->FinalPrice = obj.FinalPrice;
	return *this;
}

ostream& operator << (ostream& out, const Reserve& obj)
{
	out.setf(ios::left);
	out << setw(20) << obj.Surname << setw(20) << obj.PhoneNumber << setw(20) << obj.ID_OfTour << setw(20) << obj.AmountOfPeople << setw(20) << obj.FinalPrice << endl;
	out.unsetf(ios::left);
	return out;
}

ifstream& operator>>(ifstream& in, Reserve& obj)
{
    in.ignore(10000, '\n');
    in.getline(obj.Surname, 80, '|');
    in.clear();
	in >> obj.PhoneNumber;
	in >> obj.ID_OfTour;
	in >> obj.AmountOfPeople;
	in >> obj.FinalPrice;
	return in;
}

ofstream& operator<<(ofstream& out, Reserve& obj)
{
	out.setf(ios::left);
	out << setw(20) << obj.Surname << setw(20) << '|' << obj.PhoneNumber << setw(20) << obj.ID_OfTour << setw(20) << obj.AmountOfPeople << setw(20) << obj.FinalPrice<<endl;
	out.unsetf(ios::left);
	return out;
}

void Reserve::HeadOfSheet()
{
	cout.setf(ios::left);
	cout << setw(5) <<"№"<< setw(20) << "Фамилия" << setw(20) << "Номер телефона" << setw(20) << "ID тура" << setw(20) << "Кол-во человек" << setw(20) << "Финальная цена" << endl;
	cout.unsetf(ios::left);
}

Reserve Reserve::PickField()
{
    Reserve tmp;
    cout << "Выберите параметр для сортировки" << endl << "1.Фамилия" << endl << "2.Номер телефона" << endl << "3.ID тура" << endl
        << "4.Кол-во человек" << endl << "5.Финальная цена" << endl;
    int a = InputInt(1, 5);
    switch (a)
    {
    case 1:
    {
        strcpy_s(tmp.Surname, L, this->Surname);
        break;
    }
    case 2:
    {
        strcpy_s(tmp.PhoneNumber, L, this->PhoneNumber);
        break;
    }
    case 3:
    {
       tmp.ID_OfTour=this->ID_OfTour;
        break;
    }
    case 4:
    {
        tmp.AmountOfPeople = this->AmountOfPeople;
        break;
    }
    case 5:
    {
        tmp.FinalPrice = this->FinalPrice;
        break;
    }
    }
    return tmp;
}

void Reserve::Find()
{
    int check;
    char* tmp;
    do
    {
    cout << "Выберите параметр для поиска" << endl << "1.Фамилия" << endl << "2.Номер телефона" << endl << "3.ID тура" << endl
        << "4.Кол-во человек" << endl << "5.Финальная цена" << endl;
    int a = InputInt(1, 5);
    switch (a)
    {
    case 1:
    {
        rewind(stdin);
        cout << "Введите фамилию: ";
        tmp = InputRussian();
        strcpy_s(this->Surname, L,tmp);
        cout << endl;
        break;
    }
    case 2:
    {
        rewind(stdin);
        cout << "Введите номер телефона: ";
        tmp = InputRussian();
        strcpy_s(this->PhoneNumber, L, tmp);
        cout << endl;
        break;
    }
    case 3:
    {
        rewind(stdin);
        cout << "Введите ID тура: ";
        this->ID_OfTour=InputInt(1,10000);
        cout << endl;
        break;
    }
    case 4:
    {
        rewind(stdin);
        cout << "Введите количество человек: ";
        this->AmountOfPeople=InputInt(1,30);
        cout << endl;
        break;
    }
    case 5:
    {
        rewind(stdin);
        cout << "Введите количество человек: ";
        this->FinalPrice = InputInt(1, 10000);
        cout << endl;
        break;
    }
    }
    cout << "Добавить параметры для поиска? 1 - да, 0 - нет";
    cin >> check;
    cout << endl;
    } while (check == 1);
}

void Reserve::Change()
{
    int check;
    char* tmp;
    do
    {
        cout << "Выберите параметр для редактирования" << endl << "1.Фамилия" << endl << "2.Номер телефона" << endl << "3.ID тура" << endl
            << "4.Кол-во человек" << endl << "5.Финальная цена" << endl;
        int a = InputInt(1, 5);
        switch (a)
        {
        case 1:
        {
            rewind(stdin);
            cout << "Введите фамилию: ";
            tmp = InputRussian();
            strcpy_s(this->Surname, L, tmp);
            cout << endl;
            break;
        }
        case 2:
        {
            rewind(stdin);
            cout << "Введите номер телефона: ";
            tmp = InputRussian();
            strcpy_s(this->PhoneNumber, L, tmp);
            cout << endl;
            break;
        }
        case 3:
        {
            rewind(stdin);
            cout << "Введите ID тура: ";
            this->ID_OfTour = InputInt(1, 10000);
            cout << endl;
            break;
        }
        case 4:
        {
            rewind(stdin);
            cout << "Введите количество человек: ";
            this->AmountOfPeople = InputInt(1, 30);
            cout << endl;
            break;
        }
        case 5:
        {
            rewind(stdin);
            cout << "Введите количество человек: ";
            this->FinalPrice = InputInt(1, 10000);
            cout << endl;
            break;
        }
        }
        cout << "Добавить параметры для редактирования? 1 - да, 0 - нет";
        cin >> check;
        cout << endl;
    } while (check == 1);
}

void Reserve::ReplaceField(Reserve& obj)
{
    if (strlen(this->Surname))
        strcpy_s(this->Surname, L, obj.Surname);
    if (strlen(this->PhoneNumber))
        strcpy_s(this->PhoneNumber, L, obj.PhoneNumber);
    if (this->AmountOfPeople != 0)
        this->AmountOfPeople= obj.AmountOfPeople;
    if (this->FinalPrice != 0)
        this->FinalPrice = obj.FinalPrice;
    if (this->ID_OfTour != 0)
        this->ID_OfTour = obj.ID_OfTour;
}

istream& operator>>(istream& is, Reserve& obj)
{
    rewind(stdin);
    cout << "Фамилия: ";
    char* tmp = InputRussian();
    strcpy_s(obj.Surname, L, tmp);
    rewind(stdin);
    cout << "Номер телефона: ";
    tmp = InputRussian();
    strcpy_s(obj.PhoneNumber, L, tmp);
    rewind(stdin);
    cout << "Количество человек: ";
    obj.AmountOfPeople = InputInt(1,30);
    cout << "Финальная цена: ";
    obj.FinalPrice = InputInt(1, 30);
    cout << "ID: ";
    obj.ID_OfTour= InputInt(1, 10000);
    delete tmp;
    return is;
}

bool Reserve:: operator==(const Reserve& obj)
{
    if (strlen(obj.Surname))
    {
        if (strncmp(Surname, obj.Surname, strlen(obj.Surname))) return false;
    }
    if (strlen(obj.PhoneNumber))
    {
        if (strncmp(PhoneNumber, obj.PhoneNumber, strlen(obj.PhoneNumber))) return false;
    }
    if (obj.AmountOfPeople != 0)
    {
        if (AmountOfPeople != obj.AmountOfPeople) return false;
    }
    if (obj.FinalPrice != 0)
    {
        if (FinalPrice != obj.FinalPrice) return false;
    }
    if (obj.ID_OfTour != 0)
    {
        if (ID_OfTour != obj.ID_OfTour) return false;
    }
    return true;
}

bool Reserve:: operator<(const Reserve& obj)
{
    if (strlen(obj.Surname))
    {
        if (strcmp(Surname, obj.Surname)>0) return false;
    }
    if (strlen(obj.PhoneNumber))
    {
        if (strcmp(PhoneNumber, obj.PhoneNumber)>0) return false;
    }
    if (obj.AmountOfPeople != 0)
    {
        if (AmountOfPeople > obj.AmountOfPeople) return false;
    }
    if (obj.FinalPrice != 0)
    {
        if (FinalPrice > obj.FinalPrice) return false;
    }
    if (obj.ID_OfTour != 0)
    {
        if (ID_OfTour > obj.ID_OfTour) return false;
    }
    return true;
}

bool Reserve:: operator>(const Reserve& obj)
{
    if (strlen(obj.Surname))
    {
        if (strcmp(Surname, obj.Surname) < 0) return false;
    }
    if (strlen(obj.PhoneNumber))
    {
        if (strcmp(PhoneNumber, obj.PhoneNumber) < 0) return false;
    }
    if (obj.AmountOfPeople != 0)
    {
        if (AmountOfPeople < obj.AmountOfPeople) return false;
    }
    if (obj.FinalPrice != 0)
    {
        if (FinalPrice < obj.FinalPrice) return false;
    }
    if (obj.ID_OfTour != 0)
    {
        if (ID_OfTour < obj.ID_OfTour) return false;
    }
    return true;
}