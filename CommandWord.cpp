#include <iostream>
#include "CommandWord.h"


CommandWord::CommandWord()
{
	word = nullptr;
	command = ECommands::NO_COMMAND;
}

CommandWord::CommandWord(char * _word, ECommands _command)
{
	setWord(_word);
	setCommand(_command);
}

CommandWord::CommandWord(const CommandWord & _copy)
	:CommandWord()
{
	setData(_copy.word, _copy.command);
}

CommandWord::~CommandWord()
{
	clearWord();
}

void CommandWord::setWord(char * _word)
{
	clearWord();

	if (_word != nullptr)
	{
		int _wordLength = strlen(_word);
		if (_wordLength > 0)
		{
			word = new char[_wordLength +1];
			strcpy_s(word, _wordLength +1, _word);
		}
	}
}

char * CommandWord::getWord()
{
	return word;
}

void CommandWord::clearWord()
{
	if (word != nullptr)
	{
		delete[] word;
		word = nullptr;
	}
}

void CommandWord::setCommand(ECommands _command)
{
	command = _command;
}

ECommands CommandWord::getCommand()
{
	return command;
}

void CommandWord::setData(char * _word, ECommands _command)
{
	setWord(_word);
	setCommand(_command);
}

CommandWord & CommandWord::operator= (const CommandWord & _right)
{
	if (this == &_right)
	{
		return *this;
	}
	else
	{
		setData(_right.word, _right.command);
		return *this;
	}
}
