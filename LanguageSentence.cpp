#include <iostream>
#include "LanguageSentence.h"

LanguageSentence::LanguageSentence()
{
	action = EActions::NO_ACTION;
	object = EObjects::NO_OBJECT;
}

LanguageSentence::LanguageSentence(EActions  _action, EObjects  _object)
{
	setData(_action, _object);
}

void LanguageSentence::setAction(EActions _action)
{
	action = _action;
}

void LanguageSentence::setObject(EObjects  _object)
{
	object = _object;
}

void LanguageSentence::setData(EActions  _action, EObjects _object)
{
	setAction(_action);
	setObject(_object);
}

EActions LanguageSentence::getAction()
{
	return action;
}

EObjects  LanguageSentence::getObject()
{
	return object;
}

void LanguageSentence::clearAction()
{
	action = EActions::NO_ACTION;
}

void LanguageSentence::clearObject()
{
	object = EObjects::NO_OBJECT;
}

void LanguageSentence::clearData()
{
	clearAction();
	clearObject();
}


LanguageSentence::~LanguageSentence()
{
 /*nothing to do*/
}




