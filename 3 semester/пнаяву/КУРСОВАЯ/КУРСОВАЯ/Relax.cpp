#include "Relax.h"

char* Relax::GetActivities()
{
    return this->Activities;
}

void Relax::SetActivities(char* a)
{
    strcpy_s(this->Activities, LEN, a);
}

Relax Relax::operator=(const Relax& obj)
{
    *((Sanatorium*)this) = (Sanatorium&)obj;
    strcpy_s(this->Activities, LEN, obj.Activities);
    return *this;
}

bool Relax::operator==(const Relax& obj)
{

    if (strlen(obj.Country))
        if (strncmp(Country, obj.Country, strlen(obj.Country))) return false;
    if (strlen(obj.City))
        if (strncmp(City, obj.City, strlen(obj.City))) return false;
    if (strlen(obj.DateOfDeparture))
        if (strncmp(DateOfDeparture, obj.DateOfDeparture, strlen(obj.DateOfDeparture))) return false;
    if (strlen(obj.TransCom))
        if (strncmp(TransCom, obj.TransCom, strlen(obj.TransCom))) return false;
    if (obj.AmountOfDays != 0)
        if (AmountOfDays != obj.AmountOfDays) return false;
    if (obj.AmountOfPlaces != 0)
        if (AmountOfPlaces != obj.AmountOfPlaces) return false;
    if (obj.Price != 0)
        if (Price != obj.Price) return false;
    if (obj.ID != 0)
        if (ID != obj.ID) return false;
    if (strlen(NameOfSanat))
        if (strncmp(NameOfSanat, obj.NameOfSanat, strlen(obj.NameOfSanat))) return false;
    if (strlen(obj.Activities))
        if (strncmp(Activities, obj.Activities,strlen(obj.Activities))) return false;
    return true;
}

istream& operator>>(istream& is, Relax& obj)
{
    rewind(stdin);
    is >> dynamic_cast<Sanatorium&>(obj);
    cout << "Введите специфику: ";
    rewind(stdin);
    char* tmp = InputRussian();
    strcpy_s(obj.Activities, LEN, tmp);
    delete tmp;
    return is;
}
ostream& operator<<(ostream& out, Relax& obj)
{
    out << dynamic_cast<Sanatorium&>(obj);
    out.setf(ios::left);
    out << setw(20) << obj.Activities << setw(20)<< obj.ID << setw(20) << endl;
    out.unsetf(ios::left);
    return out;
}
ifstream& operator>>(ifstream& in, Relax& obj)
{
    in >> dynamic_cast<Sanatorium&>(obj);
    in.getline(obj.Activities, 80, '|');
    in.clear();
    in >> obj.ID;
    return in;
}
ofstream& operator<<(ofstream& out, Relax& obj)
{
    out << dynamic_cast<Sanatorium&>(obj);
    out.setf(ios::left);
    out << setw(20) << obj.Activities <<'|'<< setw(20) << obj.ID << setw(20) << endl;
    out.unsetf(ios::left);
    return out;
}

void Relax::HeadOfSheet()
{
    cout.setf(ios::left);
    cout << setw(5) << "№" << setw(20) << "Страна" << setw(20) << "Город" << setw(20) << "Дата отправления" 
        << setw(20) << "Трансп. компания" << setw(20) << "Количество дней"<< setw(20) << "Количество мест";
    cout << setw(20) << "Цена" << setw(20) << "Название базы отдыха" << setw(20) <<  "Специфика"<< setw(20) << "ID" << endl;
    cout.unsetf(ios::left);
}

