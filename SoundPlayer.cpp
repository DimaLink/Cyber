#pragma comment(lib,"Winmm.lib")
#include <iostream>
#include <Windows.h>
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	sound = nullptr;
	setIsSoundOn(true);
}

SoundPlayer::~SoundPlayer()
{
	clearSound();
}


void SoundPlayer::playSound()
{
	PlaySoundA(sound,NULL, SND_FILENAME| SND_LOOP | SND_ASYNC);
}

void SoundPlayer::stopSound()
{
	PlaySoundA(NULL, 0, 0);
}

bool SoundPlayer::checkIsSoundNew( char * _newSound)
{
	if (_newSound != nullptr)
	{
		if (sound == nullptr)
		{
			return true;
		}

		int _newSoundLength = strlen(_newSound);
		int soundLength = strlen(sound);
		if (_newSoundLength == soundLength)
		{
			int identicalIndex = 0;
			for (int i = 0; i < soundLength; ++i)
			{
				if (*(_newSound + i) == *(sound + i))
				{
					identicalIndex++;
				}
				else
				{
					identicalIndex = 0;
					break;
				}
			}

			if (identicalIndex == soundLength)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void SoundPlayer::setSound(char * _sound)
{
	if (checkIsSoundNew(_sound) == true)
	{
		clearSound();

		if (_sound != nullptr)
		{
			int _soundLength = strlen(_sound);
			if (_soundLength > 0)
			{
				sound = new char[_soundLength + 1];
				strcpy_s(sound, _soundLength + 1, _sound);
				if (getIsSoundOn() == true)
				{
					playSound();
				}
			}
		}
	}	
}

char * SoundPlayer::getSound()
{
	return sound;
}

void SoundPlayer::clearSound()
{
	if (sound != nullptr)
	{
		delete[] sound;
		sound = nullptr;
	}
}

void SoundPlayer::setIsSoundOn(bool _isSoundOn)
{
	isSoundOn = _isSoundOn;
}

bool SoundPlayer::getIsSoundOn()
{
	return isSoundOn;
}

