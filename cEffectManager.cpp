#include "DXUT.h"
#include "cEffectManager.h"

cEffectManager::cEffectManager()
{
}

cEffectManager::~cEffectManager()
{
	Reset();
}

void cEffectManager::AddEffect(cEffect* eftPtr)
{
	if (eftPtr != nullptr) m_efts.push_back(eftPtr);
	else DEBUG_LOG("���� ����Ʈ�� ����־���...\n");
}

void cEffectManager::Update()
{
	for (auto iter : m_efts)
		iter->Update();

	size_t size = m_efts.size();

	for (size_t i = 0; i < size; i++) {
		if (m_efts[i]->m_isDone == true) {
			SAFE_DELETE(m_efts[i]);
			m_efts.erase(m_efts.begin() + i);
			size--, i--;
		}
	}
}

void cEffectManager::Render()
{
	for (auto iter : m_efts)
		iter->Render();
}

void cEffectManager::Reset()
{
	for (auto iter : m_efts)
		SAFE_DELETE(iter);
	m_efts.clear();
}
