#pragma once
#ifndef GAMEPLAY_TEXT_H
#define GAMEPLAY_TEXT_H

#include "Options.h"

class GameplayText
{
public:
	GameplayText();
	~GameplayText();

	void setEnterCommand(char *);
	char * getEnterCommand();
	void clearEnterCommand();

	void setPressAnyKey(char *);
	char * getPressAnyKey();
	void clearPressAnyKey();

	friend void initGameplayText(GameplayText *, ELanguage);

private:
	char * enterCommand;
	char * pressAnyKey;

	friend void initRussianGameplayText(GameplayText *);
	friend void initEnglishGameplayText(GameplayText *);
};


void initGameplayText(GameplayText *, ELanguage);

#endif