#include <iostream>
#include "GameplayText.h"

GameplayText::GameplayText()
{
	enterCommand = nullptr;
}

GameplayText::~GameplayText()
{
	if (enterCommand != nullptr)
	{
		delete[] enterCommand;
		enterCommand = nullptr;
	}
}


void GameplayText::setEnterCommand(char * _enterCommand)
{
	clearEnterCommand();
	if (_enterCommand != nullptr)
	{
		int _enterCommandLength = strlen(_enterCommand);
		if (_enterCommandLength > 0)
		{
			enterCommand = new char[_enterCommandLength +1];
			strcpy_s(enterCommand, _enterCommandLength + 1, _enterCommand);
		}
	}

}

char * GameplayText::getEnterCommand()
{
	return enterCommand;
}


void GameplayText::clearEnterCommand()
{
	if (enterCommand != nullptr)
	{
		delete[] enterCommand;
		enterCommand = nullptr;
	}
}

void GameplayText::setPressAnyKey(char * _pressAnyKey)
{
	clearPressAnyKey();
	if (_pressAnyKey != nullptr)
	{
		int _pressAnyKeyLength = strlen(_pressAnyKey);
		if (_pressAnyKeyLength > 0)
		{
			pressAnyKey = new char[_pressAnyKeyLength + 1];
			strcpy_s(pressAnyKey, _pressAnyKeyLength + 1, _pressAnyKey);
		}
	}

}

char * GameplayText::getPressAnyKey()
{
	return pressAnyKey;
}

void GameplayText::clearPressAnyKey()
{
	if (pressAnyKey != nullptr)
	{
		delete[] pressAnyKey;
		pressAnyKey = nullptr;
	}
}


void initGameplayText(GameplayText * _gameplayText, ELanguage _language)
{
	switch (_language)
	{
	default:
	case ELanguage::RUSSIAN:
	{
		initRussianGameplayText(_gameplayText);
	}
	break;

	case ELanguage::ENGLISH:
	{
		initEnglishGameplayText(_gameplayText);
	}
	break;

	}
}


void initRussianGameplayText(GameplayText * _gameplayText)
{
	_gameplayText->setEnterCommand(const_cast<char *> ("Введите команду >> "));
	_gameplayText->setPressAnyKey(const_cast<char *> ("Нажмите любую клавишу для продолжения "));
}

void initEnglishGameplayText(GameplayText * _gameplayText)
{

}