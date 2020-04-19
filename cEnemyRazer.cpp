#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemyRazer.h"

cEnemyRazer::cEnemyRazer(string key, VEC2 pos, INT startDelay, INT atkDelay, VEC2 size, FLOAT rot)
{
	m_img = IMAGE->FindImage(key);
	m_pos = VEC2(pos.x, pos.y + m_img->m_info.Height / 2 + 30);

	m_startDelay = startDelay;
	m_atkDelay = atkDelay;

	m_size = size;
	m_rot = rot;
}

cEnemyRazer::~cEnemyRazer()
{
}

void cEnemyRazer::Update()
{
	if (m_isDone == TRUE) {
		Lerp(m_size.x, 0.f, 0.05);
		if (m_size.x < 0.1f) m_isLive = FALSE;
	}
	else if (m_atk != 0 && timeGetTime() - m_atk > m_atkDelay) {
		m_isDone = TRUE;
	}
	else if (m_atk == 0 && timeGetTime() - m_start > m_startDelay) {
		Lerp(m_size.x, 2.f, 0.05);
		if (m_size.x > 1.9f) m_atk = timeGetTime();
	}
}

void cEnemyRazer::OutMapChk()
{
}

void cEnemyRazer::Collision()
{
	auto player = ((cPlayer*)OBJFIND(PLAYER));
	if (player->m_isHit == TRUE || player->m_isNotDead == TRUE) return;

	VEC2 pPos = player->GetPos();

	RECT pRect = {
		player->GetPos().x - 5,
		player->GetPos().y - 5,
		player->GetPos().x + 5,
		player->GetPos().y + 5
	};

	RECT rect{
		m_pos.x - m_img->m_info.Width / 2 * m_size.x,
		m_pos.y - m_img->m_info.Height / 2 * m_size.y,
		m_pos.x + m_img->m_info.Width / 2 * m_size.x,
		m_pos.y + m_img->m_info.Height / 2 * m_size.y
	};

	//총알의 반지름은 이미지의 가로 길이의 절반으로
	if (OBB(m_pos, pPos, rect, pRect, m_rot, player->GetRot())) {
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
