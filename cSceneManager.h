#pragma once
#include "cSingleton.hpp"

class cScene;
class cSceneManager : public cSingleton<cSceneManager>
{
private:
	friend class cSingleton<cSceneManager>;
private:
	map<string, cScene*> m_scenes;
	cScene* m_nowScene;
	cScene* m_nextScene;
public:
	cSceneManager();
	virtual ~cSceneManager();

	void AddScene(string name, cScene* scene);
	void ChangeScene(string name);
	void Update();
	void Render();
};

#define SCENE cSceneManager::GetInst()