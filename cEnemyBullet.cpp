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
		//1초에 4
		//0.1초에 0.4감소
		//0.5초에 2감소
		if (m_accel > 1.f) m_accel -= D_TIME * 4;
		else m_accel = 1.f;
	}

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
		) m_isLive = FALSE;
	else return;
}

void cEnemyBullet::Collision()
{
	auto player = ((cPlayer*)OBJFIND(PLAYER));
	if (player->m_isHit == TRUE || player->m_isNotDead == TRUE) return;

	VEC2 pPos = player->GetPos();
	FLOAT bRad = m_img->m_info.Width / 2 * m_size.x;

	//총알의 반지름은 이미지의 가로 길이의 절반으로
	if (CIRCLE(m_pos, pPos, bRad, 1)) {
		if (player->m_life > 1) {
			SOUND->Copy("deadSND");
			EFFECT->AddEffect(
				new cEffect("enemy_dead_EFFECT", 1, player->GetPos(), VEC2(0, 0),
					VEC2(2.5, 2.5), VEC2(5, 5)
				)
			);
		}
		else {
			player->GetRefLive() = FALSE;
		}
		player->m_life--;
		player->m_nowBulletCnt = player->m_isShot = 0;
		player->m_isHit = TRUE;
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
