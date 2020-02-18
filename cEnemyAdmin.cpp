#include "DXUT.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"

cEnemyAdmin::cEnemyAdmin()
{
}

cEnemyAdmin::~cEnemyAdmin()
{
	Release();
}

void cEnemyAdmin::Update()
{
	size_t size = m_ones.size();
	DEBUG_LOG("%d\n", size);

	for (size_t i = 0; i < size; i++) {
		if (m_ones[i]->GetLive() == false) {
			SAFE_DELETE(m_ones[i]);
			m_ones.erase(m_ones.begin() + i);
			i--, size--;
		}
	}
}

void cEnemyAdmin::Render()
{
}

void cEnemyAdmin::Release()
{
	for (auto iter : m_ones)
		SAFE_DELETE(iter);
	m_ones.clear();
}

