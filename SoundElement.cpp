#include <iostream>
#include "SoundElement.h"

SoundElement::SoundElement()
{
	file = nullptr;
	next = nullptr;
}

SoundElement::SoundElement(char * _file, SoundElement * _next)
{
	setFile(_file);
	setNext(_next);
}

SoundElement::~SoundElement()
{
	clearFile(); 
}

void SoundElement::setFile(char * _file)
{
	clearFile();

	if (_file != nullptr)
	{
		int _fileLength = strlen(_file);
		if (_fileLength > 0)
		{
			file = new char[_fileLength +1];
			strcpy_s(file, _fileLength + 1, _file);
		}
	}
}

char * SoundElement::getFile()
{
	return file;
}

void SoundElement::clearFile()
{
	if (file != nullptr)
	{
		delete[] file;
		file = nullptr;
	}
}

void SoundElement::setNext(SoundElement * _next)
{
		next = _next;
}

SoundElement * SoundElement::getNext()
{
	return next;
}




