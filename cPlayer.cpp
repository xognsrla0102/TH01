#include "DXUT.h"
#include "cBalls.h"
#include "cBall.h"
#include "cPlayerBullet.h"
#include "cBallBullet.h"
#include "cBulletAdmin.h"
#include "cItem.h"
#include "cItemAdmin.h"
#include "cTimer.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{	
}

cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	if (isMarisa == FALSE) {
		m_bombFace = IMAGE->FindImage("spell_reimou_face");
		if (isB == FALSE)
			m_bombName = IMAGE->FindImage("spell_reimouA_name");
		else
			m_bombName = IMAGE->FindImage("spell_reimouB_name");
	}
	else {
		m_bombFace = IMAGE->FindImage("spell_marisa_face");
		if (isB == FALSE)
			m_bombName = IMAGE->FindImage("spell_marisaA_name");
		else
			m_bombName = IMAGE->FindImage("spell_marisaB_name");
	}
	m_bombFace->m_a = 200.f;
	m_bombFace->m_size = VEC2(1, 1);
	m_bombFace->SetNowRGB();

	m_bombName->m_a = 0.f;
	m_bombName->SetNowRGB();

	m_bombFace->m_pos = VEC2(-200, 50 + INGAMEY - 300);
	m_bombName->m_pos = VEC2(50 + 150, 50 + INGAMEY - 200);

	m_speed = 350.f;
	m_size = VEC2(1.f, 1.f);

	m_nowPlayerStatus = pIDLE;
	m_nowBulletCnt = 0;
	m_bulletCnt = 5;
	m_nowSubBulletCnt = 0;

	m_life = playerLife;
	m_bomb = playerBomb;

	m_level = 1;
	m_wasPower = 0;
	m_power = 0;
	m_graze = 0;
	m_jum = 0;

	m_nowRot = 0;

	m_score = 0.f;
	m_pAlpha = 255.f;

	m_hasBall = FALSE;
	m_isHit = FALSE;
	m_isNotDead = FALSE;
	m_isShot = FALSE;
	m_isSubShot = FALSE;
	m_isBomb = FALSE;
	m_isLevelUp = FALSE;
	m_isFullPower = FALSE;

	m_bulletTimer = new cTimer(80);
	m_subBulletTimer = new cTimer(100);

	m_bombTime = timeGetTime();

	m_ani = new cAnimation(100, 4);

	if (isMarisa == FALSE)
		if (isB == FALSE) m_subBulletTimer->m_delay = 450;
		else m_subBulletTimer->m_delay = 200;
	else
		if (isB == FALSE) m_subBulletTimer->m_delay = 200;
		else m_subBulletTimer->m_delay = 200;
}

void cPlayer::Update()
{
	INT wasLevel = m_level;

	//�÷��̾� �Ŀ� �ø��� ġƮ
	if (INPUT->KeyDown(DIK_A)) {
		if (m_power < 128) m_power += 8;
		if (m_power > 128) m_power = 128;
	}

	if (m_power == 128 && m_wasPower != 128)
		m_isFullPower = TRUE;

	if (m_power >= 128) {
		if (m_level != 9) m_level = 9;
	}
	else if (m_power >= 96)	{
		if(m_level != 8) m_level = 8;
	}
	else if (m_power >= 80)	{
		if(m_level != 7) m_level = 7;
	}
	else if (m_power >= 64)	{
		if(m_level != 6) m_level = 6;
	}
	else if (m_power >= 48)	{
		if(m_level != 5) m_level = 5;
	}
	else if (m_power >= 32)	{
		if(m_level != 4) m_level = 4;
	}
	else if (m_power >= 16)	{
		if(m_level != 3) m_level = 3;
	}
	else if (m_power >= 8) {
		if (m_level != 2) m_level = 2;
	}
	else {
		if (m_level != 1) m_level = 1;
	}

	if (wasLevel != m_level && wasLevel < m_level)
		m_isLevelUp = TRUE;

	if (m_isLevelUp == TRUE) {
		SOUND->Copy("powerupSND");
		EFFECT->AddEffect(
			new cEffect("powerUp_EFFECT", 1, VEC2(m_pos.x, m_pos.y - 20), TRUE, VEC2(0, -1))
		);
		m_isLevelUp = FALSE;
	}

	if (m_hasBall == FALSE && m_level > 1) {
		for (size_t i = 0; i < 2; i++) {
			//������ �� ����� ���� �� ����
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls().push_back(
				new cBall(OBJFIND(PLAYER)->GetRefPos(), i)
			);
		}
		m_hasBall = TRUE;
	}

	m_ani->Update();

	m_img = IMAGE->FindImage(
		m_pStatus[isMarisa][m_nowPlayerStatus],
		m_ani->m_nowFrame
	);

	if(m_nowPlayerStatus != pIDLE)
		m_nowPlayerStatus = pIDLE;

	if (m_isHit == TRUE) {
		Hit();
		return;
	}
	else if (m_isNotDead == TRUE) {
		NotDead();
	}

	Move();

	if (m_isShot == FALSE && INPUT->KeyPress(DIK_Z))
		m_isShot = m_isSubShot = TRUE;

	Fire();
	SubFire();
	Bomb();
}

