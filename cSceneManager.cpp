#include "DXUT.h"
#include "cScene.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
	: m_nowScene(nullptr), m_nextScene(nullptr)
{
}

cSceneManager::~cSceneManager()
{
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();

	m_nowScene = m_nextScene = nullptr;
}

void cSceneManager::AddScene(string name, cScene* scene)
{
	auto find = m_scenes.find(name);
	if (find != m_scenes.end()) {
		DEBUG_LOG("�̹� ���� ���̿���...\n");
		return;
	}
	m_scenes.insert(map<string, cScene*>::value_type(name, scene));
}

void cSceneManager::ChangeScene(string name)
{
	auto find = m_scenes.find(name);
	if (find == m_scenes.end()) {
		DEBUG_LOG("ã�� �̸��� ���� ������...\n");
		return;
	}
	m_nextScene = find->second;
}

void cSceneManager::Update()
{
	if (m_nextScene) {
		m_nowScene = m_nextScene;
		m_nextScene = nullptr;
	}

	if(!m_nowScene) DEBUG_LOG("���� ����Ű�� ���� ���µ� �����Ϸ��� ����..\n");
	m_nowScene->Update();
}

void cSceneManager::Render()
{
	if (!m_nowScene) DEBUG_LOG("���� ����Ű�� ���� ���µ� �׸����� ����..\n");
	m_nowScene->Render();
}
