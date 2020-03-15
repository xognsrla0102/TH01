#include "DXUT.h"
#include "cBulletAdmin.h"
#include "cEnemyBullet.h"
#include "cFairy.h"

cFairy::cFairy(INT hp, INT color, INT kind, VEC2 pos, FLOAT rot, VEC2 size)
{
	m_hp = hp;
	m_color = color;
	m_kind = kind;
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	m_ani = new cAnimation(100, m_endframes[m_color]);
} 

cFairy::~cFairy()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_path);
}

void cFairy::Update()
{
	m_ani->Update();
	m_img = IMAGE->FindImage(m_colorKey[m_color], m_ani->m_nowFrame);
	
	BOOL cngNextPoint = m_path->Update(m_pos);
	if (m_path->m_isDone == TRUE) {
		m_isLive = FALSE;
		return;
	}

	if (cngNextPoint == TRUE)
		m_pos = m_path->m_endPoint[m_path->m_nowPos - 1].m_pos;

	Pattern();
}

void cFairy::Pattern()
{
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	//직선일 경우 Lerp
	Lerp(m_pos, nowPath.m_pos, nowPath.m_speed);

	//곡선일 경우 단순 이동
	//곡선 이동 처리

	if (CanFire()) {
		switch (m_kind) {
		case 1:
			//원형탄
			Pattern1(m_circleCnt);
			break;
		case 2:
			//3갈래로 나뉘는 난사 탄
			Pattern2();
		default:
			break;
		}
	}
}

void cFairy::Pattern1(INT cnt)
{
	INT nowTime = timeGetTime() - m_bulletTime;

	if (nowTime > m_bulletDelay) {
		SOUND->Copy("normalshotSND");
		for (size_t i = 0, rot = 0; i < cnt; i++) {
			VEC2 dir = VEC2(cos(D3DXToRadian(rot)), sin(D3DXToRadian(rot)));
			D3DXVec2Normalize(&dir, &dir);

			auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(-0.3f, -0.3f), VEC2(1.5f, 1.5f), 800.f, VEC4(150, 128, 128, 255)));
			eBullet.push_back(new cEnemyBullet("bullet_blueOne", m_pos, 1, m_bulletSpeed, dir, m_isAccel));

			if (m_isRandShot == TRUE) rot += 10 + rand() % 20;
			else rot += 360 / cnt;
		}
		m_bulletTime = timeGetTime();
	}
	return;
}

void cFairy::Pattern2()
{
	INT nowTime = timeGetTime() - m_bulletTime;

	if (nowTime > m_bulletDelay) {
		SOUND->Copy("normalshotSND");
		for (size_t i = 1; i <= 10; i++) {
			FLOAT rot = 36 * i + rand() % 36;
			VEC2 dir = VEC2(cos(D3DXToRadian(rot)), sin(D3DXToRadian(rot)));
			D3DXVec2Normalize(&dir, &dir);

			auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(-0.3f, -0.3f), VEC2(1.5f, 1.5f), 800.f, VEC4(150, 128, 128, 255)));
			eBullet.push_back(new cEnemyBullet("bullet_blueOne", m_pos, 1, m_bulletSpeed, dir, m_isAccel));
		}
		m_bulletTime = timeGetTime();
	}
	return;
}

