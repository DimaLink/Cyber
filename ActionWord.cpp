#include <iostream>
#include "ActionWord.h"

ActionWord::ActionWord()
{
	word = nullptr;
	action = EActions::NO_ACTION;

}

ActionWord::ActionWord(char * _word,  EActions _action)
{
	setData(_word, _action);
}

ActionWord::ActionWord(const ActionWord & _copy)
	:ActionWord()
{
	setData(_copy.word, _copy.action);
}


void ActionWord::setData(char * _word, EActions _action)
{
	if (word != nullptr)
	{
		delete[] word;
		word = nullptr;
	}

	if (_word != nullptr)
	{
		int _wordLength = strlen(_word);
		if (_wordLength > 0)
		{
			word = new char[_wordLength + 1];
			strcpy_s(word, _wordLength + 1, _word);

			action = _action;
		}
		else
		{
			action = EActions::NO_ACTION;
		}
	}
	else
	{
		action = EActions::NO_ACTION;
	}
}

char * ActionWord::getWord()
{
	return word;
}



EActions ActionWord::getAction()
{
	return action;
}


ActionWord & ActionWord::operator= (const ActionWord & _right)
{
	if (this == &_right)
	{
		return *this;
	}
	//ActionWord  temp = ActionWord(_right.word, _right.action);
	//return temp;
	setData(_right.word, _right.action);
	return *this;

}

ActionWord::~ActionWord()
{
	if (word != nullptr)
	{
		delete[] word;
		word = nullptr;
	}
}
