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
	//효과음 틀려고하는데 효과음이 꺼져있을 경우
	if (isBGM == false && onSND == false) return;
	//브금 틀려고 하는데 브금이 꺼져있을 경우
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
	//효과음
	m_sounds[key]->Play(0, loop, 1);
}

void cSoundManager::Stop(const string& key)
{
	//Stop은 효과음엔 안 쓰이므로 효과음 처린 안 해줌
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

	//Copy 함수는 효과음일 때 많이 쓰므로
	if(onSND == true)
		pBuf->Play(0, 0, 0);
}

void cSoundManager::Reset()
{
	for (auto iter : m_sounds)
		SAFE_DELETE(iter.second);
	m_sounds.clear();
}
