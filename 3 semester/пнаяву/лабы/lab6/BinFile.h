#pragma once
#include "File.h"

template<class T>
class BinFile :public File
{
public:
	BinFile(string _name = "");
	~BinFile();
	bool is_open();
	bool feof();
	bool openReadFile();
	bool openWriteFile();
	void readFile(T& temp);
	void writeFile(T& temp);
};