void cPlayer::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, TRUE, D3DCOLOR_ARGB((int)m_pAlpha, 255, 255, 255));
}

void cPlayer::Release()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_bulletTimer);
	SAFE_DELETE(m_subBulletTimer);
}

void cPlayer::Hit()
{
	Lerp(m_pAlpha, 0.f, 0.1);
	Lerp(m_size, VEC2(0.5f, 2.f), 0.1);

	//m_isHit�� Ʈ���� ������ ��� ���������
	auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
	for (auto iter : eBullet) {
		EFFECT->AddEffect(
			new cEffect("enemy_dead_EFFECT", 1, iter->GetPos(),
				VEC2(0.5f, 0.5f), VEC2(0.3f, 0.3f)
			)
		);
		iter->GetRefLive() = FALSE;
	}

	if ((INT)m_pAlpha == 0) {
		m_ani->m_nowFrame = 0;
		m_nowPlayerStatus = pIDLE;
		m_bomb = playerBomb;
		m_isHit = FALSE;
		m_isNotDead = TRUE;
		m_notDeadTime = timeGetTime();
		m_size = VEC2(1.f, 1.f);
		if (m_power == 128) m_score -= 51200 + 150;
		else m_score -= 160;

		if (m_score < 0) m_score = 0;

		m_power -= 16;
		if (m_power < 0) m_power = 0;

		INT randNum, resultX;
		string key = "item_smallPower";

		for (size_t i = 0; i < 6; i++) {
			if (i == 5) key = "item_bigPower";

			randNum = 50 + rand() % 50;
			randNum *= rand() % 2 ? 1 : -1;
			resultX = m_pos.x + randNum;

			if (resultX < 50) resultX = 50 + 10;
			else if (resultX > 50 + INGAMEX) resultX = 50 + INGAMEX - 10;

			((cItemAdmin*)OBJFIND(ITEMS))->m_items.push_back(
				new cItem(key, VEC2(m_pos.x, m_pos.y - 10), VEC2(resultX, m_pos.y - (200 + rand() % 200)))
			);
		}

		m_pos = VEC2(50 + INGAMEX / 2, 50 + INGAMEY - 100);
	}
}

void cPlayer::NotDead()
{
	INT nowTime = timeGetTime() - m_notDeadTime;

	if (nowTime % 100 == 0) m_pAlpha = 0.f;
	else m_pAlpha = 200.f;

	if (nowTime > 4000) {
		m_pAlpha = 255.f;
		m_isNotDead = FALSE;
	}
}

