#include <iostream>
#include <ctime>
#include "Windows.h"
#include "Functions.h"
#include "Game.h"


 



Game::Game()
{
	language = ELanguage::RUSSIAN;
	path = nullptr;
	scriptPath = nullptr;
	targetNode = nullptr;

	initPaths();
	initWordList();
	initGameplayText(&gameplayText, language);
}

Game::~Game()
{
	/*nothing to do*/
}

void Game::setLanguage(ELanguage _language)
{
	language = _language;
}

ELanguage Game::getLanguage()
{
	return language;
}


void Game::setPath(char * _path)
{
	if (path != nullptr)
	{
		delete[] path;
		path = nullptr;
	}

	if (_path != nullptr)
	{
		int _pathLength = strlen(_path);
		if (_pathLength > 0)
		{
			path = new char[_pathLength + 1];
			strcpy_s(path, _pathLength + 1, _path);
		}
		else
		{
			/*nothing to do*/
		}
	}
	else
	{
		/*nothjing to do*/
	}
}

char * Game::getPath()
{
	return path;
}

void Game::setScriptPath(char *  _scriptPath)
{
	if (scriptPath != nullptr)
	{
		delete[] scriptPath;
		scriptPath = nullptr;
	}

	if (_scriptPath != nullptr)
	{
		int _scriptPathLength = strlen(_scriptPath);
		if (_scriptPathLength > 0)
		{
			scriptPath = new char[_scriptPathLength + 1];
			strcpy_s(scriptPath, _scriptPathLength + 1, _scriptPath);
		}
		else
		{
			/*nothing todo*/
		}
	}
	else
	{
		/*nothing to do*/
	}

}

char * Game::getScriptPath()
{
	return scriptPath;
}

void Game::initPaths()
{

	char buffer[4096] = "";

	GetModuleFileNameA(NULL, buffer, sizeof(buffer) / sizeof(*(buffer + 0)));

	int bufferLength = strlen(buffer);
	if (bufferLength > 0)
	{
		for (int i = bufferLength - 1; i >= 0; i--)
		{
			if (*(buffer + i) == '\\')
			{
				*(buffer + i) = '\0';
				break;
			}
		}

		setPath(buffer);


		switch (language)
		{
		default:
		case ELanguage::RUSSIAN:
		{
			strcat_s(buffer,4096,"\\Data\\ScriptRus.txt");
			setScriptPath(buffer);
		}
		break;

		case ELanguage::ENGLISH:
		{
			strcat_s(buffer, 4096, "\\Data\\ScriptEng.txt");
			setScriptPath(buffer);
		}
		break;

		}
	}
}

void Game::initWordList()
{
	switch (language)
	{
	default:
	case ELanguage::RUSSIAN:
	{
		initRussianWordList(this);
	}
	break;

	case ELanguage::ENGLISH:
	{
		initEnglishWordList(this);
	}
	break;
	}
}


void Game::askUserCommand()
{
	char userInput[64] = "";
	bool isAskUser = true;
	
	while (isAskUser == true)
	{
		strcpy_s(userInput, 64, "");
		std::cout << gameplayText.getEnterCommand();
		//std::cin >> userInput ;
		std::cin.getline(userInput, 64);
		checkInputWithWords(userInput);
		if ((userInputCommand.getAction() == EActions::NO_ACTION) || (userInputCommand.getObject() == EObjects::NO_OBJECT))
		{
			isAskUser = true;
			system("cls");
			manageTagText(currentNode.getContent());
		}
		else
		{
			isAskUser = false;
		}
	}




}

void Game::checkInputWithWords( char *  _input)
{
	userInputCommand.clearData();

	if (_input != nullptr)
	{
		int _inputLength = strlen(_input);
		if (_inputLength > 0)
		{
			int wordLength = 0;
			int wordStart = 0;
			int wordCounter = 0;

			char * word = nullptr;

			for (int i = 0; i <= _inputLength; ++i)
			{
				if ((*(_input + i) == ' ') || (i == _inputLength))
				{
					wordCounter++;
					
					word = new char[wordLength +1];
					strncpy_s(word, wordLength + 1, _input+ wordStart, wordLength);
					

					if (wordCounter == 1)
					{
						userInputCommand.setAction(checkWordWithActionList(word));
						delete [] word;
						word = nullptr;
					}
					else
					{
						if (wordCounter >= 2)
						{
							userInputCommand.setObject(checkWordWithObjectList(word));
							delete[] word;
							word = nullptr;
						}
						else
						{
							break;
						}
					}
					wordLength = 0;
					wordStart = i + 1;
				}
				else
				{
					wordLength++;
				}
			}
		}
	}
}

LanguageSentence Game::checkActionWithWords(char * _action)
{

	LanguageSentence result;
	if (_action != nullptr)
	{
		int _inputLength = strlen(_action);
		if (_inputLength > 0)
		{
			int wordLength = 0;
			int wordStart = 0;
			int wordCounter = 0;

			char * word = nullptr;

			for (int i = 0; i <= _inputLength; ++i)
			{
				if ((*(_action + i) == ' ') || (i == _inputLength))
				{
					wordCounter++;

					word = new char[wordLength + 1];
					strncpy_s(word, wordLength + 1, _action + wordStart, wordLength);


					if (wordCounter == 1)
					{
						result.setAction(checkWordWithActionList(word));
 
						delete[] word;
						word = nullptr;
					}
					else
					{
						if (wordCounter == 2)
						{
							result.setObject(checkWordWithObjectList(word));
							delete[] word;
							word = nullptr;
						}
						else
						{
							break;
						}
					}
					wordLength = 0;
					wordStart = i + 1;
				}
				else
				{
					wordLength++;
				}
			}
		}
	}
	return result;
 
	
}

