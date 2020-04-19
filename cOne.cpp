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
	SAFE_DELETE(m_path);
}

void cOne::Update()
{
	m_rot += 10;
	if (m_rot > 360.f) m_rot -= 360.f;

	Pattern();
}

void cOne::Pattern()
{
	switch (m_kind) {
	case 1:
		Pattern1();
		break;
	case 2:
		Pattern2();
		break;
	default:
		break;
	}
}

void cOne::Pattern1()
//�ݽð�������� ���鼭
//���� ����� źȯ 2�� �߻�
{
	INT nowTime = timeGetTime() - m_bulletTime;

	//�̵�
	//�ݽð�������� ���� ��
	m_dirRot--;
	if (m_dirRot < -200.f) {
		m_pos = VEC2(50 + INGAMEX + 100, 50 + INGAMEY + 100);
		m_isLive = FALSE;
	}

	VEC2 dir;
	dir.x = cos(D3DXToRadian(m_dirRot)) * 600;
	dir.y = sin(D3DXToRadian(m_dirRot)) * 100;
	D3DXVec2Normalize(&dir, &dir);

	m_pos += dir * 300.f * D_TIME;

	//����
	if (CanFire() == true && nowTime > m_bulletDelay) {
		SOUND->Copy("normalshotSND");
		//�÷��̾� �ٶ󺸴� �������� �¿쿡 4���� ����� �Ѿ�
		auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
		VEC2 pPos = ((cPlayer*)OBJFIND(PLAYER))->GetPos();

		//�÷��̾ �ٶ�
		VEC2 m_bDir = pPos - m_pos;
		FLOAT rot = D3DXToDegree(atan2(m_bDir.y, m_bDir.x));

		FLOAT newRot;
		for (size_t j = 0; j < 2; j++) {
			newRot = rot + m_theta * m_bulletCnt / 2;
			for (size_t i = 0; i < m_bulletCnt; i++) {
				m_bDir.x = cos(D3DXToRadian(newRot));
				m_bDir.y = sin(D3DXToRadian(newRot));
				D3DXVec2Normalize(&m_bDir, &m_bDir);

				EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(0, 0), VEC2(-0.3f, -0.3f), VEC2(2.f, 2.f)));
				eBullet.push_back(new cEnemyBullet("bullet_blueMeal", m_pos, 1, m_bulletSpeed + j * 30, m_bDir, m_isAccel, VEC2(1, 1), newRot + 90));
				newRot -= m_theta;
			}
		}
		m_bulletTime = timeGetTime();
	}
}

void cOne::Pattern2()
{
	INT nowTime = timeGetTime() - m_bulletTime;

	//�ð�������� ���� ��
	m_dirRot--;
	if (m_dirRot < -360.f) {
		m_pos = VEC2(50 + INGAMEX + 100, 50 + INGAMEY + 100);
		m_isLive = FALSE;
	}

	VEC2 dir;
	dir.x = -cos(D3DXToRadian(m_dirRot)) * 600;
	dir.y = sin(D3DXToRadian(m_dirRot)) * 100;
	D3DXVec2Normalize(&dir, &dir);

	m_pos += dir * 300.f * D_TIME;

	//����
	if (CanFire() == true && nowTime > m_bulletDelay) {
		SOUND->Copy("normalshotSND");

		//�÷��̾� �ٶ󺸴� �������� �¿쿡 4���� ����� �Ѿ�
		auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
		VEC2 pPos = ((cPlayer*)OBJFIND(PLAYER))->GetPos();

		//�÷��̾ �ٶ�
		VEC2 m_bDir = pPos - m_pos;
		FLOAT rot = D3DXToDegree(atan2(m_bDir.y, m_bDir.x));

		FLOAT newRot;
		for (size_t j = 0; j < 2; j++) {
			newRot = rot + m_theta * m_bulletCnt / 2;
			for (size_t i = 0; i < m_bulletCnt; i++) {
				m_bDir.x = cos(D3DXToRadian(newRot));
				m_bDir.y = sin(D3DXToRadian(newRot));
				D3DXVec2Normalize(&m_bDir, &m_bDir);

				EFFECT->AddEffect(new cEffect("createBullet_EFFECT", 1, m_pos, VEC2(0, 0), VEC2(-0.3f, -0.3f), VEC2(2.5f, 2.5f)));
				eBullet.push_back(new cEnemyBullet("bullet_blueMeal", m_pos, 1, m_bulletSpeed + j * 30, m_bDir, m_isAccel, VEC2(1, 1), newRot + 90));
				newRot -= m_theta;
			}
		}
		m_bulletTime = timeGetTime();
	}
}
