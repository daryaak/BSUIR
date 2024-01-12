#pragma once
#include "Voucher.h"
class Sanatorium :
    public Voucher
{
protected:
    char NameOfSanat[LEN];
public:

    Sanatorium()
    {
        NameOfSanat[0] = '\0';
    }

    Sanatorium(int f,int days, int price, const char* country, const char* city, const char* d, const char* t,int id, const char* sanat) :
        Voucher(f,price, days, country, city, d,t,id)
    {
        strcpy_s(this->NameOfSanat, LEN, sanat);
    }

    ~Sanatorium() {}

    Sanatorium(const Sanatorium& obj) : Voucher(obj)
    {
        strcpy_s(this->NameOfSanat, LEN, obj.NameOfSanat);
    }

    Sanatorium operator=(const Sanatorium& obj);
    bool operator==(const Sanatorium& obj);
    void SetNameOfSanat(const char* a);
    char* GetNameOfSanat();
    friend istream& operator>>(istream& is, Sanatorium& obj);
    friend ostream& operator<<(ostream& out, Sanatorium& obj);
    friend ifstream& operator>>(ifstream& in, Sanatorium& obj);
    friend ofstream& operator<<(ofstream& out, Sanatorium& obj);
    void HeadOfSheet() override;
};

