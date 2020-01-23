#pragma once
#include "cSingleton.hpp"

class cSoundManager : public cSingleton<cSoundManager>
{
private:
	CSoundManager* m_sound = nullptr;
	map<string, CSound*> m_sounds;

	int m_volume = 0;
public:
	cSoundManager();
	virtual ~cSoundManager();

	void AddSound(const string& key, const wstring& path);
	void Play(const string& key, bool isBGM = false, bool loop = false);
	void Stop(const string& key);
	void Copy(const string& key);
	void Reset();
};

#define SOUND cSoundManager::GetInst()