#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"
#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(string key, VEC2 pos, VEC2 dir, VEC2 size, FLOAT rot)
{
	m_img = IMAGE->FindImage(key);
	m_img->m_color = D3DCOLOR_ARGB(200, 255, 255, 255);

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
	if(isMarisa == FALSE) m_rot -= 8;
	if (m_rot < 0) m_rot += 360;
}

void cPlayerBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > 50 + INGAMEX ||
		m_pos.x + m_img->m_info.Width / 2 < 50 ||
		m_pos.y - m_img->m_info.Height / 2 > 50 + INGAMEY ||
		m_pos.y + m_img->m_info.Height / 2 < 50
		) m_isLive = FALSE;
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
	auto& eFairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();

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

		if (OBB(m_pos, onePos, pBulletRect, oneRect, m_rot, eOne[i]->GetRot()) == TRUE) {
			SOUND->Copy("hitSND");

			int theta = rand() % 360;
			VEC2 dir(cos(D3DXToRadian(theta)), sin(D3DXToRadian(theta)));
			D3DXVec2Normalize(&dir, &dir);

			VEC4 color;
			if (isMarisa == FALSE) color = VEC4(200, 255, 130, 130);
			else color = VEC4(200, 130, 130, 255);

			EFFECT->AddEffect(
				new cEffect("enemyHit_EFFECT", 1, m_pos, dir, VEC2(-1.f, -1.f), VEC2(3, 3), 300.f, color)
			);

			((cPlayer*)OBJFIND(PLAYER))->m_score += 10;
			m_isLive = FALSE;
			eOne[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_shotAtk;
			if (eOne[i]->m_hp <= 0.f)
				eOne[i]->GetRefLive() = FALSE;
			return;
		}
	}

	size = eFairy.size();
	for (size_t i = 0; i < size; i++) {
		VEC2 fryPos = eFairy[i]->GetPos();
		cTexture* fryImg = eFairy[i]->GetImg();

		RECT fryRect = {
			fryPos.x - fryImg->m_info.Width / 2,
			fryPos.y - fryImg->m_info.Height / 2,
			fryPos.x + fryImg->m_info.Width / 2,
			fryPos.y + fryImg->m_info.Height / 2,
		};

		if (OBB(m_pos, fryPos, pBulletRect, fryRect, m_rot, eFairy[i]->GetRot()) == TRUE) {
			SOUND->Copy("hitSND");

			int theta = rand() % 360;
			VEC2 dir(cos(D3DXToRadian(theta)), sin(D3DXToRadian(theta)));
			D3DXVec2Normalize(&dir, &dir);

			VEC4 color;
			if (isMarisa == FALSE) color = VEC4(200, 255, 130, 130);
			else color = VEC4(200, 130, 130, 255);

			EFFECT->AddEffect(
				new cEffect("enemyHit_EFFECT", 1, m_pos, dir, VEC2(-1.f, -1.f), VEC2(3, 3), 300.f, color)
			);

			((cPlayer*)OBJFIND(PLAYER))->m_score += 10;
			m_isLive = FALSE;
			eFairy[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_shotAtk;
			if (eFairy[i]->m_hp <= 0.f)
				eFairy[i]->GetRefLive() = FALSE;
			return;
		}
	}
}
