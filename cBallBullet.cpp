#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"
#include "cBallBullet.h"

cBallBullet::cBallBullet(string key, VEC2 pos, VEC2 dir, VEC2 size, FLOAT rot, BOOL isHoming)
{
	m_img = IMAGE->FindImage(key);
	m_img->m_color = D3DCOLOR_ARGB(200, 255, 255, 255);

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
	if (m_isHoming == TRUE) Homing();
	m_pos += m_dir * m_speed * D_TIME;

	if (isMarisa == FALSE && isB == FALSE) m_rot -= 8;
	if (m_rot < 0) m_rot += 360;
}

void cBallBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > 50 + INGAMEX ||
		m_pos.x + m_img->m_info.Width / 2 < 50 ||
		m_pos.y - m_img->m_info.Height / 2 > 50 + INGAMEY ||
		m_pos.y + m_img->m_info.Height / 2 < 50
		) m_isLive = FALSE;
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

		if (OBB(m_pos, onePos, bBulletRect, oneRect, m_rot, eOne[i]->GetRot()) == TRUE) {
			SOUND->Copy("hitSND");
			m_isLive = FALSE;
			eOne[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_subShotAtk;
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

		if (OBB(m_pos, fryPos, bBulletRect, fryRect, m_rot, eFairy[i]->GetRot()) == TRUE) {
			SOUND->Copy("hitSND");
			m_isLive = FALSE;
			eFairy[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_subShotAtk;
			if (eFairy[i]->m_hp <= 0.f)
				eFairy[i]->GetRefLive() = FALSE;
			return;
		}
	}
}

void cBallBullet::Homing()
{
	//현재 탄환을 기준으로 한 중심점에서 가장 거리가 가까운 적을 찾아야함
	auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
	auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();

	//유도할 거니 위치만 알면 됨
	VEC2 shortPos(WINSIZEX, WINSIZEY);
	FLOAT shortDist = DistPoint(VEC2(0, 0), shortPos);

	for (auto iter : one) {
		if (DistPoint(m_pos, iter->GetPos()) < shortDist) {
			shortPos = iter->GetPos();
			shortDist = DistPoint(m_pos, shortPos);
		}
	}
	for (auto iter : fairy) {
		if (DistPoint(m_pos, iter->GetPos()) < shortDist) {
			shortPos = iter->GetPos();
			shortDist = DistPoint(m_pos, shortPos);
		}
	}

	if (shortPos == VEC2(WINSIZEX, WINSIZEY)) return;

	VEC2 normDir;
	D3DXVec2Normalize(&normDir, &VEC2(shortPos - m_pos));
	Lerp(m_dir, normDir, 0.1);
}

