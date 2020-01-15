#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager(HWND hWnd, LPCTSTR path)
{
	//mp3���� ���
	mciOpen.lpstrDeviceType = L"mpegvideo";
	//wav������ ��� waveaudio�� ����
	mciOpen.lpstrElementName = path;
	//���� ���

	mciSendCommand(
		wDeviceID,
		MCI_OPEN,
		MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
		(DWORD)(LPVOID)&mciOpen
	);

	//MCI_OPEN_TYPE : ������ �μ���
	//����ü�� ������ MCI ��ġ�� ���

	//MCI_OPEN_ELEMENT : ������ �μ���
	//����ü�� ������ ������ ���

	wDeviceID = mciOpen.wDeviceID;
	//�뷡�� ���� �� ��ġ�� ���̵� �Ű���
	//�� ���̵� ���� �� �뷡�� ����

	mciPlay.dwCallback = (DWORD)hWnd;
	//���߿� ������ �� �ʿ��� ����
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
	//3��° ���ڿ� MCI_NOTIFY �� �Է��ϸ�
	//���� ����� �� �����쿡
	//MM_MCINOTIFY ��� �޼��� ����
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
