#pragma once
#include "Sanatorium.h"
class Relax :
    public Sanatorium
{
protected:
    char Activities[LEN];
public:
    Relax() :
        Sanatorium()
    {
        this->Activities[0] = '\0';
    }

    Relax(int f,int days, int price, const char* country, const char* city, const char* d, const char* t, int id, const char* sanat, const char* a) :
        Sanatorium(f,days, price, country, city, d,t,id, sanat)
    {
        strcpy_s(this->Activities, LEN, a);
    }

    ~Relax() {}

    Relax(const Relax& obj) :Sanatorium(obj)
    {
        strcpy_s(this->Activities, LEN, obj.Activities);
    }

    char* GetActivities();
    void SetActivities(char* a);
    Relax operator=(const Relax& obj);
    bool operator==(const Relax& obj);
    bool operator<(Relax& obj);
    bool operator>(Relax& obj);
    friend istream& operator>>(istream& is, Relax& obj);
    friend ostream& operator<<(ostream& out, Relax& obj);
    void ReplaceField(Relax& obj);
    friend ifstream& operator>>(ifstream& in, Relax& obj);
    friend ofstream& operator<<(ofstream& out, Relax& obj);
    Relax PickField();
    void HeadOfSheet() override;
    void Find();
    void Change();
};

