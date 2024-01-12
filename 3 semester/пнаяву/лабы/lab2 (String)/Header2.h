#include<cstring>
#include<iostream>
#include"mystring.h"

String operator+(const char* s, const String& s1);
ostream& operator<< (ostream& os, String& s);
istream& operator>> (istream& is, String& s);
