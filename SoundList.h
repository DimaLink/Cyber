#pragma once
#ifndef SOUND_LIST_H
#define SOUND_LIST_H

#include "SoundElement.h"

class SoundList
{
public:
	SoundList();
	~SoundList();


	void addFirst(char *);
	void addLast(char *);


	SoundElement * getElement(int);
	int getTotal();
	bool isEmpty();


	void deleteFirst();
	void deleteLast();
	void deleteAll();

private:
	SoundElement * first;
};

#endif