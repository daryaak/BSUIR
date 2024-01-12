#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include "InputExeption.h"
#define L 80

using namespace std;
class Reserve
{
protected:
	char Surname[80];
	char PhoneNumber[80];
	int ID_OfTour;
	int AmountOfPeople;
	int FinalPrice;
public:
	Reserve()
	{
		this->Surname[0] = '\0';
		this->PhoneNumber[0] = '\0';
		this->ID_OfTour = 0;
		this->AmountOfPeople = 0;
		this->FinalPrice = 0;
	}

	Reserve(const char* s, const char* p, int i, int peple, int pr)
	{
		strcpy_s(this->Surname, L, s);
		strcpy_s(this->PhoneNumber, L, p);
		this->ID_OfTour = i;
		this->AmountOfPeople = peple;
		this->FinalPrice = pr;
	}

	Reserve(const Reserve& obj)
	{
		strcpy_s(this->Surname, L, obj.Surname);
		strcpy_s(this->PhoneNumber, L, obj.PhoneNumber);
		this->ID_OfTour = obj.ID_OfTour;
		this->AmountOfPeople = obj.AmountOfPeople;
		this->FinalPrice = obj.FinalPrice;
	}
	int GetFinalPrice();
	Reserve operator=(const Reserve& obj);
	friend ostream& operator << (ostream& out, const Reserve& obj);
	friend istream& operator >> (istream& in, Reserve& obj);

	friend ifstream& operator>>(ifstream& in, Reserve& obj);
	friend ofstream& operator<<(ofstream& out, Reserve& obj);

	bool operator==(const Reserve& obj);
	bool operator<(const Reserve& obj);
	bool operator>(const Reserve& obj);
	void HeadOfSheet();
	Reserve PickField();
	void Find();
	void ReplaceField(Reserve& obj);
	void Change();
};

