#include <iostream>
#include "ObjectWord.h"



ObjectWord::ObjectWord()
{
	word = nullptr;
	object = EObjects::NO_OBJECT;
	wordTotal = 0;
}

ObjectWord::ObjectWord(char ** _word, int _wordTotal, EObjects _object)
{
	setData(_word, _wordTotal, _object);
}

ObjectWord::ObjectWord(const ObjectWord & _copy)
	: ObjectWord()
{
	setData(_copy.word, _copy.wordTotal, _copy.object);
}


void ObjectWord::setData(char ** _word, int _wordTotal, EObjects _object)
{
	if (word != nullptr)
	{
		for (int i = 0; i < wordTotal; ++i)
		{
			delete[] * (word + i);
			*(word + i) = nullptr;
		}
		delete[] word;
		word = nullptr;
	}

	if (_word != nullptr)
	{
		if (_wordTotal > 0)
		{
			word = new char*[_wordTotal];
			wordTotal = _wordTotal;

			for (int i = 0; i < wordTotal; ++i)
			{
				int _wordLength = strlen(*(_word + i));
				//if (_wordLength > 0)
				//{
				*(word + i) = new char[_wordLength + 1];
				strcpy_s(*(word + i), _wordLength + 1, *(_word + i));
				//}
				//else
				//{

				//}
			}
			object = _object;
		}
		else
		{
			object = EObjects::NO_OBJECT;
		}
	}
	else
	{
		object = EObjects::NO_OBJECT;
	}
}

char * ObjectWord::getWord(int _index)
{
	if ((_index >= 0) && (_index < wordTotal))
	{
		return *(word + _index);
	}
	else
	{
		return nullptr;
	}
}

char ** ObjectWord::getWord()
{
	return word;
}

int ObjectWord::getWordTotal()
{
	return wordTotal;
}

EObjects ObjectWord::getObject()
{
	return object;
}

ObjectWord &  ObjectWord::operator= (const ObjectWord & _right)
{
	if (this == &_right)
	{
		return *this;
	}
	else
	{
		setData(_right.word, _right.wordTotal, _right.object);
		return *this;
	}

}

ObjectWord::~ObjectWord()
{
	if (word != nullptr)
	{
		for (int i = 0; i < wordTotal; ++i)
		{
			delete[] * (word + i);
			*(word + i) = nullptr;
		}
		delete[] word;
		word = nullptr;
	}
}