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

	m_ani = new cAnimation((INT)(1000.f / m_endframes[m_color]), m_endframes[m_color]);
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
	
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	VEC2 dir = nowPath.m_pos - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	FLOAT moveDist = D3DXVec2Length(&(dir * nowPath.m_speed * D_TIME));
	moveDist *= m_isAccelCurve ? m_accelCurve : 1;

	BOOL cngNextPoint = m_path->Update(m_pos, moveDist);
	if (m_path->m_isDone == TRUE) {
		m_isLive = FALSE;
		return;
	}

	if (cngNextPoint == TRUE) {
		if (m_path->m_nowPos != 0)
			m_pos = m_path->m_endPoint[m_path->m_nowPos - 1].m_pos;
		else
			m_pos = m_path->m_endPoint[0].m_pos;
	}

	Pattern();
}

void cFairy::Pattern()
{
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	//직선일 경우 Lerp
	if(nowPath.m_isCurve == FALSE)
		Lerp(m_pos, nowPath.m_pos, nowPath.m_speed);
	//곡선일 경우 단순 이동
	else {
		VEC2 dir = nowPath.m_pos - m_pos;
		D3DXVec2Normalize(&dir, &dir);
		if (m_isAccelCurve == TRUE) {
			if (m_accelCurve < 1.f) m_accelCurve += D_TIME / m_divDelta;
			else m_accelCurve = 1.f;
			m_pos += dir * nowPath.m_speed * D_TIME * m_accelCurve;
		}
		else {
			m_pos += dir * nowPath.m_speed * D_TIME;
		}
	}

	if (CanFire()) {
		switch (m_kind) {
		case 1:
			//원형탄
			Pattern1(m_circleCnt);
			break;
		case 2:
			//여러 갈래로 나뉘는 난사 탄
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

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(0, 0), VEC2(-0.3f, -0.3f), VEC2(1.5f, 1.5f), 800.f, m_colorEffect[m_color]));
			eBullet.push_back(new cEnemyBullet(m_bullet_colorOne[m_color], m_pos, 1, m_bulletSpeed, dir, m_isAccel));

			if (m_isRandShot == TRUE) rot += 360 / cnt + (10 + rand() % 20);
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
			FLOAT rot = 360 / 10 * i + rand() % 360 / 10;
			VEC2 dir = VEC2(cos(D3DXToRadian(rot)), sin(D3DXToRadian(rot)));
			D3DXVec2Normalize(&dir, &dir);

			auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(0, 0), VEC2(-0.3f, -0.3f), VEC2(1.5f, 1.5f), 800.f, m_colorEffect[m_color]));
			eBullet.push_back(new cEnemyBullet(m_bullet_colorOne[m_color], m_pos, 1, m_bulletSpeed, dir, m_isAccel));
		}
		m_bulletTime = timeGetTime();
	}
	return;
}