void Relax::Find()
{
    int check;

    char* tmp;
    do
    {
        cout << "Выберите параметр для поиска" << endl << "1.Страна" << endl << "2.Город" << endl << "3.Дата отправления" << endl
            << "4.Трансп. компания" << endl << "5.Количество дней" << endl << "6.Количество мест" << endl;
        cout << "7.Цена тур агенства" << endl << "8.Название базы отдыха" << endl << "9.Специфика" << endl << "10.ID " << endl;
        int a = InputInt(1, 10);
        cin >> a;
        switch (a)
        {
        case 1:
        {
            rewind(stdin);
            cout << "Введите страну: ";
            tmp = InputRussian();
            strcpy_s(this->Country, LEN, tmp);
            cout << endl;
            break;
        }
        case 2:
        {
            rewind(stdin);
            cout << "Введите город: ";
            tmp = InputRussian();
            strcpy_s(this->City, LEN, tmp);
            cout << endl;
            break;
        }
        case 3:
        {
            rewind(stdin);
            cout << "Введите дату отправления: ";
            tmp = InputDate();
            strcpy_s(this->DateOfDeparture, LEN, tmp);
            cout << endl;
            break;
        }
        case 4:
        {
            rewind(stdin);
            cout << "Введите транспорную компанию: ";
            tmp = InputRussian();
            strcpy_s(this->TransCom, LEN, tmp);
            cout << endl;
            break;
        }
        case 5:
        {
            rewind(stdin);
            cout << "Введите количество дней: ";
            this->AmountOfDays = InputInt(1, MAX_DAYS);
            cout << endl;
            break;
        }
        case 6:
        {
            rewind(stdin);
            cout << "Введите количество мест: ";
            this->AmountOfDays = InputInt(1, MAX_PLACES);
            cout << endl;
            break;
        }
        case 7:
        {

            rewind(stdin);
            cout << "Введите цену тур агенства: ";
            this->Price = InputInt(0, 10000);
            break;

        }
        case 8:
        {
            rewind(stdin);
            cout << "Введите названия базы отдыха: ";
            tmp = InputRussian();
            strcpy_s(this->NameOfSanat, LEN, tmp);
            break;
        }
        case 9:
        {
            rewind(stdin);
            cout << "Введите специфику: ";
            tmp = InputRussian();
            strcpy_s(this->Activities, LEN, tmp);
            break;
        }
        case 10:
        {
            rewind(stdin);
            cout << "Введите ID: ";
            this->Price = InputInt(0, 10000);
            break;
        }
        }
        cout << "Добавить параметры для поиска? 1 - да, 0 - нет";
        cin >> check;
        cout << endl;
    } while (check == 1);
    return;
}


void Relax::Change()
{
    int check;
    char* tmp;
    do
    {
        cout << "Выберите параметр, который нужно изменить" << endl << "1.Страна" << endl << "2.Город" << endl << "3.Дата отправления"<< endl
            << "4.Трансп. компания" << endl << "5.Количество дней"<< endl << "6.Количество мест" << endl;
        cout << "7.Цена тур агенства" << endl << "8.Название базы отдыха" << endl << "9.Специфика" << endl << "10.ID " << endl << "11.Выход" << endl;
        int a = InputInt(1, 11);
        switch (a)
        {
        case 1:
        {
            rewind(stdin);
            cout << "Введите страну: ";
            tmp = InputRussian();
            strcpy_s(this->Country, LEN, tmp);
            cout << endl;
            break;
        }
        case 2:
        {
            rewind(stdin);
            cout << "Введите город: ";
            tmp = InputRussian();
            strcpy_s(this->City, LEN, tmp);
            cout << endl;
            break;
        }
        case 3:
        {
            rewind(stdin);
            cout << "Введите дату отправления: ";
            tmp = InputDate();
            strcpy_s(this->DateOfDeparture, LEN, tmp);
            cin >> this->DateOfDeparture;
            cout << endl;
            break;
        }
        case 4:
        {
            rewind(stdin);
            cout << "Введите транспортную компанию: ";
            tmp = InputRussian();
            strcpy_s(this->TransCom, LEN, tmp);
            cout << endl;
            break;
        }
        case 5:
        {
            rewind(stdin);
            cout << "Введите количество дней: ";
            this->AmountOfDays = InputInt(1, MAX_DAYS);
            cout << endl;
            break;
        }
        case 6:
        {
            rewind(stdin);
            cout << "Введите количество мест: ";
            this->AmountOfDays = InputInt(1, MAX_PLACES);
            cout << endl;
            break;
        }
        case 7:
        {
            rewind(stdin);
            cout << "Введите цену тур агенства: ";
            this->Price = InputInt(0, 10000);
            break;
        }
        case 8:
        {
            rewind(stdin);
            cout << "Введите название базы отдыха: ";
            tmp = InputRussian();
            strcpy_s(this->NameOfSanat, LEN, tmp);
            break;
        }
        case 9:
        {
            rewind(stdin);
            cout << "Введите специфику: ";
            tmp = InputRussian();
            strcpy_s(this->Activities, LEN, tmp);
            break;
        }
        case 10:
        {
            rewind(stdin);
            cout << "Введите ID: ";
            this->Price = InputInt(0, 10000);
            break;
        }
        case 11:
        {
            return;
        }
        }
        cout << "Добавить параметры для изменения? 1 - да, 0 - нет"<<endl;
        cin >> check;
        cout << endl;
    } while (check == 1);
    return;
}

