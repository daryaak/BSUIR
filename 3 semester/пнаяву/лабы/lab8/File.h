#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class File {
protected:
	string file_name;
	fstream ft;
	ifstream file_i;
	ofstream file_o;

public:
	File(string _name) {
		file_name = _name;
	}

};
