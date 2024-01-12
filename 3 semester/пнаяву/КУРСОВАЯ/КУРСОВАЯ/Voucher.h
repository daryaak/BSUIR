#pragma once
#include<cstring>
#include <iostream>
#include <ostream>
#include <iomanip>
#include  <conio.h>
#include <windows.h>
#include "Exeption.h"
#include "InputExeption.h"
#include "TextFile.h"
#include "TextFile.cpp"
#define LEN 80
#define MAX_DAYS 30
#define MAX_PLACES 30
#define MAX_PRICE 10000

using namespace std;

class Voucher
{
protected:
	char Country[LEN];
	char City[LEN];
	char DateOfDeparture[LEN];
	char TransCom[LEN];
	int AmountOfDays;
	int AmountOfPlaces;
	int Price;
	int ID;
public:

	Voucher()
	{
		this->AmountOfDays = 0;
		this->AmountOfPlaces = 0;
		this->Price = 0;
		this->Country[0] = '\0';
		this->City[0] = '\0';
		this->DateOfDeparture[0] = '\0';
		this->TransCom[0] = '\0';
		this->ID = 0;

	}

	Voucher(int f,int days, int price, const char* country, const char* city, const char* d,const char* t,int id)
	{
		this->AmountOfDays = days;
		this->AmountOfPlaces = f;
		this->Price = price;
		strcpy_s(this->Country, LEN, country);
		strcpy_s(this->City, LEN, city);
		strcpy_s(this->DateOfDeparture, LEN, d);
		strcpy_s(this->TransCom, LEN, t);
		this->ID = id;
	}

	~Voucher() {}

	Voucher(const Voucher& obj)
	{
		strcpy_s(this->Country, LEN, obj.Country);
		strcpy_s(this->City, LEN, obj.City);
		strcpy_s(this->DateOfDeparture, LEN, obj.DateOfDeparture);
		strcpy_s(this->TransCom, LEN, obj.TransCom);
		this->AmountOfDays = obj.AmountOfDays;
		this->AmountOfPlaces = obj.AmountOfPlaces;
		this->Price = obj.Price;
		this->ID = obj.ID;
	}
	void SetCountry(const char* a);
	void SetDate(char* d);
	void SetCity(const char* a);
	void SetAmountOfDays(int a);
	void SetAmountOfPlaces(int a);
	void SetPrice(int a);
	void SetID(int d);
	void SetTransCom(char* a);

	char* GetTransCom();
	char* GetCountry();
	char* GetCity();
	char* GetDateOfDeparture();
	int GetAmountOfDays();
	int GetAmountOfPlaces();
	int GetPrice();
	int GetID();

	Voucher operator=(const Voucher& obj);
	bool operator==(const Voucher& obj);

	friend istream& operator>>(istream& is, Voucher& obj);
	friend ostream& operator<<(ostream& out, const  Voucher& obj);

	friend ifstream& operator>>(ifstream& in, Voucher& obj);
	friend ofstream& operator<<(ofstream& out, Voucher& obj);

	virtual void HeadOfSheet();
};