Relax Relax::PickField()
{
    Relax tmp;
    cout << "Выберите параметр для сортировки" << endl << "1.Страна" << endl << "2.Город" << endl << "3.Дата отправления"<< endl
        << "4.Трансп. компания" << endl << "5.Количество дней"<< endl << "6.Количество мест" << endl;
    cout << "7.Цена тур агенства" << endl << "8.Название базы отдыха" << endl << "9.Специфика" << endl << "10.ID" << endl;
    int a=InputInt(1,10);
    
    switch (a)
    {
    case 1:
    {
        strcpy_s(tmp.Country, LEN, this->Country);
        
        break;
    }
    case 2:
    {
        strcpy_s(tmp.City, LEN, this->City);
        break;
    }
    case 3:
    {
        strcpy_s(tmp.DateOfDeparture, LEN, this->DateOfDeparture);
        break;
    }
    case 4:
    {
        strcpy_s(tmp.TransCom, LEN, this->TransCom);
        break;
    }
    case 5:
    {
        tmp.AmountOfDays = this->AmountOfDays;
        break;
    }
    case 6:
    {
        tmp.AmountOfPlaces = this->AmountOfPlaces;
        break;
    }
    case 7:
    {
        tmp.Price = this->Price;
        break;
    }
    case 8:
    {
        strcpy_s(tmp.NameOfSanat, LEN, this->NameOfSanat);
        break;
    }
    case 9:
    {
        strcpy_s(tmp.Activities, LEN, this->Activities);
        break;
    }
    case 10:
    {
        tmp.ID = this->ID;
        break;
    }
    }
    return tmp;
}

bool Relax::operator<(Relax& obj)
{
    if (strlen(obj.Country))
        if (strcmp(this->Country, obj.Country) > 0) return false;
    if (strlen(obj.City))
        if (strcmp(this->City, obj.City) > 0) return false;
    if (strlen(obj.TransCom))
        if (strcmp(this->TransCom, obj.TransCom) > 0) return false;
     if (strlen(obj.DateOfDeparture))
     {
         char* tmp = new char[11];
         strcpy_s(tmp, 11, obj.DateOfDeparture);
         if (this->DateOfDeparture[9] > tmp[9]) return false;
         if (this->DateOfDeparture[9] < tmp[9]) return true;
         if (this->DateOfDeparture[9] == tmp[9])
         {
             if (this->DateOfDeparture[3] > tmp[3]) return false;
             if (this->DateOfDeparture[3] < tmp[3]) return true;
             if (this->DateOfDeparture[3] == tmp[3])
             {
                 if (this->DateOfDeparture[4] > tmp[4]) return false;
                 if (this->DateOfDeparture[4] < tmp[4]) return true;
                 if (this->DateOfDeparture[4] == tmp[4])
                 {
                     if (this->DateOfDeparture[0] > tmp[0]) return false;
                     if (this->DateOfDeparture[0] < tmp[0]) return true;
                     if (this->DateOfDeparture[0] < tmp[0])
                     {
                         if (this->DateOfDeparture[1] > tmp[1]) return false;
                      
                     }
                 }
             }
         } 
     }
     if (obj.AmountOfDays != 0)
         if (this->AmountOfDays > obj.AmountOfDays) return false;
     if (obj.AmountOfPlaces != 0)
         if (this->AmountOfPlaces > obj.AmountOfPlaces) return false;
     if (obj.Price != 0)
         if (this->Price > obj.Price) return false;
     if (obj.ID != 0)
         if (this->ID > obj.ID) return false;
     if (strlen(obj.NameOfSanat))
         if (strcmp(this->NameOfSanat, obj.NameOfSanat) > 0) return false;
     if (strlen(obj.Activities))
         if (strcmp(this->Activities, obj.Activities) > 0) return false;
     return true;
}

