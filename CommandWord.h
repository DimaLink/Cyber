#pragma once
#ifndef COMMAND_WORD_H
#define COMMAND_WORD_H

enum class ECommands : int {NO_COMMAND =0 , SOUND_ON, SOUND_OFF, GAME_EXIT, GAME_SAVE, GAME_LOAD};


class CommandWord
{
public:
	CommandWord();
	CommandWord(char * , ECommands);
	~CommandWord();

	void setWord(char *);
	char * getWord();
	void clearWord();

	void setCommand(ECommands);
	ECommands getCommand();

	void setData(char *, ECommands);

	CommandWord & operator= (const CommandWord &);

private:
	char * word;
	ECommands command;


};


#endif