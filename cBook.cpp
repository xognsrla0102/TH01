#include "DXUT.h"
#include "cEnemyBullet.h"
#include "cEnemyRazer.h"
#include "cBulletAdmin.h"
#include "cBook.h"

cBook::cBook(INT hp, INT color, INT kind, BOOL onlyMagicZone, VEC2 pos, FLOAT rot, VEC2 size)
{
	m_magicZone = new cImage;
	m_magicZone->m_img = IMAGE->FindImage("enemy_magiczone");
	m_magicZone->m_pos = pos;
	m_magicZone->m_a = 0.f;
	m_magicZone->SetNowRGB();

	m_img = IMAGE->FindImage(m_colorKey[color]);
	
	m_hp = hp;
	m_color = color;
	m_kind = kind;
	m_onlyMagicZone = onlyMagicZone;
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	m_path = new cPath(m_pos);
	m_path->AddPoint(VEC2(m_pos.x, m_pos.y - 10), 8, 0);
	m_path->AddPoint(VEC2(m_pos.x, m_pos.y + 10), 8, 0);
	m_path->AddPoint(m_pos, 8, 0);
	m_path->m_isLoop = TRUE;
}

cBook::~cBook()
{
	SAFE_DELETE(m_magicZone);
	SAFE_DELETE(m_path);
}

void cBook::Update()
{
	Lerp(m_magicZone->m_a, 255.f, 0.05);
	m_magicZone->SetNowRGB();
	Lerp(m_alpha, 255.f, 0.05);

	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];
	VEC2 dir = nowPath.m_pos - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	FLOAT moveDist = D3DXVec2Length(&(dir * nowPath.m_speed * D_TIME));

	m_path->Update(m_pos, moveDist);

	Pattern();
}

void cBook::Render()
{
	IMAGE->Render(m_magicZone->m_img, m_magicZone->m_pos, 1.f, 0.f, TRUE, m_magicZone->m_color);
	if(m_onlyMagicZone == FALSE)
		IMAGE->Render(m_img, m_pos, 1.f, 0.f, TRUE, D3DCOLOR_ARGB((INT)m_alpha, 255, 255, 255));
}

void cBook::Pattern()
{
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	VEC2 dir = nowPath.m_pos - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	m_pos += dir * nowPath.m_speed * D_TIME;
		
	if (CanFire()) {
		switch (m_kind) {
		case 1:
			Pattern1(m_circleCnt);
			break;
		case 2:
			Pattern2();
			break;
		}
	}
}

void cBook::Pattern1(INT cnt)
{
	INT nowTime = timeGetTime() - m_bulletTime;

	if (nowTime > m_bulletDelay) {
		SOUND->Copy("normalshotSND");
		for (size_t i = 0, rot = 0; i < cnt; i++) {
			VEC2 dir = VEC2(cos(D3DXToRadian(rot)), sin(D3DXToRadian(rot)));
			D3DXVec2Normalize(&dir, &dir);

			auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(0, 0), VEC2(-0.3f, -0.3f), VEC2(1.5f, 1.5f), 800.f, m_colorEffect[m_color]));
			eBullet.push_back(new cEnemyBullet(m_bullet_colorOne[m_color], m_pos, 1, m_bulletSpeed, dir, m_isAccel));

			if (m_isRandShot == TRUE) rot += 360 / cnt + (10 + rand() % 20);
			else rot += 360 / cnt;
		}
		m_bulletTime = timeGetTime();
	}
	return;
}

void cBook::Pattern2()
{
	if (m_kind == 2) {
		SOUND->Copy("lazer0SND");
		auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
		eBullet.push_back(new cEnemyRazer(m_bullet_colorRazer[m_kind], m_pos, m_startDelay, m_atkDelay));
		m_kind = 0;
	}
}

