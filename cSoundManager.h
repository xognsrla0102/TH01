#pragma once
#include "cSingleton.hpp"

class cSoundManager : public cSingleton<cSoundManager>
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;

	UINT wDeviceID = 0;
public:
	cSoundManager(HWND hWnd, LPCTSTR name);
	virtual ~cSoundManager();

	void Play();
	void Pause();
	void Resume();
	void Stop();

	void PlayEffect(const string& path);
};

#define SOUND cSoundManager::GetInst()
#define LOAD(i, j) SOUND->LoadMP3(i, j)
#define PLAY(i) SOUND->PlayMP3(i)
#define PLAYEFT(i) SOUND->PlayEffect(i)