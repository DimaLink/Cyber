#pragma once
#ifndef GAME_H
#define GAME_H

#include "Options.h"
#include "ActionWord.h"
#include "ObjectWord.h"
#include "ObjectList.h"
#include "CommandWord.h"
#include "GameplayText.h"
#include "LanguageSentence.h"
#include "SoundPlayer.h"
#include "Node.h"
#include "SnowBall.h"

enum class EFileTag : int {NO_TAG, NODE_NAME, NODE_CONTENT};
enum class EPreactionsTag : int {NO_PREACTION =0 , GOTO =1, STORYEND =2};

const char NODE [] = "NODE";
const char END_NODE[] = "/NODE";
const char TEXT[] = "TEXT";
const char END_TEXT[] = "/TEXT";
const char COLOR[] = "COLOR";
const char BACKGROUND[] = "BACKGROUND";
const char ACTION[] = "ACTION";
const char LINK[] = "LINK";
const char GOTO[] = "GOTO";
const char PRESS_ANY_KEY[] = "PRESS ANY KEY";
const char FUNCTION[] = "FUNCTION";
const char STORYEND[] = "STORYEND";
const char SOUND[] = "SOUND";



const char saveExtension[] = ".CybSav";

const char  COLORS[16][12] =      { { "LightGrey" },{ "LightBlue" },{ "LightGreen" },{ "LightCyan" },{ "LightRed" },{ "LightPurple" },{ "Black" },{ "Grey" },
								    { "White" },{ "Blue" },{ "Green" },{ "Cyan" },{ "Red" },{ "Purple" },{ "Orange" },{ "Yellow" } };

const char FUNCTIONS[2][64] = { {"Function_01"},{ "Function_02" } };

class Game
{
public:
	Game();
	~Game();

	void setLanguage(ELanguage);
	ELanguage getLanguage();

	void setPath( char *);
	char * getPath();
	void clearPath();

	void setScriptPath(char *);
	char * getScriptPath();
	void clearScriptPath();

	void setSavePath(char *);
	char * getSavePath();
	void clearSavePath();

	void initPaths();
	void initWordList();

	void askUserCommand();
	void checkInputWithWords(char *);
	EActions checkWordWithActionList(char *);
    EObjects checkWordWithObjectList(char *);
	ECommands checkWordWithCommandList(char *);
	LanguageSentence checkActionWithWords(char *);


	void readFile();

	void runGameplay();

	void function_01();
	void function_02();
	void function_03();
	void function_04();
	void function_05();
	void function_06();
	void function_07();

private:

	bool isGameplay;
	

	ELanguage language;
	char * path;
	char * scriptPath;
	char *savePath;

	GameplayText gameplayText;
	LanguageSentence userInputCommand;

	Node currentNode;
	char * targetNode;

	void setTargetNode(char *);
	char * getTargetNode();
	void clearTargetNode();


	ObjectList<ActionWord> actionWordList;
	ObjectList<ObjectWord> objectWordList;
	ObjectList<CommandWord> commandWordList;


	friend void initRussianWordList(Game *);
	friend void initEnglishWordList(Game *);

	int checkKeyword(char * , int, char * );
	void checkParameter(char * , int, char **);
	bool checkNodeName(char *, char *);
	void manageNodeReactionContent(char *);
	void manageNodeActionContent(char *);
	EPreactionsTag manageNodePreActionContent(char * _content);

	ECommands  manageCommands(char * );

	void manageTagText(char *);
	void manageTagAction(char *);
	bool manageTagGoto(char *);
	void manageTagFunction(char *);
	void manageTagPressAnyKey();
	void manageTagSound(char *);
	void manageTagSave();


	WORD getForegroundColor(char *);
	WORD getBackgroundColor(char *);
	void setConsoleTextColor(WORD *, WORD *);

	void callFunction(char *);


	SoundPlayer soundPlayer;

};

#endif