void cPlayer::Fire()
{
	if (m_isShot == TRUE && m_bulletTimer->Update()) {
		//�Ѿ� �߻�
		SOUND->Copy("shotSND");
		char key[256];
		if (isMarisa == FALSE) sprintf(key, "player_reimou_mainShot");
		else sprintf(key, "player_marisa_mainShot");

		VEC2 rotVec;
		float rot = -90.f;
		
		if (isMarisa == FALSE) {
			if (isB == FALSE) {
				switch (m_level) {
				case 1:
				case 2:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos)
					);
					break;
				case 3:
					rot -= 2.5;
					for (size_t i = 0; i < 2; i++) {
						rotVec.x = cos(D3DXToRadian(rot));
						rotVec.y = sin(D3DXToRadian(rot));
						D3DXVec2Normalize(&rotVec, &rotVec);

						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
							new cPlayerBullet(key, m_pos, rotVec)
						);
						rot += 5;
					}
					rot = -90.f;
					break;
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					rot -= 5;
					for (size_t i = 0; i < 3; i++) {
						rotVec.x = cos(D3DXToRadian(rot));
						rotVec.y = sin(D3DXToRadian(rot));
						D3DXVec2Normalize(&rotVec, &rotVec);

						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
							new cPlayerBullet(key, m_pos, rotVec)
						);
						rot += 5;
					}
					rot = -90.f;
					break;
				case 9:
					rotVec.x = cos(D3DXToRadian(rot - 10));
					rotVec.y = sin(D3DXToRadian(rot - 10));
					D3DXVec2Normalize(&rotVec, &rotVec);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos, rotVec)
					);

					rotVec.x = cos(D3DXToRadian(rot - 2));
					rotVec.y = sin(D3DXToRadian(rot - 2));
					D3DXVec2Normalize(&rotVec, &rotVec);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos, rotVec)
					);

					rotVec.x = cos(D3DXToRadian(rot + 2));
					rotVec.y = sin(D3DXToRadian(rot + 2));
					D3DXVec2Normalize(&rotVec, &rotVec);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos, rotVec)
					);

					rotVec.x = cos(D3DXToRadian(rot + 10));
					rotVec.y = sin(D3DXToRadian(rot + 10));
					D3DXVec2Normalize(&rotVec, &rotVec);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos, rotVec)
					);
					break;
				default:
					break;
				}
			}
			else {
				switch (m_level) {
				case 1:
				case 2:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos)
					);
					break;
				case 3:
				case 4:
					rot -= 5;
					for (size_t i = 0; i < 2; i++) {
						rotVec.x = cos(D3DXToRadian(rot));
						rotVec.y = sin(D3DXToRadian(rot));
						D3DXVec2Normalize(&rotVec, &rotVec);

						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
							new cPlayerBullet(key, m_pos, rotVec)
						);
						rot += 10;
					}
					rot = -90.f;
					break;
				case 5:
				case 6:
				case 7:
					rot -= 10;
					for (size_t i = 0; i < 3; i++) {
						rotVec.x = cos(D3DXToRadian(rot));
						rotVec.y = sin(D3DXToRadian(rot));
						D3DXVec2Normalize(&rotVec, &rotVec);

						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
							new cPlayerBullet(key, m_pos, rotVec)
						);
						rot += 10;
					}
					rot = -90.f;
					break;
				case 8:
				case 9:
					rot -= 20;
					for (size_t i = 0; i < 5; i++) {
						rotVec.x = cos(D3DXToRadian(rot));
						rotVec.y = sin(D3DXToRadian(rot));
						D3DXVec2Normalize(&rotVec, &rotVec);

						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
							new cPlayerBullet(key, m_pos, rotVec)
						);
						rot += 10;
					}
					rot = -90.f;
					break;
				default:
					break;
				}
			}
		}
		else {
			if (isB == FALSE) {
				switch (m_level) {

				default:
					break;
				}
			}
			else {
				switch (m_level) {

				default:
					break;
				}
			}
		}

		if (m_nowBulletCnt > m_bulletCnt) m_isShot = m_nowBulletCnt = 0;
		else m_nowBulletCnt++;
	}

	if (isMarisa == FALSE) {
		if (isB == FALSE) {
			switch (m_level) {
			case 5:
				if (m_subBulletTimer->m_delay != 150)
					m_subBulletTimer->m_delay = 150;
				break;
			case 7:
				if (m_subBulletTimer->m_delay != 100)
					m_subBulletTimer->m_delay = 100;
				break;
			case 8:
				if (m_subBulletTimer->m_delay != 50)
					m_subBulletTimer->m_delay = 50;
				break;
			}
		}
		else {
			switch (m_level) {
			case 3:
				if (m_subBulletTimer->m_delay != 150)
					m_subBulletTimer->m_delay = 150;
				break;
			case 4:
				if (m_subBulletTimer->m_delay != 100)
					m_subBulletTimer->m_delay = 100;
				break;
			case 7:
				if (m_subBulletTimer->m_delay != 50)
					m_subBulletTimer->m_delay = 50;
				break;
			}
		}
	}
	else {
		if (isB == FALSE) {
			switch (m_level) {
			case 1:
				break;
			}
		}
		else {
			switch (m_level) {
			case 1:
				break;
			}
		}
	}
}

