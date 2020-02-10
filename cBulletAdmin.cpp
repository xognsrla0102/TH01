#include "DXUT.h"
#include "cBullet.h"
#include "cBulletAdmin.h"

cBulletAdmin::~cBulletAdmin()
{
	for (auto iter : m_playerBullet)
		SAFE_DELETE(iter);
	m_playerBullet.clear();
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

	DEBUG_LOG("%d\n", size);
}

void cBulletAdmin::Render()
{
}
