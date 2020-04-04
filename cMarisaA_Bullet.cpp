#include "DXUT.h"
#include "cBullet.h"
#include "cBulletAdmin.h"
#include "cItem.h"
#include "cItemAdmin.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"
#include "cPlayer.h"
#include "cMarisaA_Bullet.h"

cMarisaA_Bullet::cMarisaA_Bullet(VEC2 pos, VEC2 dir, VEC2 size, BOOL rotLeft, VEC4 color)
{
	m_img = new cImage;
	m_img->m_img = IMAGE->FindImage("spell_marisaA");

	m_speed = 200.f;

	m_pos = pos;
	m_dir = dir;
	m_size = size;
	m_rotLeft = rotLeft;

	m_img->m_a = color.x;
	m_img->m_r = color.y;
	m_img->m_g = color.z;
	m_img->m_b = color.w;

	m_img->SetNowRGB();
}

cMarisaA_Bullet::~cMarisaA_Bullet()
{
	SAFE_DELETE(m_img);
}

void cMarisaA_Bullet::Update()
{
	if (m_rotLeft == TRUE) m_rot-=5;
	else m_rot+=5;
	
	if (m_rot < 0) m_rot += 360;
	else if (m_rot > 360) m_rot -= 360;

	m_pos += m_speed * m_dir * D_TIME;
}

void cMarisaA_Bullet::Render()
{
	IMAGE->Render(m_img->m_img, m_pos, m_size, m_rot, TRUE, m_img->m_color);
}

void cMarisaA_Bullet::OutMapChk()
{
	if (m_pos.x - m_img->m_img->m_info.Width / 2 * m_size.x > 50 + INGAMEX ||
		m_pos.x + m_img->m_img->m_info.Width / 2 * m_size.x < 50 ||
		m_pos.y - m_img->m_img->m_info.Height / 2 * m_size.y > 50 + INGAMEY ||
		m_pos.y + m_img->m_img->m_info.Height / 2 * m_size.y < 50
		) m_isLive = FALSE;
	else return;
}

void cMarisaA_Bullet::Collision()
{
	FLOAT pRad = m_img->m_img->m_info.Width / 2 * m_size.x;

	auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
	auto& eOne = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
	auto& eFairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();

	//스펠 총알과 충돌하는 모든 적 총알들은 탄 소거 아이템이 된다.
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
			//탄 소거아이템은 항상 플레이어에게 흡수됨
			items[items.size() - 1]->m_followPlayer = TRUE;
			iter->GetRefLive() = FALSE;
		}
	}

	size_t size = eOne.size();
	for (size_t i = 0; i < size; i++) {
		//적의 충돌범위는 이미지의 가로 길이 중 절반을 반지름으로 설정한 원
		if (CIRCLE(m_pos, eOne[i]->GetPos(), pRad, eOne[i]->GetImg()->m_info.Width / 2.f)) {
			SOUND->Copy("hitSND");
			((cPlayer*)OBJFIND(PLAYER))->m_score += 10;

			eOne[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_shotAtk / 2.f;
			if (eOne[i]->m_hp < 1)
				eOne[i]->GetRefLive() = FALSE;
			return;
		}
	}

	size = eFairy.size();
	for (size_t i = 0; i < size; i++) {
		//적의 충돌범위는 이미지의 가로 길이 중 절반을 반지름으로 설정한 원
		if (CIRCLE(m_pos, eFairy[i]->GetPos(), pRad, eFairy[i]->GetImg()->m_info.Width / 2.f)) {
			SOUND->Copy("hitSND");
			((cPlayer*)OBJFIND(PLAYER))->m_score += 10;
			
			eFairy[i]->m_hp -= ((cPlayer*)OBJFIND(PLAYER))->m_shotAtk / 2.f;
			if (eFairy[i]->m_hp < 1)
				eFairy[i]->GetRefLive() = FALSE;
			return;
		}
	}
}
