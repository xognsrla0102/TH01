#include "DXUT.h"
#include "cBulletAdmin.h"
#include "cEnemyBullet.h"
#include "cPlayer.h"
#include "cOne.h"

cOne::cOne(INT hp, INT kind, VEC2 pos, FLOAT rot, VEC2 size)
{
	m_hp = hp;
	m_kind = kind;

	m_img = IMAGE->FindImage("enemy_one");
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

cOne::~cOne()
{
}

void cOne::Update()
{
	m_rot += 10;
	if (m_rot > 360.f) m_rot -= 360.f;

	Pattern();
}

void cOne::Pattern()
{
	INT nowTime = timeGetTime() - m_patternTime;

	switch (m_kind) {
	case 1:
		Pattern1(nowTime);
		break;
	case 2:
		Pattern2(nowTime);
		break;
	default:
		break;
	}
}

void cOne::Pattern1(INT nowTime)
{
	//�̵�
	//�ݽð�������� ���� ��
	m_dirRot--;
	if (m_dirRot < -200.f)
		m_pos = VEC2(50 + INGAMEX + 100, 50 + INGAMEY + 100);

	VEC2 dir;
	dir.x = cos(D3DXToRadian(m_dirRot)) * 600;
	dir.y = sin(D3DXToRadian(m_dirRot)) * 100;
	D3DXVec2Normalize(&dir, &dir);

	m_pos += dir * 300.f * D_TIME;

	//����
	if (CanFire() == true && timeGetTime() - m_bulletTime > 500) {
		SOUND->Copy("normalshotSND");
		//�÷��̾� �ٶ󺸴� �������� �¿쿡 4���� ����� �Ѿ�
		auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
		VEC2 pPos = ((cPlayer*)OBJFIND(PLAYER))->GetPos();

		//�÷��̾ �ٶ�
		VEC2 m_bDir = pPos - m_pos;
		FLOAT rot = D3DXToDegree(atan2(m_bDir.y, m_bDir.x));

		FLOAT newRot = rot + 10 * 2;
		for (size_t i = 0; i < 5; i++) {
			m_bDir.x = cos(D3DXToRadian(newRot));
			m_bDir.y = sin(D3DXToRadian(newRot));
			D3DXVec2Normalize(&m_bDir, &m_bDir);

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(-0.3f, -0.3f), VEC2(2.5f, 2.5f)));
			eBullet.push_back(new cEnemyBullet("bullet_blueMeal", m_pos, 1, 70.f, m_bDir, VEC2(1, 1), newRot + 90));
			newRot -= 10;
		}

		newRot = rot + 10 * 2;
		for (size_t i = 0; i < 5; i++) {
			m_bDir.x = cos(D3DXToRadian(newRot));
			m_bDir.y = sin(D3DXToRadian(newRot));
			D3DXVec2Normalize(&m_bDir, &m_bDir);

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(-0.3f, -0.3f), VEC2(2.5f, 2.5f)));
			eBullet.push_back(new cEnemyBullet("bullet_blueMeal", m_pos, 1, 100.f, m_bDir, VEC2(1.f, 1.f), newRot + 90));
			newRot -= 10;
		}
		m_bulletTime = timeGetTime();
	}
}

void cOne::Pattern2(INT nowTime)
{
	//�ð�������� ���� ��
	m_dirRot--;
	if (m_dirRot < -360.f)
		m_pos = VEC2(50 + INGAMEX + 100, 50 + INGAMEY + 100);

	VEC2 dir;
	dir.x = -cos(D3DXToRadian(m_dirRot)) * 600;
	dir.y = sin(D3DXToRadian(m_dirRot)) * 100;
	D3DXVec2Normalize(&dir, &dir);

	m_pos += dir * 300.f * D_TIME;

	//����
	if (CanFire() == true && timeGetTime() - m_bulletTime > 500) {
		SOUND->Copy("normalshotSND");

		//�÷��̾� �ٶ󺸴� �������� �¿쿡 4���� ����� �Ѿ�
		auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
		VEC2 pPos = ((cPlayer*)OBJFIND(PLAYER))->GetPos();

		//�÷��̾ �ٶ�
		VEC2 m_bDir = pPos - m_pos;
		FLOAT rot = D3DXToDegree(atan2(m_bDir.y, m_bDir.x));

		FLOAT newRot = rot + 10 * 2;
		for (size_t i = 0; i < 5; i++) {
			m_bDir.x = cos(D3DXToRadian(newRot));
			m_bDir.y = sin(D3DXToRadian(newRot));
			D3DXVec2Normalize(&m_bDir, &m_bDir);

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(-0.3f, -0.3f), VEC2(2.5f, 2.5f)));
			eBullet.push_back(new cEnemyBullet("bullet_blueMeal", m_pos, 1, 70.f, m_bDir, VEC2(1, 1), newRot + 90));
			newRot -= 10;
		}

		newRot = rot + 10 * 2;
		for (size_t i = 0; i < 5; i++) {
			m_bDir.x = cos(D3DXToRadian(newRot));
			m_bDir.y = sin(D3DXToRadian(newRot));
			D3DXVec2Normalize(&m_bDir, &m_bDir);

			EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(-0.3f, -0.3f), VEC2(2.5f, 2.5f)));
			eBullet.push_back(new cEnemyBullet("bullet_blueMeal", m_pos, 1, 100.f, m_bDir, VEC2(1.f, 1.f), newRot + 90));
			newRot -= 10;
		}
		m_bulletTime = timeGetTime();
	}
}
