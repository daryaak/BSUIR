#pragma once
#include "Travel.h"
class Sea :
    public Travel
{
protected:
    char NameOfSea[LEN];
public:

    Sea() :
        Travel()
    {
        NameOfSea[0] = '\0';
    }

    Sea(int f,int days, int price, const char* country, const char* city, const char* d, const char* t,int id, char* n, const char* name) :
        Travel(f,days, price, country, city, d,t,id, n)
    {
        strcpy_s(this->NameOfSea, LEN, name);
    }

    ~Sea() {}

    Sea(const Sea& obj) :Travel(obj)
    {
        strcpy_s(this->NameOfSea, LEN, obj.NameOfSea);
    }

    Sea operator=(const Sea& obj);
    bool  operator==(const Sea& obj);
    bool operator<(Sea& obj);
    bool operator>(Sea& obj);
    void SetNameOfSea(const char* a);
    char* GetNameOfSea();

    friend istream& operator>>(istream& is, Sea& obj);
    friend ostream& operator<<(ostream& out, Sea& obj);

    friend ifstream& operator>>(ifstream& in, Sea& obj);
    friend ofstream& operator<<(ofstream& out, Sea& obj);

    void HeadOfSheet() override;
    void Find();
    Sea PickField();
    void ReplaceField(Sea& obj);
    void Change();
};

