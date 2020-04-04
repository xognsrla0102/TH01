#include "DXUT.h"
#include "cBalls.h"
#include "cBall.h"
#include "cPlayerBullet.h"
#include "cReimouA_Bullet.h"
#include "cMarisaA_Bullet.h"
#include "cBallBullet.h"
#include "cEnemyBullet.h"
#include "cBulletAdmin.h"
#include "cItem.h"
#include "cItemAdmin.h"
#include "cEnemy.h"
#include "cEnemyAdmin.h"
#include "cTimer.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{	
	m_spellB_RED[0] = new cImage;
	m_spellB_RED[1] = new cImage;
	m_spellB_BLUE[0] = new cImage;
	m_spellB_BLUE[1] = new cImage;

	m_spellB_RED[0]->m_img = IMAGE->FindImage("spell_reimouB_RED");
	m_spellB_RED[1]->m_img = IMAGE->FindImage("spell_reimouB_RED");
	m_spellB_RED[1]->m_rot = 180;

	m_spellB_BLUE[0]->m_img = IMAGE->FindImage("spell_reimouB_BLUE");
	m_spellB_BLUE[1]->m_img = IMAGE->FindImage("spell_reimouB_BLUE");
	m_spellB_BLUE[1]->m_rot = 180;

	m_spellB_Razer = new cImage;
	m_spellB_Razer->m_img = IMAGE->FindImage("spell_marisaB");
}

cPlayer::~cPlayer()
{
	for (auto iter : m_spellB_RED)
		SAFE_DELETE(iter);
	for (auto iter : m_spellB_BLUE)
		SAFE_DELETE(iter);
	SAFE_DELETE(m_spellB_Razer);

	Release();
}

void cPlayer::Init()
{
	m_spellB_RED[0]->m_a = m_spellB_RED[1]->m_a = 0.f;
	m_spellB_BLUE[0]->m_a = m_spellB_BLUE[1]->m_a = 0.f;;
	m_spellB_RED[0]->SetNowRGB();
	m_spellB_RED[1]->SetNowRGB();
	m_spellB_BLUE[0]->SetNowRGB();
	m_spellB_BLUE[1]->SetNowRGB();

	m_spellB_Razer->m_a = 0.f;
	m_spellB_Razer->SetNowRGB();

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

	m_shotAtk = 1.f;
	m_subShotAtk = 1.f;

	m_hasBall = FALSE;
	m_isHit = FALSE;
	m_isNotDead = FALSE;
	m_isShot = FALSE;
	m_isSubShot = FALSE;
	m_isBomb = FALSE;
	m_isBombShot = FALSE;
	m_isLevelUp = FALSE;
	m_isFullPower = FALSE;
	m_isExtend = FALSE;

	m_bulletTimer = new cTimer(80);
	m_subBulletTimer = new cTimer(450);

	m_reimouA_BulletTime = timeGetTime();
	m_bombTime = timeGetTime();

	m_ani = new cAnimation(100, 4);
	//레이무 IDLE일 땐 4장, LEFT, RIGHT는 7장
	//마리사 IDLE일 땐 4장, LEFT, RIGHT는 8장

	if (isMarisa == FALSE) {
		if (isB == FALSE) m_subBulletTimer->m_delay = 450;
		else m_subBulletTimer->m_delay = 200;
	}
	else {
		if (isB == FALSE) m_subBulletTimer->m_delay = 600;
		else m_subBulletTimer->m_delay = 2000;
	}
}