void cPlayer::SubFire()
{
	if (m_hasBall == TRUE && m_isSubShot == TRUE && m_subBulletTimer->Update()) {
		//���� �Ѿ� �߻�
		char key[256];
		if (isMarisa == FALSE)
			if (isB == FALSE) sprintf(key, "player_reimou_subShot0");
			else sprintf(key, "player_reimou_subShot1");
		else
			if (isB == FALSE) sprintf(key, "player_marisa_subShot0");
			else sprintf(key, "player_marisa_subShot1");

		VEC2 m_pos[2] = {
			//left ball
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetPos(),
			//right ball
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetPos()
		};

		VEC2 rotVec;
		int rot;

		if (isMarisa == FALSE) {
			if (isB == FALSE) {
				//ȣ�� �ֹķ�
				switch (m_level) {
				case 2:
				case 3:
				case 4:
				case 5:
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i], VEC2(0, -1), VEC2(1, 1), 0, TRUE)
						);
					break;
				case 6:
					for (size_t i = 0; i < 2; i++) {
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, VEC2(m_pos[i].x - 5, m_pos[i].y), VEC2(0, -1), VEC2(1, 1), 0, TRUE)
						);
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, VEC2(m_pos[i].x + 5, m_pos[i].y), VEC2(0, -1), VEC2(1, 1), 0, TRUE)
						);
					}
					break;
				case 7:
					rotVec.x = cos(D3DXToRadian(m_bRot[1][m_nowRot]));
					rotVec.y = sin(D3DXToRadian(m_bRot[1][m_nowRot]));
					D3DXVec2Normalize(&rotVec, &rotVec);

					for (size_t i = 0; i < 2; i++) {
						rotVec.x = -rotVec.x;
						rot = m_bRot[i][m_nowRot];
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i], rotVec, VEC2(1, 1), rot, TRUE)
						);
					}
					m_nowRot = !m_nowRot;
					break;
				case 8:
				case 9:
					rotVec.x = cos(D3DXToRadian(m_bRot[1][m_nowRot]));
					rotVec.y = sin(D3DXToRadian(m_bRot[1][m_nowRot]));
					D3DXVec2Normalize(&rotVec, &rotVec);

					for (size_t i = 0; i < 2; i++) {
						rotVec.x = -rotVec.x;
						rot = m_bRot[i][m_nowRot];
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i], rotVec, VEC2(1, 1), rot, TRUE)
						);
					}
					if (m_nowRot < 2) m_nowRot++;
					else m_nowRot = 0;

					break;
				default:
					break;
				}
			}
			else {
				//�ϵ� ��
				switch (m_level) {
				case 2:
				case 3:
				case 4:
				case 5:
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i])
						);
					break;
				case 6:
				case 7:
				case 8:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x - 15, m_pos[0].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x + 15, m_pos[0].y))
					);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x - 15, m_pos[1].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x + 15, m_pos[1].y))
					);
					break;
				case 9:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x - 20, m_pos[0].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, m_pos[0])
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x + 20, m_pos[0].y))
					);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x - 20, m_pos[1].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, m_pos[1])
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x + 20, m_pos[1].y))
					);
					break;
				default:
					break;
				}
			}
		}

		if (m_isShot == FALSE)
			m_isSubShot = FALSE;
	}
}

