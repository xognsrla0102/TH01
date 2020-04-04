#include "DXUT.h"

#include "cTimer.h"

#include "cPlayer.h"
#include "cBulletAdmin.h"

#include "cEnemy.h"
#include "cEnemyAdmin.h"

#include "cItem.h"
#include "cItemAdmin.h"

#include "cReimouA_Bullet.h"

cReimouA_Bullet::cReimouA_Bullet(VEC2 pos)
{
	m_rgbTimers[0] = new cTimer(300 + rand() % 4 * 100);
	m_rgbTimers[1] = new cTimer(300 + rand() % 4 * 100);
	m_rgbTimers[2] = new cTimer(300 + rand() % 4 * 100);

	m_img = new cImage;
	m_img->m_img = IMAGE->FindImage("spell_reimouA");

	m_img->m_a = 180.f;
	m_img->SetNowRGB();

	D3DXVec2Normalize(&m_dir, &(OBJFIND(PLAYER)->GetPos() - m_pos));

	m_size = VEC2(0, 0);
	m_pos = pos;
	m_speed = 1300.f;
}

cReimouA_Bullet::~cReimouA_Bullet()
{
	for (auto iter : m_rgbTimers)
		SAFE_DELETE(iter);
	SAFE_DELETE(m_img);
}

void cReimouA_Bullet::Update()
{
	if (timeGetTime() - m_start > 2000) {
		SOUND->Copy("chargeshotSND");
		SOUND->Copy("chargeshotSND");
		//���� �� ����Ʈ�� �Բ� ī�޶� ����
		EFFECT->AddEffect(
			new cEffect("enemy_dead_EFFECT", 1, m_pos, VEC2(0, 0),
				VEC2(1.5f, 1.5f), VEC2(2.f, 2.f), 500.f
			)
		);

		CAMERA->m_delay = 30;
		CAMERA->m_velocity = 30;
		CAMERA->m_isShake = TRUE;
		m_isLive = FALSE;
	}

	for (size_t i = 0; i < 3; i++) {
		if (m_rgbTimers[i]->Update()) {
			m_rgbTimers[i]->m_delay = 300 + rand() % 4 * 100;
			m_rgbDir[i] = (m_rgbDir[i] == 1) ? -3 : 3;
		}
		else {
			if(m_img->m_r > 254) m_rgbDir[0] = (m_rgbDir[0] == 1) ? -3 : 3;
			else if (m_img->m_g > 254) m_rgbDir[1] = (m_rgbDir[1] == 1) ? -3 : 3;
			else if (m_img->m_b > 254) m_rgbDir[2] = (m_rgbDir[2] == 1) ? -3 : 3;

			if(i == 0) m_img->m_r += m_rgbDir[i];
			else if (i == 1) m_img->m_g += m_rgbDir[i];
			else if(i == 2) m_img->m_b += m_rgbDir[i];
		}
	}
	m_img->SetNowRGB();

	if (m_size.x < 5.f && m_size.y < 5.f)
		m_size += VEC2(0.05f, 0.05f);

	Homing();

	if (m_accel < 1.f) m_accel += D_TIME;
	else m_accel = 1.f;

	m_pos += m_dir * m_speed * m_accel * D_TIME;
}

void cReimouA_Bullet::Render()
{
	IMAGE->Render(m_img->m_img, m_pos, m_size, 0.f, TRUE, m_img->m_color);
}

void cReimouA_Bullet::OutMapChk()
{
	if (m_pos.x - m_img->m_img->m_info.Width / 2 * m_size.x > 50 + INGAMEX ||
		m_pos.x + m_img->m_img->m_info.Width / 2 * m_size.x < 50 ||
		m_pos.y - m_img->m_img->m_info.Height / 2 * m_size.y > 50 + INGAMEY ||
		m_pos.y + m_img->m_img->m_info.Height / 2 * m_size.y < 50
		) m_isLive = FALSE;
	else return;
}

