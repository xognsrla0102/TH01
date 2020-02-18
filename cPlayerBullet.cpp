#include "DXUT.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"
#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(string key, VEC2 pos, VEC2 dir, VEC2 size, FLOAT rot)
{
	m_img = IMAGE->FindImage(key);
	m_img->m_color = D3DCOLOR_ARGB(150, 255, 255, 255);

	m_pos = pos;
	m_dir = dir;
	m_size = size;
	m_rot = rot;
	m_speed = 1500.f;
}

cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	m_pos += m_dir * m_speed * D_TIME;
	if(isMarisa == false) m_rot -= 8;
	if (m_rot > 360) m_rot -= 360;
}

void cPlayerBullet::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cPlayerBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > WINSIZEX ||
		m_pos.x + m_img->m_info.Width / 2 < -300 ||
		m_pos.y - m_img->m_info.Height / 2 > WINSIZEY + 300 ||
		m_pos.y + m_img->m_info.Height / 2 < -300
		) m_isLive = false;
	else return;
}

void cPlayerBullet::Collision()
{
	RECT pBulletRect = {
		m_pos.x - m_img->m_info.Width / 2,
		m_pos.y - m_img->m_info.Height / 2,
		m_pos.x + m_img->m_info.Width / 2,
		m_pos.y + m_img->m_info.Height / 2,
	};

	auto& eOne = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();

	size_t size = eOne.size();
	for (size_t i = 0; i < size; i++) {
		VEC2 onePos = eOne[i]->GetPos();
		cTexture* oneImg = eOne[i]->GetImg();

		RECT oneRect = {
			onePos.x - oneImg->m_info.Width / 2,
			onePos.y - oneImg->m_info.Height / 2,
			onePos.x + oneImg->m_info.Width / 2,
			onePos.y + oneImg->m_info.Height / 2,
		};

		if (AABB(pBulletRect, oneRect) == true) {
			m_isLive = false;
			eOne[i]->GetRefLive() = false;
			return;
		}
	}
}
