#include "DXUT.h"
#include "cItem.h"
#include "cItemAdmin.h"
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

		if (m_ones[i]->GetLive() == FALSE) {
			VEC2 onePos = m_ones[i]->GetPos();
			//∏  æ»ø°º≠ ¡◊æ˙¿ª ∞ÊøÏ∏∏ ¿Ã∆Â∆ÆøÕ ªÁøÓµÂ ≥™∞‘
			if (!(50 > onePos.x + 25 || onePos.x - 25 > 50 + INGAMEX ||
				50 > onePos.y + 25 || onePos.y - 25 > 50 + INGAMEY )) {
				SOUND->Copy("enemydeadSND");
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, onePos, VEC2(0, 0),
						VEC2(0.5f, 0.5f), VEC2(1, 1)
					)
				);
				//¡◊¿∏∏È æ∆¿Ã≈€ ∂≥±¿
				for (size_t j = 0; j < m_ones[i]->GetItemNames().size(); j++) {
					string nowItemName = m_ones[i]->GetItemNames()[j];
					((cItemAdmin*)OBJFIND(ITEMS))->m_items.push_back(
						new cItem(nowItemName, onePos, VEC2(onePos.x, onePos.y - (40 + rand() % 30)))
					);
				}
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
				SOUND->Copy("enemydeadSND");
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, fairyPos, VEC2(0, 0),
						VEC2(0.5f, 0.5f), VEC2(1, 1))
				);
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

