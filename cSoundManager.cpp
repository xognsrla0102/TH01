#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager(HWND hWnd, LPCTSTR path)
{
	//mp3형식 재생
	mciOpen.lpstrDeviceType = L"mpegvideo";
	//wav파일일 경우 waveaudio로 설정
	mciOpen.lpstrElementName = path;
	//파일 경로

	mciSendCommand(
		wDeviceID,
		MCI_OPEN,
		MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
		(DWORD)(LPVOID)&mciOpen
	);

	//MCI_OPEN_TYPE : 마지막 인수인
	//구조체에 지정된 MCI 장치를 사용

	//MCI_OPEN_ELEMENT : 마지막 인수인
	//구조체에 지정된 파일을 사용

	wDeviceID = mciOpen.wDeviceID;
	//노래를 넣은 이 장치의 아이디 옮겨줌
	//이 아이디를 통해 이 노래를 조작

	mciPlay.dwCallback = (DWORD)hWnd;
	//나중에 실행할 때 필요한 정보
}

cSoundManager::~cSoundManager()
{
	MCI_GENERIC_PARMS mciGen;

	mciSendCommand(
		wDeviceID,
		MCI_CLOSE,
		MCI_WAIT,
		(DWORD)(LPVOID)&mciGen
	);
}

void cSoundManager::Play()
{
	mciSendCommand(
		wDeviceID,
		MCI_PLAY,
		MCI_DGV_PLAY_REPEAT,
		(DWORD)(LPVOID)&mciPlay
	);
	//3번째 인자에 MCI_NOTIFY 를 입력하면
	//곡이 종료될 때 윈도우에
	//MM_MCINOTIFY 라는 메세지 보냄
}

void cSoundManager::Pause()
{
	MCI_GENERIC_PARMS mciGen;

	mciSendCommand(
		wDeviceID,
		MCI_PAUSE,
		MCI_WAIT,
		(DWORD)(LPVOID)&mciGen
	);
}

void cSoundManager::Resume()
{
	MCI_GENERIC_PARMS mciGen;

	mciSendCommand(
		wDeviceID,
		MCI_RESUME,
		MCI_WAIT,
		(DWORD)(LPVOID)&mciGen
	);
}

void cSoundManager::Stop()
{
	MCI_GENERIC_PARMS mciGen;

	mciSendCommand(
		wDeviceID,
		MCI_STOP,
		MCI_WAIT,
		(DWORD)(LPVOID)&mciGen
	);
}

void cSoundManager::PlayEffect(const string& path)
{
	sndPlaySound((LPCWSTR)path.c_str(), SND_ASYNC);
}