EActions Game::checkWordWithActionList(char * _word)
{
	int listSize = actionWordList.getTotal();
	int actionLength = 0;
	int inputLength = strlen(_word);
	char * action = nullptr;
	int wordIdentityIndex = 0;

	if (listSize > 0)
	{
		for (int i = 1; i <= listSize; ++i)
		{
			action = ((actionWordList.getElement(i))->getObject())->getWord();
			actionLength = strlen(action);
				if (actionLength == inputLength)
				{
					for (int j = 0; j < actionLength; ++j)
					{
						int left = tolower(*(action + j));
						int right = tolower(*(_word + j));
						if (  left != right )
						{
							wordIdentityIndex = 0;
							break;
						}
						else
						{
							wordIdentityIndex++;
							if (wordIdentityIndex == actionLength)
							{
								return  ((actionWordList.getElement(i))->getObject())->getAction();
							}
						}
					}
				}
		}
		return EActions::NO_ACTION;
	}
}

EObjects Game::checkWordWithObjectList(char * _word)
{
	int listSize = objectWordList.getTotal();
	int objectLength = 0;
	int inputLength = strlen(_word);
	char * object = nullptr;
	int wordIdentityIndex = 0;
	int wordsInItem = 0;

	if (listSize > 0)
	{
		for (int i = 1; i <= listSize; ++i)
		{

			wordsInItem = ((objectWordList.getElement(i))->getObject())->getWordTotal();
				for (int j = 0; j < wordsInItem; j++)
				{
					objectLength = 0;
					wordIdentityIndex = 0;
					object = ((objectWordList.getElement(i))->getObject())->getWord(j);
					objectLength = strlen(object);
					if (objectLength == inputLength)
					{
						for (int k = 0; k < objectLength; ++k)
						{
							if (tolower(*(object + k)) != tolower (*(_word + k)))
							{
								wordIdentityIndex = 0;
								break;
							}
							else
							{
								wordIdentityIndex++;
								if (wordIdentityIndex == objectLength)
								{
									return  ((objectWordList.getElement(i))->getObject())->getObject();
								}
							}
						}
					}
				}

		}
		return EObjects::NO_OBJECT;
	}
}


ECommands Game::checkWordWithCommandList(char * _word)
{
	int listSize = commandWordList.getTotal();
	int commandLength = 0;
	int inputLength = strlen(_word);
	char * command = nullptr;
	int wordIdentityIndex = 0;

	if (listSize > 0)
	{
		for (int i = 1; i <= listSize; ++i)
		{
			command = ((commandWordList.getElement(i))->getObject())->getWord();
			commandLength = strlen(command);
			if (commandLength == inputLength)
			{
				for (int j = 0; j < commandLength; ++j)
				{
					int left = tolower(*(command + j));
					int right = tolower(*(_word + j));
					if (left != right)
					{
						wordIdentityIndex = 0;
						break;
					}
					else
					{
						wordIdentityIndex++;
						if (wordIdentityIndex == commandLength)
						{
							return  ((commandWordList.getElement(i))->getObject())->getCommand();
						}
					}
				}
			}
		}
		return ECommands::NO_COMMAND;
	}
}

void Game::readFile()
{
	FILE * file = nullptr;

	fopen_s(&file,scriptPath,"rb");
	
	char c = ' '; int integer = 0;
	EFileTag fileTag = EFileTag::NO_TAG;
	fpos_t startTagPosition = -1;
	fpos_t endTagPosition = -1;
	int dataLength = 0;

	long long startContentPosition = -1, endContentPosition = -1;
    

	while ( (integer = fgetc(file)) != EOF)
	{
		c = (char)integer;

		if (fileTag == EFileTag::NO_TAG)
		{
			if (c == '<')
			{
				fgetpos(file,&startTagPosition);
				startTagPosition--;
			}
			else
			{
				if (c == '>')
				{
					fgetpos(file, &endTagPosition);
					long tagLength = endTagPosition - startTagPosition;
					char *tag = new char[tagLength+1];
					fsetpos(file,&startTagPosition);
					fread_s(tag, tagLength + 1, sizeof(char), tagLength,file);
					if (checkNodeName(tag, targetNode) == true)
					{
						fileTag = EFileTag::NODE_NAME;				
						delete[] tag;
						tag = nullptr;
						startContentPosition = -1;
						endContentPosition = -1;
					}
				}
			}
		}
		else
		{
			if (fileTag == EFileTag::NODE_NAME)
			{
				if (startContentPosition == -1)
				{
					fgetpos(file, &startTagPosition);
					startContentPosition = startTagPosition;
				}

				if (c == '<')
				{
					fgetpos(file, &startTagPosition);
					startTagPosition--;
				}
				else
				{
					if (c == '>')
					{
						fgetpos(file, &endTagPosition);
						long tagLength = endTagPosition - startTagPosition;						
						char *tag = new char[tagLength + 1];

						fsetpos(file, &startTagPosition);
						fread_s(tag, tagLength + 1, sizeof(char), tagLength, file);
						if (checkKeyword(tag,0, const_cast<char *>(END_NODE)) >=0)
						{
							fileTag = EFileTag::NODE_CONTENT;
							endContentPosition = endTagPosition;

							int contentLength = endContentPosition - startContentPosition;
							char * content = new char[contentLength +1];
							fsetpos(file,&startContentPosition);
							fread_s(content, contentLength + 1,sizeof(char), contentLength, file);
							currentNode.setContent(content);
							delete[] content;
							content = nullptr;

							manageNodeReactionContent(currentNode.getContent());

							delete[] tag;
							tag = nullptr;
							break;
						}
						delete[] tag;
						tag = nullptr;
					}
				}
			}
		}
	}
	fclose(file);
}

/*search in tag like "< NODE = "123" > for keyword
  return index of first letter of keyword or -1;
*/
int Game::checkKeyword(char * _text, int _startIndex, char *_keyword)
{
	if (_text != nullptr)
	{
		if (_keyword != nullptr)
		{
			int _textLength = strlen(_text);
			int _keywordLength = strlen(_keyword);

			if ((_textLength > 0) && (_keywordLength > 0))
			{
				if ((_startIndex >= 0) && (_startIndex <= _textLength - _keywordLength ))
				{
					int j = 0;

					for (int i = _startIndex; i < _textLength; ++i)
					{

						if (  tolower(*(_text + i)) == tolower((*(_keyword + j))))
						{
							j++;
							if (j == _keywordLength)
							{
								return (i - _keywordLength + 1);
							}
						}
						else
						{							
							if (j > 0)
							{
								i--;
							}
							j = 0;
						}
					}
				}				
			}
		}
	}
	return -1;
}

