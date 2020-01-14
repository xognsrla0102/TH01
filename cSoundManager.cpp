#include "DXUT.h"
#include "cSoundManager.h"

DWORD cSoundManager::LoadMP3(HWND hWnd, LPCTSTR name)
{
	DWORD result;

	//mp3형식 재생
	mciOpen.lpstrDeviceType = L"MPEGVideo";
	mciOpen.lpstrElementName = name;

	result = mciSendCommand(
		wDeviceID,
		MCI_OPEN,
		MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
		(DWORD)(LPVOID)&mciOpen
	);

	if (result) return result;

	wDeviceID = mciOpen.wDeviceID;

	mciPlay.dwCallback = (DWORD)hWnd;

	return 0;
}

void cSoundManager::PlayMP3()
{
	mciSendCommand(wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
		(DWORD)(LPVOID)&mciPlay);
}

void cSoundManager::PlaySoundEffect()
{
	//PlaySoundW(, NULL, SND_ASYNC);
}
