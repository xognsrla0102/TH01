#include "DXUT.h"
#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(string key, VEC2 pos, VEC2 size, FLOAT rot)
{
	m_img = IMAGE->FindImage(key);
	m_pos = pos;
	m_size = size;
	m_rot = rot;
	m_speed = 100.f;
}

cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	m_pos.y -= m_speed * D_TIME;
}

void cPlayerBullet::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}



void cPlayerBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > WINSIZEX ||
		m_pos.x + m_img->m_info.Width / 2 < -500 ||
		m_pos.y - m_img->m_info.Height / 2 < WINSIZEY + 500 ||
		m_pos.y + m_img->m_info.Height / 2 < -500
		) m_isLive = false;
	else return;
}

void cPlayerBullet::Collision()
{
}