void Game::checkParameter(char * _text,int _startIndex ,char ** _parameter)
{
	if (_text != nullptr)
	{
		int _textLength = strlen(_text);
		if (_textLength > 0)
		{
			if ((_startIndex >= 0) && (_startIndex < _textLength) )
			{
				if (*_parameter != nullptr)
				{
					delete[] * _parameter;
					*_parameter = nullptr;
				}

				int parameterPhase = 0;
				int wordLength = 0;
				int wordStart = 0;
				for (int i = _startIndex; i < _textLength; ++i)
				{
					if (parameterPhase == 0)
					{
						if (*(_text + i) == '=')
						{
							parameterPhase = 1;
						}
					}
					else
					{
						if (parameterPhase == 1)
						{
							if (*(_text + i) == '"')
							{
								parameterPhase = 2;
								wordStart = i + 1;
								wordLength = 0;
							}
						}
						else
						{
							if (parameterPhase == 2)
							{
								if (*(_text + i) == '"')
								{
									if (wordLength > 0)
									{
										*_parameter = new char[wordLength +1];
										strncpy_s(*_parameter, wordLength + 1, _text+ wordStart, wordLength);
									}
									parameterPhase = -1;
								}
								else
								{
									wordLength++;
								}
							}
						}
					}
				}

			}


		}

	}
}

