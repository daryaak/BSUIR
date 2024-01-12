#pragma once
#include "Voucher.h"

class Travel :
    public Voucher
{
protected:
    char NameOfHotel[LEN];

public:
    Travel() : Voucher()
    {
        NameOfHotel[0] = '\0';
    }

    Travel(int f,int days, int price, const char* country, const char* city, const char* d, const char* t, int id, const char* name) :
        Voucher(f,price, days, country, city, d, t, id)
    {
        strcpy_s(this->NameOfHotel, LEN, name);

    }

    Travel(const Travel& obj) :Voucher(obj)
    {
        strcpy_s(this->NameOfHotel, LEN, obj.NameOfHotel);

    }

    ~Travel() {}

    Travel operator=(const Travel& obj);

    void SetNameOfHotel(char* a);

    char* GetNameOfHotel();

    bool operator==(const Travel& obj);

    friend istream& operator>>(istream& is, Travel& obj);
    friend ostream& operator<<(ostream& out, Travel& obj);

    friend ifstream& operator>>(ifstream& in, Travel& obj);
    friend ofstream& operator<<(ofstream& out, Travel& obj);

    void HeadOfSheet() override;

};