void cPlayer::Update()
{
	//천만점 되면 익스텐드
	if (m_isExtend == FALSE && m_score >= 10000000) {
		if (m_life < 8) {
			SOUND->Copy("extendSND");
			SOUND->Copy("extendSND");
			m_life++;
			m_isExtend = TRUE;
		}
	}

	if (m_hasBall == FALSE && m_level > 1) {
		for (size_t i = 0; i < 2; i++) {
			//오른쪽 볼 만들고 왼쪽 볼 만듦
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls().push_back(
				new cBall(OBJFIND(PLAYER)->GetRefPos(), i)
			);
		}
		m_hasBall = TRUE;
	}
	else if (m_hasBall == TRUE && m_level < 2) {
		for (auto iter : ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls())
			SAFE_DELETE(iter);
		((cBalls*)OBJFIND(BALLS))->GetPlayerBalls().clear();

		m_hasBall = FALSE;
	}

	INT wasLevel = m_level;

	//플레이어 파워 올리는 치트
	if (INPUT->KeyDown(DIK_A)) {
		if (m_power < 128) m_power += 8;
		if (m_power > 128) m_power = 128;
	}

	if (m_power == 128 && m_wasPower != 128)
		m_isFullPower = TRUE;

	if (m_power >= 128)		{ if(m_level != 9) m_level = 9; }
	else if (m_power >= 96) { if(m_level != 8) m_level = 8; }
	else if (m_power >= 80) { if(m_level != 7) m_level = 7; }
	else if (m_power >= 64) { if(m_level != 6) m_level = 6; }
	else if (m_power >= 48) { if(m_level != 5) m_level = 5; }
	else if (m_power >= 32) { if(m_level != 4) m_level = 4; }
	else if (m_power >= 16) { if(m_level != 3) m_level = 3; }
	else if (m_power >= 8)  { if(m_level != 2) m_level = 2; }
	else if (m_level != 1)  {				   m_level = 1; }

	if (wasLevel != m_level && wasLevel < m_level)
		m_isLevelUp = TRUE;

	if (m_isLevelUp == TRUE) {
		SOUND->Copy("powerupSND");
		EFFECT->AddEffect(
			new cEffect("powerUp_EFFECT", 1, VEC2(m_pos.x, m_pos.y - 20), VEC2(0, -1))
		);
		m_isLevelUp = FALSE;
	}

	m_ani->Update();

	m_img = IMAGE->FindImage(
		m_pStatus[isMarisa][m_nowPlayerStatus],
		m_ani->m_nowFrame
	);

	if (m_isHit == TRUE) {
		Hit();
		return;
	}
	else if (m_isNotDead == TRUE) {
		NotDead();
	}

	Move();
	if(m_isHit == FALSE && m_isNotDead == FALSE)
		Graze();

	if (m_isShot == FALSE && INPUT->KeyPress(DIK_Z))
		m_isShot = m_isSubShot = TRUE;

	Fire();
	SubFire();
	Bomb();

	if (m_isBombShot == TRUE) {
		if (isMarisa == FALSE) {
			if (isB == FALSE) ReimouA();
			else ReimouB();
		}
		else {
			if (isB == FALSE) MarisaA();
			else MarisaB();
		}
	}
}

void cPlayer::Render()
{
	for (size_t i = 0; i < 2; i++) {
		IMAGE->Render(m_spellB_RED[i]->m_img, m_spellB_RED[i]->m_pos, 1.f, m_spellB_RED[i]->m_rot, TRUE, m_spellB_RED[i]->m_color);
		IMAGE->Render(m_spellB_BLUE[i]->m_img, m_spellB_BLUE[i]->m_pos, 1.f, m_spellB_BLUE[i]->m_rot, TRUE, m_spellB_BLUE[i]->m_color);
	}
	IMAGE->Render(m_spellB_Razer->m_img, m_spellB_Razer->m_pos, 1.f, 0.f, TRUE, m_spellB_Razer->m_color);
	IMAGE->Render(m_img, m_pos, m_size, m_rot, TRUE, D3DCOLOR_ARGB((INT)m_pAlpha, 255, 255, 255));
}

void cPlayer::Release()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_bulletTimer);
	SAFE_DELETE(m_subBulletTimer);
}