bool Game::checkNodeName(char * _node, char * _targetName)
{
	if (_node != nullptr)
	{
		int nodeStart = -1;
		int nodeLength = strlen(_node);
		char * parameter = nullptr;
		
		nodeStart = checkKeyword(_node, 0,const_cast<char *>(NODE));
		if (nodeStart >= 0)
		{
			checkParameter(_node, nodeStart+3,&parameter);
			if (parameter != nullptr)
			{
				int parameterLength = strlen(parameter);
				if (parameterLength > 0)
				{
					if (_targetName != nullptr)
					{
						 int result = checkKeyword(parameter,0, _targetName);
						if (result >=0)
						{
							currentNode.setName(parameter);
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						currentNode.setName(parameter);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Game::manageNodeReactionContent(char * _content)
{
	bool textTag = false;
	bool actionTag = false;


	if (_content != nullptr)
	{
		int _contentLength = strlen(_content);
		if (_contentLength > 0)
		{
			int startTagPosition = 0, endTagPosition = 0;
			int startDataPosition = 0, endDataPosition = 0;

			for (int i = 0; i < _contentLength; ++i)
			{
				char c = *(_content+i);

				if (c == '<')
				{
					startTagPosition = i;
					if (textTag == false)
					{
						startDataPosition = i;
					}
				}
				else
				{
					if (c == '>')
					{
						endTagPosition = i;
						int tagLength = endTagPosition - startTagPosition+1;
						char *tag = new char[tagLength +1];
						strncpy_s(tag, tagLength + 1,_content+ startTagPosition, tagLength);


						if (textTag == false)
						{
							if (checkKeyword(tag, 0, const_cast<char *>(TEXT)) >= 0)
							{
								textTag = true;
								//startDataPosition = i;
							}

 
							if (checkKeyword(tag, 0, const_cast<char *>(PRESS_ANY_KEY)) >= 0)
							{
								int dataLength = endTagPosition - startTagPosition;

								char * data = new char[dataLength + 1];
								strncpy_s(data, dataLength + 1, _content + startTagPosition, dataLength);
								manageTagPressAnyKey();
								endDataPosition = 0;
								startDataPosition = 0;
								endTagPosition = 0;
								startTagPosition = 0;
							}

							if (checkKeyword(tag, 0, const_cast<char *>(SOUND)) >= 0)
							{
								int dataLength = endTagPosition - startTagPosition;

								char * data = new char[dataLength + 1];
								strncpy_s(data, dataLength + 1, _content + startTagPosition, dataLength);
								manageTagSound(data);
								endDataPosition = 0;
								startDataPosition = 0;
								endTagPosition = 0;
								startTagPosition = 0;
							}

							if (checkKeyword(tag, 0, const_cast<char *>(FUNCTION)) >= 0)
							{
								int dataLength = endTagPosition - startTagPosition;

								char * data = new char[dataLength + 1];
								strncpy_s(data, dataLength + 1, _content + startTagPosition, dataLength);
								manageTagFunction(data);
								endDataPosition = 0;
								startDataPosition = 0;
								endTagPosition = 0;
								startTagPosition = 0;
							}


						}
						else
						{
							if (checkKeyword(tag, 0, const_cast<char *>(END_TEXT)) >= 0)
							{
								textTag = false;
								
								endDataPosition = endTagPosition;
								int dataLength = endDataPosition - startDataPosition+1;

								char * data = new char[dataLength +1];
								strncpy_s(data, dataLength +1, _content+startDataPosition, dataLength);
								manageTagText(data);
								endDataPosition = 0;
								startDataPosition = 0;
								endTagPosition =0;
								startTagPosition = 0;

							}
						}

						delete[] tag;
						tag = nullptr;
					}
				}
			}
		}
	}

}

EPreactionsTag Game::manageNodePreActionContent(char * _content)
{
	EPreactionsTag preactionTag = EPreactionsTag::NO_PREACTION;

	if (_content != nullptr)
	{
		int _contentLength = strlen(_content);
		if (_contentLength > 0)
		{
			char c = 0;
			int startTagPosition = -1, endTagPosition = -1;

			for (int i = 0; i < _contentLength; ++i)
			{
				c = *(_content + i);
				if (c == '<')
				{
					startTagPosition = i;
				}
				else
				{
					if (c == '>')
					{
						endTagPosition = i;
						int tagLength = endTagPosition - startTagPosition + 1;
						char * tag = new char[tagLength + 1];
						strncpy_s(tag, tagLength + 1, _content + startTagPosition, tagLength);

							if (checkKeyword(tag, 0, const_cast <char *> (GOTO)) >= 0)
							{
								if (manageTagGoto(tag) == true)
								{
									preactionTag = EPreactionsTag::GOTO;
								}
							}
							else
							{
								if (checkKeyword(tag, 0, const_cast <char *> (STORYEND)) >= 0)
								{
									preactionTag = EPreactionsTag::STORYEND;
								}
							}

						delete[] tag;
						tag = nullptr;

						startTagPosition = -1;
						endTagPosition = -1;
					}
				}
			}
		}
	}
	return preactionTag;
}


void Game::manageNodeActionContent(char * _content)
{
	if (_content != nullptr)
	{
		int _contentLength = strlen(_content);
		if (_contentLength > 0)
		{
			char c = 0;
			int startTagPosition = -1, endTagPosition = -1; 

			for (int i = 0; i < _contentLength; ++i)
			{
				c = *(_content + i);
				if (c == '<')
				{
					startTagPosition = i;
				}
				else
				{
					if (c == '>')
					{
						endTagPosition = i;
						int tagLength = endTagPosition - startTagPosition + 1;
						char * tag = new char[tagLength +1];
						strncpy_s(tag, tagLength + 1 , _content + startTagPosition, tagLength);

						if (checkKeyword(tag, 0, const_cast <char *> (ACTION)) >= 0)
						{
							manageTagAction(tag);
						}
						else
						{
							/*nothing to do*/
						}

						delete[] tag;
						tag = nullptr;

						startTagPosition = -1;
						endTagPosition = -1;
					}
				}
			}
		}
	}
}

void Game::manageTagText(char * _text)
{
	if (_text != nullptr)
	{
		int _textLength = strlen(_text);
		if (_textLength > 0)
		{
			bool startTextTagPosition = false;
			int startTextContentPosition = -1;
			char c = ' ';
			int startTagPosition = 0, endTagPosition = 0;
			WORD foregroundColor = 0, backgroundColor = 0;


			for (int i = 0; i < _textLength; ++i)
			{
				c = *(_text + i);
				if (c == '<')
				{
					startTagPosition = i;
				}
				else
				{
					if (c == '>')
					{
						endTagPosition = i;
						int tagLength = endTagPosition - startTagPosition+1;
						char * tag = new char[tagLength+1];
						strncpy_s(tag, tagLength+1, _text+ startTagPosition, tagLength);
						if (startTextTagPosition == false)
						{
							int keywordTextIndex = checkKeyword(tag, 0, const_cast<char *>(TEXT));
							int keywordNonTextIndex = 0;

							if (keywordTextIndex >= 0)
							{
								startTextTagPosition = true;
								startTextContentPosition = i+1;
								keywordNonTextIndex = checkKeyword(tag, keywordTextIndex, const_cast<char *>(COLOR));
								if (keywordNonTextIndex >= 0)
								{
									char * parameter = nullptr;
									checkParameter(tag, keywordNonTextIndex, &parameter);
									if (parameter != nullptr)
									{
										int paramenterLength = strlen(parameter);
										if (paramenterLength > 0)
										{
											foregroundColor = getForegroundColor(parameter);
										}
									}

									delete[] parameter;
									parameter = nullptr;
								}
								else
								{
									foregroundColor = FOREGROUND_GREEN;
								}

								keywordNonTextIndex = checkKeyword(tag, keywordTextIndex, const_cast<char *>(BACKGROUND));
								if (keywordNonTextIndex >= 0)
								{
									char * parameter = nullptr;
									checkParameter(tag, keywordNonTextIndex, &parameter);
									if (parameter != nullptr)
									{
										int paramenterLength = strlen(parameter);
										if (paramenterLength > 0)
										{
											backgroundColor = getBackgroundColor(parameter);
										}
									}

									delete[] parameter;
									parameter = nullptr;
								}
								else
								{
									backgroundColor = 0; //black
								}

								setConsoleTextColor(&foregroundColor, &backgroundColor);

							}
						}
						else
						{
							int keywordTextIndex = checkKeyword(tag, 0, const_cast<char *>(END_TEXT));
							if (keywordTextIndex >= 0)
							{
								int contentLength = i - 7 - startTextContentPosition +1;
								char * content = new char[contentLength + 1];
								strncpy_s(content, contentLength + 1, _text + startTextContentPosition, contentLength);

								std::cout << content;

								delete[] content;
								content = nullptr;
								startTextTagPosition = false;
							}
						}
						delete[] tag;
						tag = nullptr;
					}
					else
					{
						if (startTextTagPosition == true)
						{
							if (startTextContentPosition == -1)
							{
								startTextContentPosition = i;
							}
							else
							{


							}
						}
					}
				}
			}
		}
	}
}

void Game::manageTagSound(char * _sound)
{
	if (_sound != nullptr)
	{
		int _soundLength = strlen(_sound);
		if (_soundLength > 0)
		{
			int soundTagIndex = checkKeyword(_sound,0,const_cast <char *> (SOUND));
			if (soundTagIndex >= 0)
			{
				char * parameter = nullptr;
				checkParameter(_sound, soundTagIndex + strlen (SOUND),&parameter);
				if (parameter != nullptr)
				{
					int fileLength = strlen(parameter) + strlen("Data\\");
					char * pathToFile = new char[fileLength +1];
					strcpy_s(pathToFile, fileLength +1,"Data\\");
					strcat_s(pathToFile,fileLength + 1, parameter);

					soundPlayer.setSound(pathToFile);

					delete[] pathToFile;
					pathToFile = nullptr;

					delete[] parameter;
					parameter = nullptr;
				}
			}
		}
	}
}


void Game::setTargetNode(char * _targetNode)
{
	clearTargetNode();

	if (_targetNode != nullptr)
	{
		int _targetNodeLength = strlen(_targetNode);
		if (_targetNodeLength > 0)
		{
			targetNode = new char[_targetNodeLength +1];
			strcpy_s(targetNode, _targetNodeLength + 1, _targetNode);
		}
	}
}


char * Game::getTargetNode()
{
	return targetNode;
}

void Game::clearTargetNode()
{
	if (targetNode != nullptr)
	{
		delete[] targetNode;
		targetNode = nullptr;
	}
}

void  Game::manageTagAction(char * _action)
{
	if ((userInputCommand.getAction() != EActions::NO_ACTION) && (userInputCommand.getObject() != EObjects::NO_OBJECT))
	{
		if (_action != nullptr)
		{
			int _actionLength = strlen(_action);
			if (_actionLength > 0)
			{
				for (int i = 0; i < _actionLength; ++i)
				{
					int tagActionIndex = checkKeyword(_action,0,const_cast<char *> (ACTION));
					
					char * parameterAction = nullptr;
					checkParameter(_action, tagActionIndex +strlen (ACTION), &parameterAction);

					if (parameterAction != nullptr)
					{
                        LanguageSentence languageSentence = checkActionWithWords(parameterAction);

						if ((languageSentence.getAction() != EActions::NO_ACTION) && (languageSentence.getObject() != EObjects::NO_OBJECT))
						{
							if ((languageSentence.getAction() == userInputCommand.getAction()) && (languageSentence.getObject() == userInputCommand.getObject()))
							{
								int tagLinkIndex = checkKeyword(_action, 0, const_cast<char *> (LINK));
								if (tagLinkIndex >= 0)
								{
									char * parameterLink = nullptr;
									checkParameter(_action, tagLinkIndex + strlen(LINK), &parameterLink);
									if (parameterLink != nullptr)
									{
										setTargetNode(parameterLink);

										delete[] parameterLink;
										parameterLink = nullptr;
									}
								}
							}
						}
						delete parameterAction;
						parameterAction = nullptr;
					}
				}
			}
		}
	}
}


bool Game::manageTagGoto(char * _goto)
{
	if (_goto != nullptr)
	{
		int _gotoLength = strlen(_goto);
		if (_gotoLength >0)
		{
			for (int i = 0; i < _gotoLength; ++i)
			{
				int tagGotoIndex = checkKeyword(_goto, 0, const_cast<char *> (GOTO));
				if (tagGotoIndex >= 0)
				{
					char *parameter = nullptr;
					checkParameter(_goto, tagGotoIndex +strlen (GOTO),&parameter);

					if (parameter != nullptr)
					{
						setTargetNode(parameter);


						delete[]  parameter;
						parameter = nullptr;

						return true;
					}
				}
			}
		}
	}
	return false;
}



void Game::manageTagFunction (char *_function)
{
	if (_function != nullptr)
	{
		int tagFunctionIndex = checkKeyword(_function,0,const_cast <char *> (FUNCTION));
		if (tagFunctionIndex >= 0)
		{
			char * parameter = nullptr;
			checkParameter(_function, tagFunctionIndex +strlen (FUNCTION), &parameter);

			if (parameter != nullptr)
			{
				callFunction(parameter);

				delete[] parameter;
				parameter = nullptr;
			}
		}
	}
}

void Game::manageTagPressAnyKey()
{
	//std::cout << gameplayText.getPressAnyKey();
	system("pause");
}


void Game::runGameplay()
{
	bool isGameplay = true;
	EPreactionsTag preactionsTag = EPreactionsTag::NO_PREACTION;
	while (isGameplay == true)
	{
	   system("cls");
	   readFile();
	   preactionsTag = manageNodePreActionContent(currentNode.getContent());
	   if (preactionsTag  == EPreactionsTag::NO_PREACTION)
	   {
		   askUserCommand();
		   manageNodeActionContent(currentNode.getContent());
	   }
	   else
	   {
		   if (preactionsTag == EPreactionsTag::STORYEND)
		   {
			   isGameplay = false;
		   }
	   }
	}

}

WORD Game::getForegroundColor(char * _color)
{
	WORD  color = FOREGROUND_GREEN;

	if (_color != nullptr)
	{
		int _colorLength = strlen(_color);
		if (_colorLength > 0)
		{
			//LightGrey
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 0))) >= 0)
			{
				color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
				return color;
			}

			//LightBlue
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 1))) >= 0)
			{
				color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				return color;
			}

			//LightGreen
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 2))) >= 0)
			{
				color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				return color;
			}

			//LightCyan
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 3))) >= 0)
			{
				color = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				return color;
			}

			//LightRed
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 4))) >= 0)
			{
				color = FOREGROUND_RED | FOREGROUND_INTENSITY;
				return color;
			}

			//LightPurple
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 5))) >= 0)
			{
				color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				return color;
			}

			//Black
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 6))) >= 0)
			{
				color = 0;
				return color;
			}

			//Grey
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 7))) >= 0)
			{
				color = FOREGROUND_INTENSITY;
				return color;
			}

			//White
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 8))) >= 0)
			{
				color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				return color;
			}

			//Blue
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 9))) >= 0)
			{
				color = FOREGROUND_BLUE;
				return color;
			}

			//Green
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 10))) >= 0)
			{
				color = FOREGROUND_GREEN;
				return color;
			}

			//Cyan
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 11))) >= 0)
			{
				color = FOREGROUND_GREEN;
				return color;
			}

			//Red
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 12))) >= 0)
			{
				color = FOREGROUND_RED;
				return color;
			}

			//Purple
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 13))) >= 0)
			{
				color = FOREGROUND_RED | FOREGROUND_BLUE;
				return color;
			}

			//Orange
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 14))) >= 0)
			{
				color = FOREGROUND_RED | FOREGROUND_GREEN;
				return color;
			}

			//Yellow
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 15))) >= 0)
			{
				color = color = FOREGROUND_RED | FOREGROUND_GREEN;
				return color;
			}
		}
	}
	return color;
}

