#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemyBullet.h"

cEnemyBullet::cEnemyBullet(string key, VEC2 pos, INT kind, FLOAT speed, VEC2 dir, BOOL isAccel, VEC2 size, FLOAT rot)
{
	m_img = IMAGE->FindImage(key);
	m_pos = pos;
	m_kind = kind;
	m_speed = speed;
	m_dir = dir;
	m_isAccel = isAccel;

	m_size = size;
	m_rot = rot;

	if (m_isAccel == TRUE) m_accel = 3.f;
	else m_accel = 1.f;
}

cEnemyBullet::~cEnemyBullet()
{
}

void cEnemyBullet::Update()
{
	if (m_isAccel == TRUE) {
		//1�ʿ� 4
		//0.1�ʿ� 0.4����
		//0.5�ʿ� 2����
		if (m_accel > 1.f) m_accel -= D_TIME * 4;
		else m_accel = 1.f;
	}

	//����
	switch (m_kind) {
	case 1:
		//1. ����
		Straight();
		break;
	case 2:
		//2. ����
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

	//�Ѿ��� �������� ���� ���� / 2�� �ӽô�å
	if (CIRCLE(m_pos, pPos, bRad, 1)) {
		m_isLive = false;
		if (player->m_life > 0) {
			player->m_life--;
			player->m_isHit = TRUE;
		}
		else player->GetRefLive() = FALSE;
		return;
	}
}

void cEnemyBullet::Straight()
{
	m_pos += m_dir * m_speed * D_TIME * m_accel;
}

void cEnemyBullet::Follow()
{
}
