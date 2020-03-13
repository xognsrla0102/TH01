#include "DXUT.h"
#include "cPlayer.h"
#include "cBullet.h"
#include "cEnemyBullet.h"
#include "cBulletAdmin.h"

cBulletAdmin::~cBulletAdmin()
{
	Release();
}

void cBulletAdmin::Update()
{
	size_t size = m_playerBullet.size();
	for (size_t i = 0; i < size; i++) {
		m_playerBullet[i]->Update();
		m_playerBullet[i]->OutMapChk();
		m_playerBullet[i]->Collision();

		if (m_playerBullet[i]->GetLive() == false) {
			SAFE_DELETE(m_playerBullet[i]);
			m_playerBullet.erase(m_playerBullet.begin() + i);
			i--, size--;
		}
	}

	size = m_ballBullet.size();
	for (size_t i = 0; i < size; i++) {
		m_ballBullet[i]->Update();
		m_ballBullet[i]->OutMapChk();
		m_ballBullet[i]->Collision();

		if (m_ballBullet[i]->GetLive() == false) {
			SAFE_DELETE(m_ballBullet[i]);
			m_ballBullet.erase(m_ballBullet.begin() + i);
			i--, size--;
		}
	}

	size = m_enemyBullet.size();
	for (size_t i = 0; i < size; i++) {
		m_enemyBullet[i]->Update();
		m_enemyBullet[i]->OutMapChk();
		m_enemyBullet[i]->Collision();

		if (m_enemyBullet[i]->GetLive() == false) {
			SAFE_DELETE(m_enemyBullet[i]);
			m_enemyBullet.erase(m_enemyBullet.begin() + i);
			i--, size--;
		}
	}
}

void cBulletAdmin::Render()
{
	for (auto iter : m_playerBullet)
		iter->Render();
	for (auto iter : m_ballBullet)
		iter->Render();
	for (auto iter : m_enemyBullet)
		iter->Render();
}

void cBulletAdmin::Release()
{
	for (auto iter : m_playerBullet)
		SAFE_DELETE(iter);
	m_playerBullet.clear();

	for (auto iter : m_ballBullet)
		SAFE_DELETE(iter);
	m_ballBullet.clear();

	for (auto iter : m_enemyBullet)
		SAFE_DELETE(iter);
	m_enemyBullet.clear();
}