WORD Game::getBackgroundColor(char * _color)
{
	WORD  color = BACKGROUND_GREEN;

	if (_color != nullptr)
	{
		int _colorLength = strlen(_color);
		if (_colorLength > 0)
		{
			//LightGrey
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 0))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
				return color;
			}

			//LightBlue
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 1))) >= 0)
			{
				color = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				return color;
			}

			//LightGreen
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 2))) >= 0)
			{
				color = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
				return color;
			}

			//LightCyan
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 3))) >= 0)
			{
				color = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				return color;
			}

			//LightRed
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 4))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_INTENSITY;
				return color;
			}

			//LightPurple
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 5))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				return color;
			}

			//Black
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 6))) >= 0)
			{
				color = 0;
				return color;
			}

			//Grey
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 7))) >= 0)
			{
				color = BACKGROUND_INTENSITY;
				return color;
			}

			//White
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 8))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				return color;
			}

			//Blue
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 9))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				return color;
			}

			//Green
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 10))) >= 0)
			{
				color = BACKGROUND_GREEN;
				return color;
			}

			//Cyan
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 11))) >= 0)
			{
				color = BACKGROUND_GREEN;
				return color;
			}

			//Red
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 12))) >= 0)
			{
				color = BACKGROUND_RED;
				return color;
			}

			//Purple
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 13))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_BLUE;
				return color;
			}

			//Orange
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 14))) >= 0)
			{
				color = BACKGROUND_RED | BACKGROUND_GREEN;
				return color;
			}

			//Yellow
			if (checkKeyword(_color, 0, const_cast<char *>(*(COLORS + 15))) >= 0)
			{
				color = color = BACKGROUND_RED | BACKGROUND_GREEN;
				return color;
			}
		}
	}
	return color;
}


