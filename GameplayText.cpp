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

void GameplayText::setSaveMenu(char * _saveMenu)
{
	clearSaveMenu();
	if (_saveMenu != nullptr)
	{
		int _saveMenuLength = strlen(_saveMenu);
		if (_saveMenuLength > 0)
		{
			saveMenu = new char[_saveMenuLength + 1];
			strcpy_s(saveMenu, _saveMenuLength + 1, _saveMenu);
		}
	}

}

char * GameplayText::getSaveMenu()
{
	return saveMenu;
}

void GameplayText::clearSaveMenu()
{
	if (saveMenu != nullptr)
	{
		delete[] saveMenu;
		saveMenu = nullptr;
	}
}

void GameplayText::setEnterSaveFileName(char * _enterSaveFileName)
{
	clearEnterSaveFileName();
	if (_enterSaveFileName != nullptr)
	{
		int _enterSaveFileNameLength = strlen(_enterSaveFileName);
		if (_enterSaveFileNameLength > 0)
		{
			enterSaveFileName = new char[_enterSaveFileNameLength + 1];
			strcpy_s(enterSaveFileName, _enterSaveFileNameLength + 1, _enterSaveFileName);
		}
	}

}

char * GameplayText::getEnterSaveFileName()
{
	return enterSaveFileName;
}

void GameplayText::clearEnterSaveFileName()
{
	if (enterSaveFileName != nullptr)
	{
		delete[] enterSaveFileName;
		enterSaveFileName = nullptr;
	}
}


void GameplayText::setGameSaved(char * _gameSaved)
{
	clearGameSaved();
	if (_gameSaved != nullptr)
	{
		int _gameSavedLength = strlen(_gameSaved);
		if (_gameSavedLength > 0)
		{
			gameSaved = new char[_gameSavedLength + 1];
			strcpy_s(gameSaved, _gameSavedLength + 1, _gameSaved);
		}
	}

}

char * GameplayText::getGameSaved()
{
	return gameSaved;
}

void GameplayText::clearGameSaved()
{
	if (gameSaved != nullptr)
	{
		delete[] gameSaved;
		gameSaved = nullptr;
	}
}

void GameplayText::setError(char * _error)
{
	clearError();
	if (_error != nullptr)
	{
		int _errorLength = strlen(_error);
		if (_errorLength > 0)
		{
			error = new char[_errorLength + 1];
			strcpy_s(error, _errorLength + 1, _error);
		}
	}

}

char * GameplayText::getError()
{
	return error;
}

void GameplayText::clearError()
{
	if (error != nullptr)
	{
		delete[] error;
		error = nullptr;
	}
}

void GameplayText::setErrorCannotSave(char * _errorCannotSave)
{
	clearErrorCannotSave();
	if (_errorCannotSave != nullptr)
	{
		int _errorCannotSaveLength = strlen(_errorCannotSave);
		if (_errorCannotSaveLength > 0)
		{
			errorCannotSave = new char[_errorCannotSaveLength + 1];
			strcpy_s(errorCannotSave, _errorCannotSaveLength + 1, _errorCannotSave);
		}
	}

}

char * GameplayText::getErrorCannotSave()
{
	return errorCannotSave;
}

void GameplayText::clearErrorCannotSave()
{
	if (errorCannotSave != nullptr)
	{
		delete[] errorCannotSave;
		errorCannotSave = nullptr;
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
	_gameplayText->setSaveMenu(const_cast<char *> ("Сохранить Игру"));
	_gameplayText->setEnterSaveFileName(const_cast<char *> ("Введите имя файла для создания сохранения >> "));
	_gameplayText->setGameSaved(const_cast<char *> ("Игра сохранена"));
	_gameplayText->setError(const_cast<char *> ("Ошибка"));
	_gameplayText->setErrorCannotSave(const_cast<char *> ("Не удается сохранить игру"));
}

void initEnglishGameplayText(GameplayText * _gameplayText)
{

}