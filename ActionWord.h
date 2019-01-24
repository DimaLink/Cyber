#pragma once
#ifndef ACTION_WORD_H
#define ACTION_WORD_H

enum class EActions : int { NO_ACTION, LOOK, SPEAK };

class ActionWord
{
public:

	ActionWord();
	ActionWord(char * , EActions);
	ActionWord(const ActionWord &);
	~ActionWord();

	void setData(char *, EActions);
	char * getWord();
	EActions getAction();

	ActionWord & operator= (const ActionWord & _right);

private:

	char *  word;
	EActions action;
};

#endif