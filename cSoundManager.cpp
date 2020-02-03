#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	m_sound = new CSoundManager;
	m_sound->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
}

cSoundManager::~cSoundManager()
{
	Reset();
	SAFE_DELETE(m_sound);
}

void cSoundManager::AddSound(const string& key, const wstring& path)
{
	CSound* sound;
	m_sound->Create(&sound, (LPWSTR)path.c_str());
	m_sounds[key] = sound;
}

void cSoundManager::Play(const string& key, bool isBGM, bool loop)
{
	//ȿ���� Ʋ�����ϴµ� ȿ������ �������� ���
	if (isBGM == false && onSND == false) return;
	//��� Ʋ���� �ϴµ� ����� �������� ���
	if (isBGM == true && onBGM == false)
		return;
	if (isBGM == true) {
		char str[256];
		if (isMidi == true)
			sprintf(str, key.c_str(), "midi");
		else
			sprintf(str, key.c_str(), "wav");

		m_sounds[str]->GetBuffer(0)->SetCurrentPosition(0);
		m_sounds[str]->Play(0, loop);
		return;
	}
	//ȿ����
	m_sounds[key]->Play(0, loop, 1);
}

void cSoundManager::Stop(const string& key)
{
	//Stop�� ȿ������ �� ���̹Ƿ� ȿ���� ó�� �� ����
	char str[256];
	if (isMidi == true) sprintf(str, key.c_str(), "midi");
	else sprintf(str, key.c_str(), "wav");
	
	m_sounds[str]->Stop();
}

void cSoundManager::Copy(const string& key)
{
	LPDIRECTSOUNDBUFFER pBuf;
	m_sound->GetDirectSound()->DuplicateSoundBuffer(
		m_sounds[key]->GetBuffer(0),
		&pBuf
	);

	pBuf->SetCurrentPosition(0);

	//Copy �Լ��� ȿ������ �� ���� ���Ƿ�
	if(onSND == true)
		pBuf->Play(0, 0, 0);
}

void cSoundManager::Reset()
{
	for (auto iter : m_sounds)
		SAFE_DELETE(iter.second);
	m_sounds.clear();
}