void cPlayer::Graze()
{
	auto& enemyBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
	for (size_t i = 0; i < enemyBullet.size(); i++) {
		cEnemyBullet* eBullet = ((cEnemyBullet*)enemyBullet[i]);
		if (eBullet->m_isGraze == FALSE) {
			if (DistPoint(m_pos, eBullet->GetPos()) <= 50.f) {
				SOUND->Copy("grazeSND");
				SOUND->Copy("grazeSND");
				m_graze++;
				m_score += 500;

				eBullet->m_isGraze = TRUE;

				int theta = rand() % 360;
				VEC2 dir(cos(D3DXToRadian(theta)), sin(D3DXToRadian(theta)));
				D3DXVec2Normalize(&dir, &dir);

				EFFECT->AddEffect(
					new cEffect("graze_EFFECT", 1, m_pos, dir, VEC2(-0.5f, -0.5f), VEC2(1, 1), 800.f)
				);
			}
		}
	}
}

void cPlayer::Hit()
{
	Lerp(m_pAlpha, 0.f, 0.1);
	Lerp(m_size, VEC2(0.5f, 2.f), 0.1);

	//m_isHit이 트루일 동안은 계속 지워줘야함
	auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
	for (auto iter : eBullet) {
		EFFECT->AddEffect(
			new cEffect("enemy_dead_EFFECT", 1, iter->GetPos(), VEC2(0, 0),
				VEC2(0.2f, 0.2f), VEC2(0.3f, 0.3f)
			)
		);
		iter->GetRefLive() = FALSE;
	}

	if ((INT)m_pAlpha > 30 && KEYDOWN(DIK_X)) {
		Bomb();
		m_life++;
		m_isHit = FALSE;
		m_size = VEC2(1.f, 1.f);
		m_pAlpha = 255.f;
	}
	else if ((INT)m_pAlpha == 0) {
		m_ani->m_nowFrame = 0;
		m_ani->m_endFrame = 4;
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

		if (m_life > 0) {
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
		}
		else {
			key = "item_fullPower";
			for (size_t i = 0; i < 5; i++) {
				randNum = 50 + rand() % 50;
				randNum *= rand() % 2 ? 1 : -1;
				resultX = m_pos.x + randNum;

				if (resultX < 50) resultX = 50 + 10;
				else if (resultX > 50 + INGAMEX) resultX = 50 + INGAMEX - 10;

				((cItemAdmin*)OBJFIND(ITEMS))->m_items.push_back(
					new cItem(key, VEC2(m_pos.x, m_pos.y - 10), VEC2(resultX, m_pos.y - (200 + rand() % 200)))
				);
			}
			m_life = playerLife;
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
		//총알 발사
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
				}
			}
		}
		else {
			if (isB == FALSE) {
				switch (m_level) {
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos)
					);
					break;
				case 6:
				case 7:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, VEC2(m_pos.x - 10, m_pos.y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, VEC2(m_pos.x + 10, m_pos.y))
					);
					break;
				case 8:
				case 9:
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
				}
			}
			else {
				switch (m_level) {
				case 1:
				case 2:
				case 3:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
						new cPlayerBullet(key, m_pos)
					);
					break;
				case 4:
				case 5:
				case 6:
					rot -= 2;
					for (size_t i = 0; i < 2; i++) {
						rotVec.x = cos(D3DXToRadian(rot));
						rotVec.y = sin(D3DXToRadian(rot));
						D3DXVec2Normalize(&rotVec, &rotVec);

						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
							new cPlayerBullet(key, m_pos, rotVec)
						);
						rot += 4;
					}
					rot = -90.f;
					break;
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
					rot -= 10;
					for (size_t i = 0; i < 5; i++) {
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
			case 6:
				if (m_subBulletTimer->m_delay != 150)
					m_subBulletTimer->m_delay = 150;
				break;
			case 7:
				if (m_subBulletTimer->m_delay != 100)
					m_subBulletTimer->m_delay = 100;
				break;
			case 8:
			case 9:
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
			case 5:
			case 6:
				if (m_subBulletTimer->m_delay != 100)
					m_subBulletTimer->m_delay = 100;
				break;
			case 7:
			case 8:
			case 9:
				if (m_subBulletTimer->m_delay != 50)
					m_subBulletTimer->m_delay = 50;
				break;
			}
		}
	}
	else {
		if (isB == FALSE) {
			switch (m_level) {
			case 3:
				if (m_subBulletTimer->m_delay != 550)
					m_subBulletTimer->m_delay = 550;
			case 4:
				if (m_subBulletTimer->m_delay != 400)
					m_subBulletTimer->m_delay = 400;
				break;
			case 5:
				if (m_subBulletTimer->m_delay != 300)
					m_subBulletTimer->m_delay = 300;
				break;
			case 6:
				if (m_subBulletTimer->m_delay != 200)
					m_subBulletTimer->m_delay = 200;
				break;
			case 7:
			case 8:
			case 9:
				if (m_subBulletTimer->m_delay != 100)
					m_subBulletTimer->m_delay = 100;
				break;
			}
		}
		else {
			switch (m_level) {
			case 3:
				if (m_subBulletTimer->m_delay != 2000)
					m_subBulletTimer->m_delay = 2000;
				break;
			case 4:
			case 5:
				if (m_subBulletTimer->m_delay != 3000)
					m_subBulletTimer->m_delay = 3000;
				break;
			case 6:
			case 7:
			case 8:
				if (m_subBulletTimer->m_delay != 4000)
					m_subBulletTimer->m_delay = 4000;
				break;
			case 9:
				if (m_subBulletTimer->m_delay != 5000)
					m_subBulletTimer->m_delay = 5000;
				break;
			}
		}
	}
}

