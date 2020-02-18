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
		if (m_ones[i]->GetLive() == false) {
			VEC2 onePos = m_ones[i]->GetPos();

			//¸Ê¹Û ÀÏ °æ¿ì
			if (!(50 - 25 > onePos.x || onePos.x > 50 + INGAMEX + 25 ||
				50 - 25 > onePos.y || onePos.y > 50 + INGAMEY + 25)) {
				EFFECT->AddEffect(new cEffect("enemy_dead_EFFECT", 1, onePos, VEC2(-0.5f, -0.5f)));
				SOUND->Copy("enemydeadSND");
			}

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

