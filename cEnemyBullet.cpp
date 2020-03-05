#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemyBullet.h"

cEnemyBullet::cEnemyBullet(string key, VEC2 pos, INT kind, FLOAT speed, VEC2 dir, VEC2 size, FLOAT rot)
{
	m_img = IMAGE->FindImage(key);
	m_pos = pos;
	m_dir = dir;
	m_size = size;
	m_rot = rot;
	m_speed = speed;

	m_kind = kind;
}

cEnemyBullet::~cEnemyBullet()
{
}

void cEnemyBullet::Update()
{
	//패턴
	switch (m_kind) {
	case 1:
		//1. 직진
		Straight();
		break;
	case 2:
		//2. 유도
		Follow();
		break;
	default:
		break;
	}
}

void cEnemyBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 * m_size.x > WINSIZEX ||
		m_pos.x + m_img->m_info.Width / 2 * m_size.x < -300 ||
		m_pos.y - m_img->m_info.Height / 2 * m_size.y > WINSIZEY + 300 ||
		m_pos.y + m_img->m_info.Height / 2 * m_size.y  < -300
		) m_isLive = false;
	else return;
}

void cEnemyBullet::Collision()
{
	auto player = ((cPlayer*)OBJFIND(PLAYER));
	VEC2 pPos = player->GetPos();
	FLOAT bRad = m_img->m_info.Width / 2 * m_size.x;

	//총알의 반지름은 가로 길이 / 2로 임시대책
	if (CIRCLE(m_pos, pPos, bRad, 2)) {
		m_isLive = false;
		if (player->m_life > 0) player->m_life--;
		else player->GetRefLive() = false;
		return;
	}
}

void cEnemyBullet::Straight()
{
	m_pos += m_dir * m_speed * D_TIME;
}

void cEnemyBullet::Follow()
{
}
