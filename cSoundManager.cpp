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

	if (result) return result;

	return 0;
}
