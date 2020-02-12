#include "DXUT.h"
#include "cBallBullet.h"

cBallBullet::cBallBullet(string key, VEC2 pos, VEC2 dir, VEC2 size, FLOAT rot, bool isHoming)
{
	m_img = IMAGE->FindImage(key);
	m_img->m_color = D3DCOLOR_ARGB(130, 255, 255, 255);

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

void cBallBullet::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, m_img->m_color);
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
}

