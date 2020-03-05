#include "DXUT.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"
#include "cBallBullet.h"

cBallBullet::cBallBullet(string key, VEC2 pos, VEC2 dir, VEC2 size, FLOAT rot, bool isHoming)
{
	m_img = IMAGE->FindImage(key);
	m_img->m_color = D3DCOLOR_ARGB(150, 255, 255, 255);

	m_isHoming = isHoming;

	m_pos = pos;
	m_dir = dir;
	m_size = size;
	m_rot = rot;
	m_speed = 1500.f;
}

cBallBullet::~cBallBullet()
{
}

void cBallBullet::Update()
{
	m_pos += m_dir * m_speed * D_TIME;
}

void cBallBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > WINSIZEX ||
		m_pos.x + m_img->m_info.Width / 2 < -300 ||
		m_pos.y - m_img->m_info.Height / 2 > WINSIZEY + 300 ||
		m_pos.y + m_img->m_info.Height / 2 < -300
		) m_isLive = false;
	else return;
}

void cBallBullet::Collision()
{
	RECT bBulletRect = {
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

		if (OBB(m_pos, onePos, bBulletRect, oneRect, m_rot, eOne[i]->GetRot()) == true) {
			m_isLive = false;
			eOne[i]->GetRefLive() = false;
			return;
		}
	}
}