void Game::setConsoleTextColor(WORD * _foreground, WORD * _background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, *_foreground | *_background);
}


void Game::callFunction(char * _function)
{
	if (_function != nullptr)
	{
		int _functionLength = strlen(_function);
		if (_functionLength >0)
		{
          

			//function_01
			if (checkKeyword(_function, 0, const_cast<char *> (*(FUNCTIONS + 0)) ) >= 0)
			{
				function_01();
			}
			else
			{
				//function_02
				if (checkKeyword(_function, 0, const_cast<char *> (*(FUNCTIONS + 1))) >= 0)
				{
					function_02();
				}
			}
		}
	}
}

void Game::function_01()
{
	int left = 0, top = 0, right = 640, bottom = 480, hSpace = 60,vSpace = 60;


	HWND console = GetConsoleWindow();
	HDC hdcConsole = GetDC(console);

	LPPOINT lpPoint = nullptr;

	//dark green
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 100, 0));
	SelectObject(hdcConsole, pen);

	
	float k = 0;
	//for (int j = 0; j < 10000000000; ++j)

	manageTagPressAnyKey();

	for (int j = 0; j < 5; ++j)
	{
			Sleep(500);

			system("cls");

			if (j % 2 == 0)
			{
				k = 0.5;
				MoveToEx(hdcConsole, left + 2 * hSpace  , top + 2 * vSpace , lpPoint);
				LineTo(hdcConsole, right - 2 * hSpace  , top + 2 * vSpace  );

				MoveToEx(hdcConsole, right - 2 * hSpace  , top + 2 * vSpace  , lpPoint);
				LineTo(hdcConsole, right - 2 * hSpace , bottom - 2 * vSpace );

				MoveToEx(hdcConsole, right - 2 * hSpace  , bottom - 2 * vSpace  , lpPoint);
				LineTo(hdcConsole, left + 2 * hSpace  , bottom - 2 * vSpace  );

				MoveToEx(hdcConsole, left + 2 * hSpace , bottom - 2 * vSpace  , lpPoint);
				LineTo(hdcConsole, left + 2 * hSpace  , top + 2 * vSpace  );
			}
			else
			{
				k = 0;
				for (int i = 0; i < 3; ++i)
				{
					MoveToEx(hdcConsole, left + i * hSpace + hSpace * k, top + i * vSpace + vSpace * k, lpPoint);
					LineTo(hdcConsole, right - i * hSpace - hSpace * k, top + i * vSpace + vSpace * k);

					MoveToEx(hdcConsole, right - i * hSpace - hSpace * k, top + i * vSpace + vSpace * k, lpPoint);
					LineTo(hdcConsole, right - i * hSpace - hSpace * k, bottom - i * vSpace - vSpace * k);

					MoveToEx(hdcConsole, right - i * hSpace - hSpace * k, bottom - i * vSpace - vSpace * k, lpPoint);
					LineTo(hdcConsole, left + i * hSpace + hSpace * k, bottom - i * vSpace - vSpace * k);

					MoveToEx(hdcConsole, left + i * hSpace + hSpace * k, bottom - i * vSpace - vSpace * k, lpPoint);
					LineTo(hdcConsole, left + i * hSpace + hSpace * k, top + i * vSpace + vSpace * k);
				}
			}

			

		
	}

	system("cls");

	ReleaseDC(console,hdcConsole);
}

void Game::function_02()
{

	int xStart = 100, yStart = 0, width=300,height=480,lineheight = 50, lineVSpace = 40, yLineMovement = 25;
	float kX = 0.8f, kY = 0,kMove=0;
	LPPOINT lpPoint = nullptr;

	HWND hwndConsole = GetConsoleWindow();
	HDC hdcConsole = GetDC(hwndConsole);

	//dark green
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 100, 0));
	SelectObject(hdcConsole, pen);

	for (int i = 0; i < 7; ++i)
	{

		Sleep(500);
			if (i % 2 == 0)
			{
				kMove = 1;
			}
			else
			{
				kMove = 0;
			}

			system("cls");

			MoveToEx(hdcConsole, xStart, yStart, lpPoint);
			LineTo(hdcConsole, xStart - kX * xStart, yStart + height);

			MoveToEx(hdcConsole, xStart + width, yStart, lpPoint);
			LineTo(hdcConsole, xStart + width + kX * xStart, yStart + height);

			for (int j = 0; j < 6; ++j)
			{
				MoveToEx(hdcConsole, xStart + 0.5*width, yStart + j * (lineheight + lineVSpace) + kMove*yLineMovement, lpPoint);
				LineTo(hdcConsole, xStart + 0.5*width, yStart + j * (lineheight + lineVSpace) + lineheight + kMove * yLineMovement);
			}
		


	}







	ReleaseDC(hwndConsole,hdcConsole);
}


