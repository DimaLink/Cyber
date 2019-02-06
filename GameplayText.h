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

	void setSaveMenu(char *);
	char * getSaveMenu();
	void clearSaveMenu();

	void setEnterSaveFileName(char *);
	char * getEnterSaveFileName();
	void clearEnterSaveFileName();

	void setGameSaved(char *);
	char * getGameSaved();
	void clearGameSaved();

	void setError(char *);
	char * getError();
	void clearError();

	void setErrorCannotSave(char *);
	char * getErrorCannotSave();
	void clearErrorCannotSave();
	

	friend void initGameplayText(GameplayText *, ELanguage);

private:
	char * enterCommand;
	char * pressAnyKey;
	char * saveMenu;
	char * enterSaveFileName;
	char * gameSaved;
	char * error;
	char * errorCannotSave;

	friend void initRussianGameplayText(GameplayText *);
	friend void initEnglishGameplayText(GameplayText *);
};


void initGameplayText(GameplayText *, ELanguage);

#endif