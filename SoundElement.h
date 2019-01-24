#pragma once
#ifndef SOUND_ELEMENT_H
#define SOUND_ELEMENT_H

class SoundElement
{
public:
	SoundElement();
	SoundElement(char * , SoundElement * = nullptr);
	~SoundElement();

	void setFile(char *);
	char * getFile();
	void clearFile();

	void setNext(SoundElement *);
	SoundElement * getNext();

private:
	char * file;
	SoundElement * next;

};

#endif
