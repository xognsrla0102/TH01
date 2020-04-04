#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cBall.h"
#include "cBalls.h"
#include "cEnemyAdmin.h"
#include "cBallBullet.h"

cBallBullet::cBallBullet(string key, VEC2 pos, VEC2 dir, VEC2 size, FLOAT rot, BOOL isHoming)
{
	m_img = new cImage;
	if (isMarisa == TRUE && isB == TRUE) {
		INT border, pLevel = ((cPlayer*)OBJFIND(PLAYER))->m_level;
		if (pLevel > 7) border = 2;
		else if (pLevel > 4) border = 1;
		else border = 0;

		CHAR temp[256];
		sprintf(temp, key.c_str(), border);
		m_img->m_img = IMAGE->FindImage(temp);
	}
	else m_img->m_img = IMAGE->FindImage(key);
	m_img->m_color = D3DCOLOR_ARGB(200, 255, 255, 255);

	m_isHoming = isHoming;

	m_pos = pos;
	m_dir = dir;
	m_size = size;
	m_rot = rot;
	m_speed = 1500.f;
	if (isMarisa == TRUE) {
		if (isB == FALSE) {
			m_accel = 0.f;
		}
		else {
			m_img->m_a = 0.f;
			m_img->SetNowRGB();
		}
	}
}

cBallBullet::~cBallBullet()
{
	SAFE_DELETE(m_img);
}

void cBallBullet::Update()
{
	if (isMarisa == TRUE) {
		if (isB == FALSE) {
			m_accel += D_TIME * 2;
		}
		else {
			//먼저 페이드인을 함
			if (m_isFadeIn == FALSE && (INT)m_img->m_a < 200) {
				m_img->m_a += 10;
				m_img->SetNowRGB();
			}
			//페이드인이 끝나면 어택 타임을 시작함
			else if(m_atkTime == 0 && m_isFadeIn == FALSE && (INT)m_img->m_a >= 200) {
				m_img->m_a = 200;
				m_atkTime = timeGetTime();
			}
			//어택타임을 시작하고 그 딜레이를 넘어서면 
			else if (m_atkTime != 0 && m_isFadeIn == FALSE) {
				if (timeGetTime() - m_atkTime > m_atkDelay)
					m_isFadeIn = TRUE;
			}
			//페이드 아웃을 시작함
			else if (m_isFadeIn == TRUE) {
				if ((INT)m_img->m_a > 0) m_img->m_a -= 10;
				else m_img->m_a = 0;
				m_img->SetNowRGB();

				if((INT)m_img->m_a == 0)
					m_isLive = FALSE;
			}
		}
	}

	if (m_accel > 1.f) m_accel = 1.f;
	if (m_isHoming == TRUE) Homing();

	//마리사B가 아니면 이동
	if(!(isMarisa == TRUE && isB == TRUE))
		m_pos += m_dir * m_speed * D_TIME * m_accel;
	//마리사 B라면 볼의 위치로
	else {
		//볼이 존재한다면 위치를 옮기고
		auto& balls = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls();
		if (balls.size() != 0) {
			m_pos.x = balls[m_index]->GetPos().x;
			m_pos.y = balls[m_index]->GetPos().y - 310;
		}
		//볼이 없다면 레이저 파괴
		else {
			m_isLive = FALSE;
		}
	}
	if (isMarisa == FALSE && isB == FALSE) m_rot -= 8;
	if (m_rot < 0) m_rot += 360;
}

void cBallBullet::Render()
{
	IMAGE->Render(m_img->m_img, m_pos, m_size, m_rot, TRUE, m_img->m_color);
}

void cBallBullet::OutMapChk()
{
	if (m_pos.x - m_img->m_img->m_info.Width / 2 > 50 + INGAMEX ||
		m_pos.x + m_img->m_img->m_info.Width / 2 < 50 ||
		m_pos.y - m_img->m_img->m_info.Height / 2 > 50 + INGAMEY ||
		m_pos.y + m_img->m_img->m_info.Height / 2 < 50
		) m_isLive = FALSE;
	else return;
}

void cBallBullet::Collision()
{
	RECT bBulletRect = {
		m_pos.x - m_img->m_img->m_info.Width / 2,
		m_pos.y - m_img->m_img->m_info.Height / 2,
		m_pos.x + m_img->m_img->m_info.Width / 2,
		m_pos.y + m_img->m_img->m_info.Height / 2,
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

			int theta = rand() % 360;
			VEC2 dir(cos(D3DXToRadian(theta)), sin(D3DXToRadian(theta)));
			D3DXVec2Normalize(&dir, &dir);

			VEC4 color;
			if (isMarisa == FALSE && isB == FALSE)
				color = VEC4(200, 130, 130, 255);
			else if (isMarisa == FALSE && isB == TRUE)
				color = VEC4(200, 255, 255, 255);
			else if (isMarisa == TRUE && isB == FALSE)
				color = VEC4(200, 130, 255, 130);
			else if (isMarisa == TRUE && isB == TRUE)
				color = VEC4(200, 255, 255, 130);

			//레이무B가 아닐 경우
			if (!(isMarisa == FALSE && isB == TRUE)) {
				EFFECT->AddEffect(
					new cEffect("enemyHit_EFFECT", 1, m_pos, dir, VEC2(-1.f, -1.f), VEC2(3, 3), 300.f, color)
				);
			}
			//레이무B는 세로로 길어짐
			else {
				EFFECT->AddEffect(
					new cEffect("player_reimou_subShot1", 1, m_pos, VEC2(0, 0), VEC2(0.f, 0.1f), VEC2(1, 1), 300.f, color)
				);
			}

			//레이저는 관통함
			if(!(isMarisa == TRUE && isB == TRUE))
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

			int theta = rand() % 360;
			VEC2 dir(cos(D3DXToRadian(theta)), sin(D3DXToRadian(theta)));
			D3DXVec2Normalize(&dir, &dir);

			VEC4 color;
			if (isMarisa == FALSE && isB == FALSE)
				color = VEC4(200, 130, 130, 255);
			else if (isMarisa == FALSE && isB == TRUE)
				color = VEC4(200, 255, 255, 255);
			else if (isMarisa == TRUE && isB == FALSE)
				color = VEC4(200, 130, 255, 130);
			else if (isMarisa == TRUE && isB == TRUE)
				color = VEC4(200, 255, 255, 130);

			//레이무B가 아닐 경우
			if (!(isMarisa == FALSE && isB == TRUE)) {
				EFFECT->AddEffect(
					new cEffect("enemyHit_EFFECT", 1, m_pos, dir, VEC2(-1.f, -1.f), VEC2(3, 3), 300.f, color)
				);
			}
			//레이무B는 세로로 길어짐
			else {
				EFFECT->AddEffect(
					new cEffect("player_reimou_subShot1", 1, m_pos, VEC2(0, 0), VEC2(0.f, 0.1f), VEC2(1, 1), 300.f, color)
				);
			}

			if (!(isMarisa == TRUE && isB == TRUE))
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

