#include "DXUT.h"
#include "cScene.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
	: m_nowScene(nullptr), m_nextScene(nullptr)
{
}

cSceneManager::~cSceneManager()
{
	if(m_nowScene) m_nowScene->Release();
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();

	m_nowScene = m_nextScene = nullptr;
}

void cSceneManager::AddScene(string name, cScene* scene)
{
	auto find = m_scenes.find(name);
	if (find != m_scenes.end()) {
		DEBUG_LOG("이미 만든 씬이에유...\n");
		return;
	}
	m_scenes.insert(map<string, cScene*>::value_type(name, scene));
}

void cSceneManager::ChangeScene(string name)
{
	auto find = m_scenes.find(name);
	if (find == m_scenes.end()) {
		DEBUG_LOG("찾는 이름의 씬이 읎네유...\n");
		return;
	}
	m_nextScene = find->second;
}

void cSceneManager::Update()
{
	if (m_nextScene) {
		m_nowScene = m_nextScene;
		m_nextScene = nullptr;
		m_nowScene->Init();
	}

	if (!m_nowScene) {
		DEBUG_LOG("현재 가리키는 씬이 읎는데 갱신하려고 해유..\n");
		return;
	}
	m_nowScene->Update();
}

void cSceneManager::Render()
{
	if (!m_nowScene) {
		DEBUG_LOG("현재 가리키는 씬이 읎는데 그리려구 해유..\n");
		return;
	}
	m_nowScene->Render();
}
