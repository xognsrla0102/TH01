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
	for (size_t i = 0; i < size; i++) {
		m_ones[i]->Update();
		m_ones[i]->OutMapChk();

		if (m_ones[i]->GetLive() == false) {
			VEC2 onePos = m_ones[i]->GetPos();
			//맵안에서 죽었을 경우만 이펙트와 사운드 나게
			if (!(50 > onePos.x + 25 || onePos.x - 25 > 50 + INGAMEX ||
				50 > onePos.y + 25 || onePos.y - 25 > 50 + INGAMEY )) {
				SOUND->Copy("enemydeadSND");
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, onePos,
						VEC2(0.5f, 0.5f), VEC2(1, 1)
					)
				);
			}
			SAFE_DELETE(m_ones[i]);
			m_ones.erase(m_ones.begin() + i);
			i--, size--;
		}
	}

	size = m_fairys.size();
	for (size_t i = 0; i < size; i++) {
		m_fairys[i]->Update();
		m_fairys[i]->OutMapChk();

		if (m_fairys[i]->GetLive() == FALSE) {
			VEC2 fairyPos = m_fairys[i]->GetPos();
			if (!(50 > fairyPos.x + 23 || fairyPos.x - 23 > 50 + INGAMEX ||
				50 > fairyPos.y + 23 || fairyPos.y - 23 > 50 + INGAMEY)) {
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, fairyPos,
						VEC2(0.5f, 0.5f), VEC2(1, 1))
				);
				SOUND->Copy("enemydeadSND");
			}
			SAFE_DELETE(m_fairys[i]);
			m_fairys.erase(m_fairys.begin() + i);
			i--, size--;
		}
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_ones)
		iter->Render();
	for (auto iter : m_fairys)
		iter->Render();
}

void cEnemyAdmin::Release()
{
	for (auto iter : m_ones)
		SAFE_DELETE(iter);
	m_ones.clear();

	for (auto iter : m_fairys)
		SAFE_DELETE(iter);
	m_fairys.clear();
}

