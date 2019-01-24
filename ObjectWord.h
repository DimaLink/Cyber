#pragma once
#ifndef OBJECT_WORD_H
#define OBJECT_WORD_H


enum class EObjects : int { NO_OBJECT, DOCTOR, ROOM };


class ObjectWord
{
public:

	ObjectWord();
	ObjectWord(char **, int , EObjects);
	ObjectWord(const ObjectWord & );
	~ObjectWord();

	void setData(char **, int, EObjects);
	char * getWord(int);
	char ** getWord();
	int getWordTotal();
	EObjects getObject();

	ObjectWord & operator= (const ObjectWord & );

private:
	char ** word;
	int wordTotal;

	EObjects object;
};

#endif