void Game::function_03()
{
	HWND hwndConsole = GetConsoleWindow();
	HDC hdcConsole = GetDC(hwndConsole);

	int left = 100, right = 600, top = 50, bottom = 350, line1Top = 100,line1SectorLength=100, line2Top = 300, line2SectorLength = 150, rEllipse =5;

	LPPOINT lpPoint = nullptr;

	//dark green
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 100, 0));
	HPEN pen2 = CreatePen(PS_SOLID, 5, RGB(100, 0, 0));
	HPEN pen3 = CreatePen(PS_SOLID, 5, RGB(0, 0, 100));


		system("cls");

		SelectObject(hdcConsole, pen);

		MoveToEx(hdcConsole, left, top, lpPoint);
		LineTo(hdcConsole, right, top);

		MoveToEx(hdcConsole, right, top, lpPoint);
		LineTo(hdcConsole, right, bottom);

		MoveToEx(hdcConsole, right, bottom, lpPoint);
		LineTo(hdcConsole, left, bottom);

		MoveToEx(hdcConsole, left, bottom, lpPoint);
		LineTo(hdcConsole, left, top);

		MoveToEx(hdcConsole, left, line1Top, lpPoint);
		LineTo(hdcConsole, left + line1SectorLength, line1Top);

		MoveToEx(hdcConsole, left + line1SectorLength, line1Top, lpPoint);
		LineTo(hdcConsole, left + 2 * line1SectorLength, line1Top + 0.5*line1Top);

		MoveToEx(hdcConsole, left + 2 * line1SectorLength, line1Top + 0.5*line1Top, lpPoint);
		LineTo(hdcConsole, left + 3 * line1SectorLength, line1Top + 0.5*line1Top);


		MoveToEx(hdcConsole, left, line2Top, lpPoint);
		LineTo(hdcConsole, left + line2SectorLength, line2Top);

		MoveToEx(hdcConsole, left + line2SectorLength, line2Top, lpPoint);
		LineTo(hdcConsole, left + 2 * line2SectorLength, line2Top - 0.2*line2Top);

		MoveToEx(hdcConsole, left + 2 * line2SectorLength, line2Top - 0.2*line2Top, lpPoint);
		LineTo(hdcConsole, left + 3 * line2SectorLength, line2Top - 0.2*line2Top);



				SelectObject(hdcConsole, pen2);
				Ellipse(hdcConsole, left + 3 * line1SectorLength - rEllipse, line1Top + 0.5*line1Top - rEllipse, left + 3 * line1SectorLength + rEllipse, line1Top + 0.5*line1Top + rEllipse);


				SelectObject(hdcConsole, pen3);
				Ellipse(hdcConsole, left + 3 * line2SectorLength - rEllipse, line2Top - 0.2*line2Top - rEllipse, left + 3 * line2SectorLength + rEllipse, line2Top - 0.2*line2Top + rEllipse);

	







	//COLORREF COLOR = RGB(100, 0, 0);
	//SetPixel(hdcConsole, left + 3 * line1SectorLength, line1Top + 0.5*line1Top, COLOR);

	//COLOR = RGB(0, 0, 100);
	//SetPixel(hdcConsole, left + 3 * line2SectorLength, line2Top - 0.2*line2Top, COLOR);

	ReleaseDC(hwndConsole, hdcConsole);
}


void Game::function_04()
{
	HWND hwndConsole = GetConsoleWindow();
	HDC hdcConsole = GetDC(hwndConsole);

	int xStart = 0, yStart = 0, xStep = 70, yStep = 50, radius = 5;

	LPPOINT lppoint = nullptr;

	HPEN pen = CreatePen(PS_SOLID,5,RGB(0,100,0));

	system("cls");

	SelectObject(hdcConsole, pen);

	int xCenter = 0, yCenter = 0;
	int rndValue = 0,rndSigh = 0;



	for (int k = 0; k < 1000000000000; ++k)
	{

		if (k % 100000000 == 0)
		{

			system("cls");
			rndValue = rand() % 15;
			rndSigh = rand() % 3 + 1;

			for (int j = 0; j < 25; ++j)
			{
				yCenter = yStart + j * yStep;
				for (int i = 0; i < 10; ++i)
				{
					xCenter = xStart + i * xStep;
					if (rndSigh == 1)
					{
						xCenter += rndValue;
					}
					else
					{
						if (rndSigh == 2)
						{
							xCenter -= rndValue;
						}
						else
						{
							/*nothing to do*/
						}
					}
					Ellipse(hdcConsole, xCenter - radius, yCenter - radius, xCenter + radius, yCenter + radius);
				}
			}
		}
	}


	ReleaseDC(hwndConsole, hdcConsole);
}




void Game::function_05()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	HPEN hpen = CreatePen(PS_SOLID, 5, RGB(0, 100, 0));
	SelectObject(hdc,hpen);

	LPPOINT lppoint = nullptr;

	const int snowArraySize = 100;

	SnowBall  snowArray[snowArraySize];
	int left = 0, right = 0, top = 0, bottom = 0;



	system("cls");
	for (int j = 0; j < 100000000000; ++j)
	{
		if (j % 10000000 == 0)
		{
			for (int i = 0; i < snowArraySize; ++i)
			{
				(snowArray + i)->move();
				left = (snowArray + i)->getX() - (snowArray + i)->getSize() / 2;
				right = (snowArray + i)->getX() + (snowArray + i)->getSize() / 2;
				top = (snowArray + i)->getY() - (snowArray + i)->getSize() / 2;
				bottom = (snowArray + i)->getY() + (snowArray + i)->getSize() / 2;
				Ellipse(hdc, left, top, right, bottom);
			}
		}
	}








	ReleaseDC(hwnd, hdc);
}


