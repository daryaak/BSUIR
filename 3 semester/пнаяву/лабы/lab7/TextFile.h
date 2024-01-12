#pragma once
#include "File.h"

template<class T>
class TextFile :public File
{
public:
	TextFile(string _name);
	~TextFile();
	//bool is_open();
	bool feof();
	bool openReadFile();
	bool openWriteFile();
	void readFile(T& temp);
	void writeFile(T& temp);
	void Remote();


};
