#pragma once
#include "cSingleton.hpp"

class cSoundManager : public cSingleton<cSoundManager>
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	MCI_STATUS_PARMS mciStatus;

	UINT wDeviceID = 0;
public:
	DWORD LoadMP3(HWND hWnd, LPCTSTR name);
};