void cReimouA_Bullet::Collision()
{
	FLOAT pRad = m_img->m_img->m_info.Width / 2 * m_size.x;

	auto& eOne = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
	auto& eFairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
	auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();

	//���� �Ѿ˰� �浹�ϴ� ��� �� �Ѿ˵��� ź �Ұ� �������� �ȴ�.
	for (auto iter : eBullet) {
		if (CIRCLE(m_pos, iter->GetPos(), pRad, iter->GetImg()->m_info.Width / 2.f)) {
			EFFECT->AddEffect(
				new cEffect("enemy_dead_EFFECT", 1, iter->GetPos(), VEC2(0, 0),
					VEC2(0.2f, 0.2f), VEC2(0.3f, 0.3f)
				)
			);
			auto& items = ((cItemAdmin*)OBJFIND(ITEMS))->m_items;
			items.push_back(
				new cItem("item_tan", iter->GetPos(), iter->GetPos())
			);
			//ź �Ұž������� �׻� �÷��̾�� �����
			items[items.size() - 1]->m_followPlayer = TRUE;

			iter->GetRefLive() = FALSE;
		}
	}

	size_t size = eOne.size();
	for (size_t i = 0; i < size; i++) {
		//���� �浹������ �̹����� ���� ���� �� ������ ���������� ������ ��
		if (CIRCLE(m_pos, eOne[i]->GetPos(), pRad, eOne[i]->GetImg()->m_info.Width / 2.f)) {
			SOUND->Copy("hitSND");
			((cPlayer*)OBJFIND(PLAYER))->m_score += 10;
			m_life--;
			if (m_life < 1) {
				SOUND->Copy("chargeshotSND");
				SOUND->Copy("chargeshotSND");
				//���� �� ����Ʈ�� �Բ� ī�޶� ����
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, m_pos, VEC2(0, 0),
						VEC2(1.5f, 1.5f), VEC2(2.f, 2.f), 500.f
					)
				);

				CAMERA->m_delay = 30;
				CAMERA->m_velocity = 15;
				CAMERA->m_isShake = TRUE;

				m_isLive = FALSE;
			}
			eOne[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_shotAtk * 5;
			if (eOne[i]->m_hp <= 0.f)
				eOne[i]->GetRefLive() = FALSE;
			return;
		}
	}

	size = eFairy.size();
	for (size_t i = 0; i < size; i++) {
		//���� �浹������ �̹����� ���� ���� �� ������ ���������� ������ ��
		if (CIRCLE(m_pos, eFairy[i]->GetPos(), pRad, eFairy[i]->GetImg()->m_info.Width / 2.f)) {
			SOUND->Copy("hitSND");
			((cPlayer*)OBJFIND(PLAYER))->m_score += 10;
			m_life--;
			if (m_life < 1) {
				SOUND->Copy("chargeshotSND");
				SOUND->Copy("chargeshotSND");
				//���� �� ����Ʈ�� �Բ� ī�޶� ����
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, m_pos, VEC2(0, 0),
						VEC2(1.5f, 1.5f), VEC2(2.f, 2.f), 500.f
					)
				);
				CAMERA->m_delay = 30;
				CAMERA->m_velocity = 15;
				CAMERA->m_isShake = TRUE;

				m_isLive = FALSE;
			}
			//�⺻ ���� 5�� ���� ���� ������
			eFairy[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_shotAtk * 5;
			if (eFairy[i]->m_hp <= 0.f)
				eFairy[i]->GetRefLive() = FALSE;
			return;
		}
	}
}

void cReimouA_Bullet::Homing()
{
	//���� źȯ�� �������� �� �߽������� ���� �Ÿ��� ����� ���� ã�ƾ���
	auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
	auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();

	//������ �Ŵ� ��ġ�� �˸� ��
	VEC2 shortPos(WINSIZEX, WINSIZEY);
	FLOAT shortDist = DistPoint(VEC2(0, 0), shortPos);

	for(auto iter : one){
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

	VEC2 normDir;

	VEC2 pPos = OBJFIND(PLAYER)->GetPos();

	//�� �ȿ� ������ ���� ���� ��� �⺻������ �÷��̾ �����ϵ��� ����
	if (shortPos == VEC2(WINSIZEX, WINSIZEY))
		D3DXVec2Normalize(&normDir, &(VEC2(-50 + pPos.x + rand() % 100, -50 + pPos.y + rand() % 100) - m_pos));
	//���� �ִٸ� �� ���� ���� �������� ����
	else D3DXVec2Normalize(&normDir, &VEC2(shortPos - m_pos));

	Lerp(m_dir, normDir, 0.08f);
}

