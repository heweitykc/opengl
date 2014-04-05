#include <iostream>
#include <fstream>
#include "fileio.h"
using namespace std;

void Loader::load(const char *fname)
{
	streampos size;

	ifstream *file = new ifstream(fname, ios::in);
	if (file->is_open()){
		size = file->tellg();
		buff = new char[size];
		file->seekg (0, ios::beg);
		file->read (buff, size);
		file->close();
	}
	else 
		cout << "Unable to open file" <<endl;
	file->close();
	delete file;
}

char* Loader::getbuff()
{
	return buff;
}

void Loader::clear()
{
	delete[] buff;
}