void cPlayer::SubFire()
{
	if (m_isShot == FALSE)
		m_isSubShot = FALSE;

	if (m_hasBall == TRUE && m_isSubShot == TRUE && m_subBulletTimer->Update()) {
		//보조 총알 발사
		string key;
		if (isMarisa == FALSE) {
			if (isB == FALSE) key = "player_reimou_subShot0";
			else key = "player_reimou_subShot1";
		}
		else {
			if (isB == FALSE) key = "player_marisa_subShot0";
			else key = "player_marisa_subShot1_%d";
		}
		
		VEC2 m_pos[2] = {
			//left ball
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetPos(),
			//right ball
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetPos()
		};

		VEC2 rotVec;
		INT rot;

		if (isMarisa == FALSE) {
			if (isB == FALSE) {
				//호밍 애뮬랫
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
				//니들 샷
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
		else {
			if (isB == FALSE) {
				//미사일
				switch (m_level) {
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i])
						);
					break;
				case 9:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x - 10, m_pos[0].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x + 10, m_pos[0].y))
					);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x - 10, m_pos[1].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x + 10, m_pos[1].y))
					);
					break;
				}
			}
			else {
				//레이저
				auto& ballBullet = ((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet();
				switch (m_level) {
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
					for (size_t i = 0; i < 2; i++) {
						ballBullet.push_back(
							new cBallBullet(key, VEC2(m_pos[i].x, m_pos[i].y - 310))
						);
						//레이저 지속시간은 입력 딜레이보다 1초 짧게(페이드인,아웃되는 시간은 1초 미만이므로)
						((cBallBullet*)(ballBullet[ballBullet.size() - 1]))->m_atkDelay
							= m_subBulletTimer->m_delay - 1000;
						((cBallBullet*)(ballBullet[ballBullet.size() - 1]))->m_index = i;
					}
					break;
				}
			}
		}
	}
}

