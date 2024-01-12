#pragma once
#include "Sanatorium.h"
class Therapy :
    public Sanatorium
{
protected:
    char Deseases[LEN];
public:
    Therapy() :Sanatorium()
    {

        Deseases[0] = '\0';
    }

    Therapy(int f,int days, int price, const char* country, const char* city, const char* d, const char* t,int id, const char* sanat, const char* a) :
        Sanatorium(f,days, price, country, city, d,t,id, sanat)
    {

        strcpy_s(this->Deseases, LEN, a);
    }

    Therapy(const Therapy& obj) : Sanatorium(obj)
    {
        strcpy_s(this->Deseases, LEN, obj.Deseases);
    }

    bool operator==(const Therapy& obj);
    bool operator<(Therapy& obj);
    bool operator>(Therapy& obj);

    Therapy operator=(const Therapy& obj);

    void SetDeseases(const char* a);
    char* GetDeseases();

    friend istream& operator>>(istream& is, Therapy& obj);
    friend ostream& operator<<(ostream& out, Therapy& obj);

    friend ifstream& operator>>(ifstream& in, Therapy& obj);
    friend ofstream& operator<<(ofstream& out, Therapy& obj);

    void HeadOfSheet() override;

    Therapy PickField();

    void Find();

    void ReplaceField(Therapy& obj);
    void Change();
};