void cPlayer::Bomb()
{
	if (m_isBomb == FALSE && m_bomb > 0 && INPUT->KeyDown(DIK_X)) {
		//�� ���� �ʹ� �۰� ����� 2�� ����
		SOUND->Copy("bombSND");
		SOUND->Copy("bombSND");
		if (isMarisa == FALSE) {
			if (isB == FALSE) {
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, m_pos,
						VEC2(4, 4), VEC2(5, 5)
					)
				);

				auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
				for (auto iter : eBullet) {
					//�÷��̾� ������ �ִ� �Ѿ��� ��� ���ش�.
					if (CIRCLE(
							iter->GetPos(),
							m_pos,
							iter->GetImg()->m_info.Width * iter->GetSize().x,
							230
					)) {
						EFFECT->AddEffect(
							new cEffect("enemy_dead_EFFECT", 1, iter->GetPos(),
								VEC2(0.5f, 0.5f), VEC2(0.3f, 0.3f)
							)
						);
						iter->GetRefLive() = FALSE;
					}
				}
			}
			else SOUND->Copy("reimouBbombSND");
		}
		else {
			if (isB == FALSE) SOUND->Copy("marisaAbombSND");
			else SOUND->Copy("marisaBbombSND");
		}

		m_bomb--;
		m_isBomb = TRUE;
		m_isNotDead = TRUE;
		m_notDeadTime = timeGetTime();
		m_bombTime = timeGetTime();
	}

	else if (m_isBomb == TRUE) {
		INT nowTime = timeGetTime() - m_bombTime;

		if (nowTime < 1000) {
			Lerp(m_bombFace->m_pos.x, 50.f + 200, 0.05);
			Lerp(m_bombName->m_a, 255.f, 0.05);
			m_bombName->SetNowRGB();
		}

		else if (nowTime > 1500) {
			Lerp(m_bombFace->m_size, VEC2(2, 2), 0.03);
			Lerp(m_bombFace->m_a, 0.f, 0.05);
			m_bombFace->SetNowRGB();
			Lerp(m_bombName->m_a, 0.f, 0.05);
			m_bombName->SetNowRGB();
		}

		if ((int)m_bombFace->m_a == 0 && (int)m_bombName->m_a == 0) {
			m_bombFace->m_pos = VEC2(-200, 50 + INGAMEY - 300);
			m_bombFace->m_size = VEC2(1, 1);
			m_bombFace->m_a = 200.f;
			m_bombFace->SetNowRGB();

			m_isBomb = FALSE;
		}
	}
}

void cPlayer::Move()
{
	//shift������ �ӵ� 50% ��
	if (INPUT->KeyPress(DIK_LSHIFT)) {
		m_speed = 350.f * 0.5f;
		if (m_hasBall == TRUE) {
			auto& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			auto& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 15, m_pos.y - 50), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 10, m_pos.y - 50), 0.1);
		}
	} 
	else {
		if (m_speed != 350.f) m_speed = 350.f;
		if (m_hasBall == TRUE) {
			auto& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			auto& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 50, m_pos.y), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 45, m_pos.y), 0.1);
		}
	}

	if (INPUT->KeyPress(DIK_LEFT) && INPUT->KeyPress(DIK_RIGHT)) {
		m_ani->m_nowFrame = 0;
		m_nowPlayerStatus = pIDLE;
	}

	else if (INPUT->KeyPress(DIK_LEFT) || INPUT->KeyPress(DIK_RIGHT)) {
		if (INPUT->KeyDown(DIK_LEFT) || INPUT->KeyDown(DIK_RIGHT))
			//�¿�Ű�� ���ʷ� ���� ��� �ִϸ��̼��� �����ؾ� �ϹǷ�
			//���� �������� �ʱ�ȭ
			m_ani->m_nowFrame = 0;
		if (INPUT->KeyPress(DIK_LEFT)) {
			//�������� ���� �ִϸ��̼����� ���������� ��
			m_nowPlayerStatus = pLEFT;
			if (m_pos.x - 10 > 50) m_pos.x -= m_speed * D_TIME;
			else m_pos.x = 50 + 10;
		}
		if (INPUT->KeyPress(DIK_RIGHT)) {
			//���������� ���� �ִϸ��̼����� ���������� ��
			m_nowPlayerStatus = pRIGHT;
			if (m_pos.x + 10 < 50 + INGAMEX) m_pos.x += m_speed * D_TIME;
			else m_pos.x = 50 + INGAMEX - 10;
		}
	}

	if (INPUT->KeyPress(DIK_UP)) {
		if (m_pos.y - 10 > 50) m_pos.y -= m_speed * D_TIME;
		else m_pos.y = 50 + 10;
	}
	if (INPUT->KeyPress(DIK_DOWN)) {
		if (m_pos.y + 10 < 50 + INGAMEY) m_pos.y += m_speed * D_TIME;
		else m_pos.y = 50 + INGAMEY - 10;
	}
}