void cPlayer::Bomb()
{
	if (m_isBombShot == FALSE && m_isBomb == FALSE && m_bomb > 0 && INPUT->KeyDown(DIK_X)) {
		//붐 사운드 너무 작게 들려서 2개 걸음
		SOUND->Copy("bombSND");
		SOUND->Copy("bombSND");
		if (isMarisa == FALSE) {
			if (isB == FALSE) {
				EFFECT->AddEffect(
					new cEffect("enemy_dead_EFFECT", 1, m_pos, VEC2(0, 0),
						VEC2(3, 3), VEC2(5, 5), 500.f
					)
				);
				auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
				for (auto iter : eBullet) {
					//플레이어 주위에 있는 총알을 모두 없앤다.
					if (CIRCLE(
							iter->GetPos(),
							m_pos,
							iter->GetImg()->m_info.Width * iter->GetSize().x,
							230
					)) {
						EFFECT->AddEffect(
							new cEffect("enemy_dead_EFFECT", 1, iter->GetPos(), VEC2(0, 0),
								VEC2(0.2f, 0.2f), VEC2(0.3f, 0.3f)
							)
						);
						((cItemAdmin*)OBJFIND(ITEMS))->m_items.push_back(
							new cItem("item_tan", iter->GetPos(), iter->GetPos())
						);
						iter->GetRefLive() = FALSE;
					}
				}
				m_reimouA_BulletTime = timeGetTime();
			}
			else {
				SOUND->Copy("reimouBbombSND");
				SOUND->Copy("reimouBbombSND");

				CAMERA->m_delay = 30;
				CAMERA->m_velocity = 1;
				CAMERA->m_isShake = TRUE;

				m_spellB_RED[0]->m_pos = VEC2(m_pos.x, 50 + INGAMEY / 2);
				m_spellB_RED[1]->m_pos = VEC2(m_pos.x, 50 + INGAMEY / 2);
				m_spellB_BLUE[0]->m_pos = VEC2(50 + INGAMEX / 2, m_pos.y);
				m_spellB_BLUE[1]->m_pos = VEC2(50 + INGAMEX / 2, m_pos.y);
			}
		}
		else {
			if (isB == FALSE) {
				SOUND->Copy("marisaAbombSND");

				VEC2 pos[3] = {
					VEC2(m_pos.x, m_pos.y + 30),
					VEC2(m_pos.x - 30, m_pos.y ),
					VEC2(m_pos.x, m_pos.y)
				};
				BOOL rotLeft[8] = { TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE };
				VEC4 color[8] = {
					VEC4(100, 200, 200, 255),
					VEC4(100, 200, 255, 200),
					VEC4(100, 200, 200, 255),
					VEC4(100, 200, 255, 200),
					VEC4(100, 255, 200, 200),
					VEC4(100, 200, 200, 255),
					VEC4(100, 200, 255, 200),
					VEC4(100, 255, 200, 200)
				};

				for (INT i = 0, rot = 0; i < 8; i++, rot += 45) {
					VEC2 dir;
					dir.x = cos(D3DXToRadian(rot - 90));
					dir.y = sin(D3DXToRadian(rot - 90));
					D3DXVec2Normalize(&dir, &dir);

					for (size_t j = 0; j < 3; j++) {
						((cBulletAdmin*)OBJFIND(BULLETS))->GetSpellBullet().push_back(
							new cMarisaA_Bullet(
								pos[j], dir, VEC2((j + 1) / 3.f, (j + 1) / 3.f), rotLeft[i], color[i]
							)
						);
					}
				}
				m_marisaA_BulletTime = timeGetTime();
			}
			else {
				SOUND->Copy("marisaBbombSND");
				m_marisaB_RazerTime = timeGetTime();
			}
		}
		m_bomb--;
		m_isBomb = TRUE;
		m_isBombShot = TRUE;
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

		if ((INT)m_bombFace->m_a == 0 && (INT)m_bombName->m_a == 0) {
			m_bombFace->m_pos = VEC2(-200, 50 + INGAMEY - 300);
			m_bombFace->m_size = VEC2(1, 1);
			m_bombFace->m_a = 200.f;
			m_bombFace->SetNowRGB();

			m_isBomb = FALSE;
		}
	}
}

