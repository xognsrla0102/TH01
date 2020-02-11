#include "DXUT.h"
#include "cBullet.h"
#include "cBulletAdmin.h"

cBulletAdmin::~cBulletAdmin()
{
	Release();
}

void cBulletAdmin::Update()
{
	size_t size = m_playerBullet.size();

	for (size_t i = 0; i < size; i++) {
		if (m_playerBullet[i]->GetLive() == false) {
			SAFE_DELETE(m_playerBullet[i]);
			m_playerBullet.erase(m_playerBullet.begin() + i);
			i--, size--;
		}
	}

	size = m_ballBullet.size();
	for (size_t i = 0; i < size; i++) {
		if (m_ballBullet[i]->GetLive() == false) {
			SAFE_DELETE(m_ballBullet[i]);
			m_ballBullet.erase(m_ballBullet.begin() + i);
			i--, size--;
		}
	}
}

void cBulletAdmin::Render()
{
}

void cBulletAdmin::Release()
{
	for (auto iter : m_playerBullet)
		SAFE_DELETE(iter);
	m_playerBullet.clear();

	for (auto iter : m_ballBullet)
		SAFE_DELETE(iter);
	m_ballBullet.clear();
}