void Game::function_06()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	HPEN hpen = CreatePen(PS_SOLID, 5, RGB(0, 100, 0));
	SelectObject(hdc, hpen);

	LPPOINT lppoint = nullptr;

	const int snowArraySize = 30;

	SnowBall  snowArray[snowArraySize];

	for (int i = 0; i < snowArraySize; ++i)
	{
		*(snowArray + i) = SnowBall(30,30,5,5,640,480);
	}


	int left = 0, right = 0, top = 0, bottom = 0;

	int xstart = 320, ystart = 10, length = 200;

	system("cls");
	for (int j = 0; j < 10; ++j)
	{

		Sleep(500);
			system("cls");
			for (int i = 0; i < snowArraySize; ++i)
			{
				(snowArray + i)->move();
				left = (snowArray + i)->getX() - (snowArray + i)->getSize() / 2;
				right = (snowArray + i)->getX() + (snowArray + i)->getSize() / 2;
				top = (snowArray + i)->getY() - (snowArray + i)->getSize() / 2;
				bottom = (snowArray + i)->getY() + (snowArray + i)->getSize() / 2;
				Ellipse(hdc, left, top, right, bottom);
			}

			for (int i = 0; i < 17; ++i)
			{
				MoveToEx(hdc, 0, 50 * (i + 1), lppoint);
				LineTo(hdc, 700, 50 * (i + 1));

				MoveToEx(hdc, 50 * (i + 1), 0, lppoint);
				LineTo(hdc, 50 * (i + 1), 500);
			}

			if (j >= 3)
			{
				MoveToEx(hdc, xstart, ystart, lppoint);
				LineTo(hdc, xstart - length, length);

				MoveToEx(hdc, xstart - length, length, lppoint);
				LineTo(hdc, xstart, length * 2);

				MoveToEx(hdc, xstart, length * 2, lppoint);
				LineTo(hdc, xstart + length, length);

				MoveToEx(hdc, xstart + length, length, lppoint);
				LineTo(hdc, xstart, ystart);
			}

			if (j == 5)
			{
			   length = 250;
			}

			if (j == 7)
			{
				length = 200;
			}


		
	}

	//system("cls");
	//HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN   );
	//std::cout << "кибер::ПАУТИНА" << std::endl;
	//std::cout << "кибер::ПАУТИНА" << std::endl;
	//std::cout << "ПАУТИНА" << std::endl;


	ReleaseDC(hwnd, hdc);
}


void Game::function_07()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	HPEN hpen = CreatePen(PS_SOLID, 5, RGB(0, 100, 0));
	SelectObject(hdc, hpen);

	LPPOINT lppoint = nullptr;



	int xstart = 320, ystart = 10,length = 200, move =0, moveStep =20;


	system("cls");
	for (int j = 0; j < 60; ++j)
	{

		Sleep(100);
		system("cls");

		MoveToEx(hdc, xstart, ystart,lppoint);
		LineTo(hdc, xstart-length+ move, length);

		MoveToEx(hdc, xstart - length + move, length, lppoint);
		LineTo(hdc, xstart, length*2);

		MoveToEx(hdc, xstart, length * 2, lppoint);
		LineTo(hdc, xstart+length - move, length);

		MoveToEx(hdc, xstart + length -move, length,lppoint);
		LineTo(hdc, xstart, ystart);

		MoveToEx(hdc, xstart, length*0.75f, lppoint);
		LineTo(hdc, xstart - length + move, length);

		MoveToEx(hdc, xstart, length*0.75f, lppoint);
		LineTo(hdc, xstart + length - move, length);

		MoveToEx(hdc, xstart, length*1.25f, lppoint);
		LineTo(hdc, xstart - length + move, length);

		MoveToEx(hdc, xstart, length*1.25f, lppoint);
		LineTo(hdc, xstart + length - move, length);


		MoveToEx(hdc, xstart, ystart, lppoint);
		LineTo(hdc, xstart, length);

		MoveToEx(hdc, xstart, length * 2, lppoint);
		LineTo(hdc, xstart, length);

		move += moveStep;
		if (move >= moveStep * 20)
		{
			move = 0;
		}

	}








	ReleaseDC(hwnd, hdc);
}



void initRussianWordList(Game * _game)
{
	ActionWord actionWord( const_cast <char *>("Осмотреть"), EActions::LOOK);
	_game->actionWordList.addElement(actionWord);
	actionWord.setData(const_cast <char *>("Говорить"), EActions::SPEAK);
	_game->actionWordList.addElement(actionWord);

	char ** charValues = nullptr;
	set2DimensionCharArray(&charValues,  const_cast <char *> ("|Врач|Врача|Врачу|Врача|Врачом|Враче"));
	ObjectWord objectWord = ObjectWord(charValues,6,EObjects::DOCTOR);
	_game->objectWordList.addElement(objectWord);
	clearAndSet2DimensionCharArray(&charValues, 6, const_cast <char *> ("|Комната|Комнату|Комнате|Комнату|Комнатой|Комнате"));
	objectWord.setData(charValues, 6, EObjects::ROOM);
	_game->objectWordList.addElement(objectWord);
	clear2DimensionCharArray(&charValues,6);

	CommandWord commandWord(const_cast <char *>("Звук Вкл"), ECommands::SOUND_ON);
	_game->actionWordList.addElement(actionWord);
	commandWord.setData(const_cast <char *>("Звук Выкл"), ECommands::SOUND_OFF);
	_game->actionWordList.addElement(actionWord);
	commandWord.setData(const_cast <char *>("Выход"), ECommands::GAME_EXIT);
	_game->actionWordList.addElement(actionWord);
	commandWord.setData(const_cast <char *>("Сохр"), ECommands::GAME_SAVE);
	_game->actionWordList.addElement(actionWord);
	commandWord.setData(const_cast <char *>("Загр"), ECommands::GAME_LOAD);
	_game->actionWordList.addElement(actionWord);

}

void initEnglishWordList(Game * _game)
{

}


