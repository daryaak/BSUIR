#pragma once
#include "Travel.h"

class Turism :
    public Travel
{
protected:
    char places[LEN];
public:
    Turism() : Travel()
    {
        this->places[0] = '\0';
    }

    Turism(int f,int days, int price, const char* country, const char* city, const char* d, const char* t, char* name,int id, const char* b) :
        Travel(f,days, price, country, city, d, t,id, name)
    {
        strcpy_s(this->places, LEN, b);
    }

    Turism(const Turism& obj) :Travel(obj)
    {
        strcpy_s(this->places, LEN, obj.places);
    }
    Turism operator=(const Turism& obj);
    void ReplaceField(Turism& obj);

    Turism PickField();
    char* GetPlaces();
    void SetPlaces(char* a);

    bool operator==(const Turism& obj);
    bool operator<(Turism& obj);
    bool operator>(Turism& obj);

    friend istream& operator>>(istream& is, Turism& obj);
    friend ostream& operator<<(ostream& out, Turism& obj);

    friend ifstream& operator>>(ifstream& in, Turism& obj);
    friend ofstream& operator<<(ofstream& out, Turism& obj);

    void HeadOfSheet() override;

    void Find();

    void Change();
};