void cPlayer::ReimouA()
{
	static INT m_bulletCnt = 0;
	static time_t firstShot = timeGetTime();

	if (timeGetTime() - firstShot < 1000) return;

	INT nowTime = timeGetTime() - m_reimouA_BulletTime;
	if (nowTime > 250) {
		SOUND->Copy("reimouAbombSND");
		SOUND->Copy("reimouAbombSND");
		((cBulletAdmin*)OBJFIND(BULLETS))->GetSpellBullet().push_back(
			new cReimouA_Bullet(VEC2(-50 + m_pos.x + rand() % 8 * 10, m_pos.y))
		);
		m_bulletCnt++;
		m_reimouA_BulletTime = timeGetTime();
	}

	if (m_bulletCnt > 7) {
		m_isBombShot = FALSE;
		m_bulletCnt = 0;
	}
}

void cPlayer::ReimouB()
{
	auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
	auto& eOne = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
	auto& eFairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();

	RECT spell[2][2];

	for (size_t i = 0; i < 2; i++) {
		spell[0][i].left = m_spellB_RED[i]->m_pos.x - m_spellB_RED[i]->m_img->m_info.Width / 2;
		spell[0][i].top = m_spellB_RED[i]->m_pos.y - m_spellB_RED[i]->m_img->m_info.Height / 2;
		spell[0][i].right = m_spellB_RED[i]->m_pos.x + m_spellB_RED[i]->m_img->m_info.Width / 2;
		spell[0][i].bottom = m_spellB_RED[i]->m_pos.y + m_spellB_RED[i]->m_img->m_info.Height / 2;
	}
	for (size_t i = 0; i < 2; i++) {
		spell[1][i].left = m_spellB_BLUE[i]->m_pos.x - m_spellB_BLUE[i]->m_img->m_info.Width / 2;
		spell[1][i].top = m_spellB_BLUE[i]->m_pos.y - m_spellB_BLUE[i]->m_img->m_info.Height / 2;
		spell[1][i].right = m_spellB_BLUE[i]->m_pos.x + m_spellB_BLUE[i]->m_img->m_info.Width / 2;
		spell[1][i].bottom = m_spellB_BLUE[i]->m_pos.y + m_spellB_BLUE[i]->m_img->m_info.Height / 2;
	}

	//스펠과 충돌하는 모든 적 총알들은 탄 소거 아이템이 된다.
	for (auto iter : eBullet) {
		RECT bulletRect{
			iter->GetPos().x - iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y - iter->GetImg()->m_info.Height / 2,
			iter->GetPos().x + iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y + iter->GetImg()->m_info.Height / 2
		};

		if (AABB(spell[0][0], bulletRect) ||
			AABB(spell[0][1], bulletRect) ||
			AABB(spell[1][0], bulletRect) ||
			AABB(spell[1][1], bulletRect))
		{
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

	for (auto iter : eOne) {
		RECT eRect = {
			iter->GetPos().x - iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y - iter->GetImg()->m_info.Height / 2,
			iter->GetPos().x + iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y + iter->GetImg()->m_info.Height / 2
		};

		if (AABB(spell[0][0], eRect) ||
			AABB(spell[0][1], eRect) ||
			AABB(spell[1][0], eRect) ||
			AABB(spell[1][1], eRect))
		{
			SOUND->Copy("hitSND");
			m_score += 10;
			iter->m_hp -= m_shotAtk / 2;
			if (iter->m_hp < 1) iter->GetRefLive() = FALSE;
		}
	}

	for (auto iter : eFairy) {
		RECT eRect = {
			iter->GetPos().x - iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y - iter->GetImg()->m_info.Height / 2,
			iter->GetPos().x + iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y + iter->GetImg()->m_info.Height / 2
		};

		if (AABB(spell[0][0], eRect) ||
			AABB(spell[0][1], eRect) ||
			AABB(spell[1][0], eRect) ||
			AABB(spell[1][1], eRect))
		{
			SOUND->Copy("hitSND");
			m_score += 10;
			iter->m_hp -= m_shotAtk / 2;
			if (iter->m_hp < 1) iter->GetRefLive() = FALSE;
		}
	}

	if ((INT)m_spellB_RED[0]->m_a != 200) {
		Lerp(m_spellB_RED[0]->m_a, 201.f, 0.05);
		Lerp(m_spellB_RED[1]->m_a, 201.f, 0.05);
		Lerp(m_spellB_BLUE[0]->m_a, 201.f, 0.05);
		Lerp(m_spellB_BLUE[1]->m_a, 201.f, 0.05);
		m_spellB_RED[0]->SetNowRGB();
		m_spellB_RED[1]->SetNowRGB();
		m_spellB_BLUE[0]->SetNowRGB();
		m_spellB_BLUE[1]->SetNowRGB();

		//계속 최신시간으로 갱신시켜줌
		m_reimouB_SpreadTime = timeGetTime();
	}
	else {
		if (timeGetTime() - m_reimouB_SpreadTime < 2000) {
			Lerp(m_spellB_RED[0]->m_pos.x, 50.f, 0.05);
			Lerp(m_spellB_RED[1]->m_pos.x, 50.f + INGAMEX, 0.05);
			Lerp(m_spellB_BLUE[0]->m_pos.y, 50.f, 0.05);
			Lerp(m_spellB_BLUE[1]->m_pos.y, 50.f + INGAMEY, 0.05);
		}
		else {
			m_isBombShot = FALSE;

			m_spellB_RED[0]->m_a = m_spellB_RED[1]->m_a
			= m_spellB_BLUE[0]->m_a = m_spellB_BLUE[1]->m_a = 0.f;
			m_spellB_RED[0]->SetNowRGB();
			m_spellB_RED[1]->SetNowRGB();
			m_spellB_BLUE[0]->SetNowRGB();
			m_spellB_BLUE[1]->SetNowRGB();
		}
	}
}

void cPlayer::MarisaA()
{
	if (timeGetTime() - m_marisaA_BulletTime > 3000)
		m_isBombShot = FALSE;
}

void cPlayer::MarisaB()
{
	auto& eBullet = ((cBulletAdmin*)OBJFIND(BULLETS))->GetEnemyBullet();
	auto& eOne = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
	auto& eFairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();

	RECT razerRect = {
		m_spellB_Razer->m_pos.x - m_spellB_Razer->m_img->m_info.Width / 2,
		m_spellB_Razer->m_pos.y - m_spellB_Razer->m_img->m_info.Height / 2,
		m_spellB_Razer->m_pos.x + m_spellB_Razer->m_img->m_info.Width / 2,
		m_spellB_Razer->m_pos.y + m_spellB_Razer->m_img->m_info.Height / 2
	};

	for (auto iter : eBullet) {
		RECT bulletRect{
			iter->GetPos().x - iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y - iter->GetImg()->m_info.Height / 2,
			iter->GetPos().x + iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y + iter->GetImg()->m_info.Height / 2
		};

		if (AABB(razerRect, bulletRect)) {
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

	for (auto iter : eOne) {
		RECT eRect = {
			iter->GetPos().x - iter->GetImg()->m_info.Width /2,
			iter->GetPos().y - iter->GetImg()->m_info.Height / 2,
			iter->GetPos().x + iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y + iter->GetImg()->m_info.Height / 2
		};

		if (AABB(razerRect, eRect)) {
			SOUND->Copy("hitSND");
			m_score += 10;
			iter->m_hp -= m_shotAtk;
			if (iter->m_hp < 1) iter->GetRefLive() = FALSE;
		}
	}

	for (auto iter : eFairy) {
		RECT eRect = {
			iter->GetPos().x - iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y - iter->GetImg()->m_info.Height / 2,
			iter->GetPos().x + iter->GetImg()->m_info.Width / 2,
			iter->GetPos().y + iter->GetImg()->m_info.Height / 2
		};

		if (AABB(razerRect, eRect)) {
			SOUND->Copy("hitSND");
			m_score += 10;
			iter->m_hp -= m_shotAtk;
			if (iter->m_hp < 1) iter->GetRefLive() = FALSE;
		}
	}

	INT nowTime = timeGetTime() - m_marisaB_RazerTime;

	m_spellB_Razer->m_pos = VEC2(
		m_pos.x,
		m_pos.y
		- m_spellB_Razer->m_img->m_info.Height / 2
		- m_img->m_info.Height / 2
	);

	if (nowTime < 1000) {
		Lerp(m_spellB_Razer->m_a, 200.f, 0.05);
		m_spellB_Razer->SetNowRGB();
	}
	else if (1500 < nowTime && nowTime < 1520) {
		m_spellB_Razer->m_a = 200.f;
		m_spellB_Razer->SetNowRGB();

		CAMERA->m_delay = 30;
		CAMERA->m_velocity = 1;
		CAMERA->m_isShake = TRUE;
	}
	else if (2500 < nowTime && (INT)m_spellB_Razer->m_a != 0.f) {
		Lerp(m_spellB_Razer->m_a, 0.f, 0.1);
		m_spellB_Razer->SetNowRGB();
	}
	else if ((INT)m_spellB_Razer->m_a == 0.f) {
		m_isBombShot = FALSE;
	}
}

void cPlayer::Move()
{
	//shift누르면 속도 50% 됨
	if (INPUT->KeyPress(DIK_LSHIFT)) {
		m_speed = 350.f * 0.5f;
		if (m_hasBall == TRUE) {
			VEC2& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			VEC2& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 15, m_pos.y - 50), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 10, m_pos.y - 50), 0.1);
		}
	} 
	else if (isMarisa == TRUE && isB == TRUE && m_isBombShot == TRUE) {
		m_speed = 350.f * 0.5f;
		if (m_hasBall == TRUE) {
			VEC2& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			VEC2& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 50, m_pos.y), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 45, m_pos.y), 0.1);
		}
	}
	else {
		if (m_speed != 350.f) m_speed = 350.f;
		if (m_hasBall == TRUE) {
			VEC2& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			VEC2& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 50, m_pos.y), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 45, m_pos.y), 0.1);
		}
	}

	if (INPUT->KeyPress(DIK_LEFT) && INPUT->KeyPress(DIK_RIGHT)) {
		if (m_nowPlayerStatus != pIDLE) {
			m_ani->m_nowFrame = 0;
			m_ani->m_endFrame = 4;
			m_nowPlayerStatus = pIDLE;
		}
	}
	else if (INPUT->KeyPress(DIK_LEFT) || INPUT->KeyPress(DIK_RIGHT)) {
		//좌우키가 최초로 눌린 경우 애니메이션을 변경해야 하므로
		//현재 프레임을 초기화
		if (m_nowPlayerStatus == pIDLE) {
			m_ani->m_nowFrame = 0;
			if (isMarisa == FALSE) m_ani->m_endFrame = 7;
			else m_ani->m_endFrame = 8;
		}
		if (INPUT->KeyPress(DIK_LEFT)) {
			//왼쪽으로 가는 애니메이션으로 변경시켜줘야 함
			if (m_nowPlayerStatus != pLEFT) m_nowPlayerStatus = pLEFT;
			if (m_pos.x - 10 > 50) m_pos.x -= m_speed * D_TIME;
			else m_pos.x = 50 + 10;
		}
		else {
			//오른쪽으로 가는 애니메이션으로 변경시켜줘야 함
			if (m_nowPlayerStatus != pRIGHT) m_nowPlayerStatus = pRIGHT;
			if (m_pos.x + 10 < 50 + INGAMEX) m_pos.x += m_speed * D_TIME;
			else m_pos.x = 50 + INGAMEX - 10;
		}
	}
	else if(m_nowPlayerStatus != pIDLE) {
		m_ani->m_nowFrame = 0;
		m_ani->m_endFrame = 4;
		m_nowPlayerStatus = pIDLE;
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