bool Relax::operator>(Relax& obj)
{
    if (strlen(obj.Country))
        if (strcmp(this->Country, obj.Country) < 0) return false;
    if (strlen(obj.City))
        if (strcmp(this->City, obj.City) < 0) return false;
    if (strlen(obj.TransCom))
        if (strcmp(this->TransCom, obj.TransCom) < 0) return false;
    if (strlen(obj.DateOfDeparture))
    {
        char* tmp = new char[11];
        strcpy_s(tmp, 11, obj.DateOfDeparture);
        if (this->DateOfDeparture[9] < tmp[9]) return false;
        if (this->DateOfDeparture[9] > tmp[9]) return true;
        if (this->DateOfDeparture[9] == tmp[9])
        {
            if (this->DateOfDeparture[3] < tmp[3]) return false;
            if (this->DateOfDeparture[3] > tmp[3]) return true;
            if (this->DateOfDeparture[3] == tmp[3])
            {
                if (this->DateOfDeparture[4] < tmp[4]) return false;
                if (this->DateOfDeparture[4] > tmp[4]) return true;
                if (this->DateOfDeparture[4] == tmp[4])
                {
                    if (this->DateOfDeparture[0] < tmp[0]) return false;
                    if (this->DateOfDeparture[0] > tmp[0]) return true;
                    if (this->DateOfDeparture[0] == tmp[0])
                    {
                        if (this->DateOfDeparture[1] > tmp[1]) return false;

                    }
                }
            }
        }
    }
    if (obj.AmountOfDays != 0)
        if (this->AmountOfDays < obj.AmountOfDays) return false;
    if (obj.AmountOfPlaces != 0)
        if (this->AmountOfPlaces < obj.AmountOfPlaces) return false;
    if (obj.Price != 0)
        if (this->Price < obj.Price) return false;
    if (obj.ID != 0)
        if (this->ID < obj.ID) return false;
    if (strlen(obj.NameOfSanat))
        if (strcmp(this->NameOfSanat, obj.NameOfSanat) < 0) return false;
    if (strlen(obj.Activities))
        if (strcmp(this->Activities, obj.Activities) < 0) return false;
    return true;
}

void Relax::ReplaceField(Relax& obj)
{
    if (strlen(this->Country))
        strcpy_s(this->Country, LEN, obj.Country);
    if (strlen(this->City))
        strcpy_s(this->City, LEN, obj.City);
    if (strlen(this->DateOfDeparture))
        strcpy_s(this->DateOfDeparture, LEN, obj.DateOfDeparture);
    if (strlen(this->TransCom))
        strcpy_s(this->TransCom, LEN, obj.TransCom);
   if (this->AmountOfDays!=0)
        this->AmountOfDays=obj.AmountOfDays;
   if (this->AmountOfPlaces!=0)
        this->AmountOfPlaces=obj.AmountOfPlaces;
   if (this->Price!=0)
        this->Price=obj.Price;
   if (this->ID!=0)
        this->ID=obj.ID;
   if (strlen(this->NameOfSanat))
        strcpy_s(this->NameOfSanat, LEN, obj.NameOfSanat);
   if (strlen(this->Activities))
        strcpy_s(this->Activities, LEN, obj.Activities);
}