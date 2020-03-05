#include "DXUT.h"
#include "cBalls.h"
#include "cBall.h"
#include "cPlayerBullet.h"
#include "cBallBullet.h"
#include "cBulletAdmin.h"
#include "cTimer.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_pos = VEC2(200, WINSIZEY / 2);
	m_speed = 350.f;
}

cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	m_pos = VEC2(200, WINSIZEY / 2);
	m_nowPlayerStatus = pIDLE;
	m_nowBulletCnt = 0;
	m_bulletCnt = 5;
	m_nowSubBulletCnt = 0;

	m_life = playerLife;
	m_bomb = playerBomb;

	m_level = 1;
	m_power = 0;

	m_nowRot = 0;

	m_score = 0.f;

	m_hasBall = false;
	m_isHit = false;
	m_isShot = false;
	m_isSubShot = false;

	m_bulletTimer = new cTimer(80);
	m_subBulletTimer = new cTimer(100);
	m_ani = new cAnimation(100, 4);

	if (isMarisa == false)
		if (isB == false) m_subBulletTimer->m_delay = 450;
		else m_subBulletTimer->m_delay = 200;
	else
		if (isB == false) m_subBulletTimer->m_delay = 200;
		else m_subBulletTimer->m_delay = 200;
}

void cPlayer::Update()
{
	if (INPUT->KeyDown(DIK_A))
		if (m_level < 9) m_level++;

	if (m_hasBall == false && m_level > 1) {
		for (size_t i = 0; i < 2; i++) {
			//오른쪽 볼 만들고 왼쪽 볼 만듦
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls().push_back(
				new cBall(OBJFIND(PLAYER)->GetRefPos(), i)
			);
		}
		m_hasBall = true;
	}

	m_ani->Update();

	m_img = IMAGE->FindImage(m_pStatus[isMarisa][m_nowPlayerStatus], m_ani->m_nowFrame);

	if(m_nowPlayerStatus != pIDLE) m_nowPlayerStatus = pIDLE;

	Move();

	if (m_isShot == false && INPUT->KeyPress(DIK_Z))
		m_isShot = m_isSubShot = true;

	Fire();
	SubFire();
	Bomb();
}

void cPlayer::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cPlayer::Release()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_bulletTimer);
	SAFE_DELETE(m_subBulletTimer);
}

void cPlayer::Fire()
{
	if (m_isShot == true && m_bulletTimer->Update()) {
		//총알 발사
		SOUND->Copy("shotSND");
		char key[256];
		if (isMarisa == false) sprintf(key, "player_reimou_mainShot");
		else sprintf(key, "player_marisa_mainShot");

		VEC2 rotVec;
		float rot = -90.f;
		
		if (isMarisa == false) {
			if (isB == false) {
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
			if (isB == false) {
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

	if (isMarisa == false) {
		if (isB == false) {
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
		if (isB == false) {
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
	if (m_hasBall == true && m_isSubShot == true && m_subBulletTimer->Update()) {
		//보조 총알 발사
		char key[256];
		if (isMarisa == false)
			if (isB == false) sprintf(key, "player_reimou_subShot0");
			else sprintf(key, "player_reimou_subShot1");
		else
			if (isB == false) sprintf(key, "player_marisa_subShot0");
			else sprintf(key, "player_marisa_subShot1");

		VEC2 m_pos[2] = {
			//left ball
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetPos(),
			//right ball
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetPos()
		};

		VEC2 rotVec;
		int rot;

		if (isMarisa == false) {
			if (isB == false) {
				//호밍 애뮬랫
				switch (m_level) {
				case 2:
				case 3:
				case 4:
				case 5:
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i], VEC2(0, -1), VEC2(1, 1), 0, true)
						);
					break;
				case 6:
					for (size_t i = 0; i < 2; i++) {
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, VEC2(m_pos[i].x - 5, m_pos[i].y), VEC2(0, -1), VEC2(1, 1), 0, true)
						);
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, VEC2(m_pos[i].x + 5, m_pos[i].y), VEC2(0, -1), VEC2(1, 1), 0, true)
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
							new cBallBullet(key, m_pos[i], rotVec, VEC2(1, 1), rot, true)
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
							new cBallBullet(key, m_pos[i], rotVec, VEC2(1, 1), rot, true)
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

		if (m_isShot == false)
			m_isSubShot = false;
	}
}

void cPlayer::Bomb()
{
	if (m_bomb > 0 && INPUT->KeyDown(DIK_X)) {
		m_bomb--;
	}
}

void cPlayer::Move()
{
	//shift누르면 속도 50% 됨
	if (INPUT->KeyPress(DIK_LSHIFT)) {
		m_speed = 350.f * 0.5f;
		if (m_hasBall == true) {
			auto& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			auto& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 15, m_pos.y - 50), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 10, m_pos.y - 50), 0.1);
		}
	} 
	else {
		if (m_speed != 350.f) m_speed = 350.f;
		if (m_hasBall == true) {
			auto& ballPos0 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[0]->GetRefPos();
			auto& ballPos1 = ((cBalls*)OBJFIND(BALLS))->GetPlayerBalls()[1]->GetRefPos();
			Lerp(ballPos0, VEC2(m_pos.x - 50, m_pos.y), 0.1);
			Lerp(ballPos1, VEC2(m_pos.x + 45, m_pos.y), 0.1);
		}
	}

	if (INPUT->KeyPress(DIK_LEFT) && INPUT->KeyPress(DIK_RIGHT))
		m_nowPlayerStatus = pIDLE;

	else if (INPUT->KeyPress(DIK_LEFT) || INPUT->KeyPress(DIK_RIGHT)) {
		if (INPUT->KeyDown(DIK_LEFT) || INPUT->KeyDown(DIK_RIGHT))
			//좌우키가 최초로 눌린 경우 애니메이션을 변경해야 하므로
			//현재 프레임을 초기화
			m_ani->m_nowFrame = 0;
		if (INPUT->KeyPress(DIK_LEFT)) {
			//왼쪽으로 가는 애니메이션으로 변경시켜줘야 함
			m_nowPlayerStatus = pLEFT;
			if (m_pos.x - 10 > 50) m_pos.x -= m_speed * D_TIME;
			else m_pos.x = 50 + 10;
		}
		if (INPUT->KeyPress(DIK_RIGHT)) {
			//오른쪽으로 가는 애니메이션으로 변경시켜줘야 함
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

