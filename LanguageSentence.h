#pragma once
#ifndef LANGUAGE_SENTENCE_H
#define LANGUAGE_SENTENCE_H

#include "ActionWord.h"
#include "ObjectWord.h"



class LanguageSentence
{
public:
	LanguageSentence();
	LanguageSentence(EActions , EObjects );
	~LanguageSentence();

	void setAction(EActions );
	void setObject(EObjects );
	void setData(EActions , EObjects );

	EActions  getAction();
	EObjects  getObject();

	void clearAction();
	void clearObject();
	void clearData();

private:
	EActions  action;
	EObjects  object;
};

#endif