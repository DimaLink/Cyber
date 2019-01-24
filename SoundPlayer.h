#pragma once
#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

class SoundPlayer
{
public:
	SoundPlayer();
	~SoundPlayer();

	void playSound();
	void stopSound();
	void setSound(char *);
	char * getSound();
	void clearSound();
	bool checkIsSoundNew( char *);

	void setIsSoundOn(bool);
	bool getIsSoundOn();

private:
	char * sound;
	bool isSoundOn;
};

#endif