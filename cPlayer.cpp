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

	m_bulletTimer = new cTimer(80);
	m_subBulletTimer = new cTimer(150);
	m_ani = new cAnimation(100, 4);
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
	m_subBulletCnt = 3;
	m_level = 2;

	m_hasBall = false;
	m_isHit = false;
	m_isShot = false;
	m_isSubShot = false;

	m_bulletTimer = new cTimer(80);
	m_subBulletTimer = new cTimer(150);
	m_ani = new cAnimation(100, 4);

	if (isMarisa == false)
		if (isB == false)
			m_subBulletTimer->m_delay = m_bulletTimer->m_delay;
	else
		if (isB == false) 1;
		else 1;
}

void cPlayer::Update()
{
	if (m_hasBall == false && m_level > 1) {
		for (size_t i = 0; i < 2; i++) {
			((cBalls*)OBJFIND(BALLS))->GetPlayerBalls().push_back(
				new cBall(OBJFIND(PLAYER)->GetRefPos(), i)
			);
		}
		m_hasBall = true;
	}

	m_ani->Update();

	if(m_nowPlayerStatus != pIDLE)
		m_nowPlayerStatus = pIDLE;

	//shift누르면 속도 50% 됨
	if (INPUT->KeyPress(DIK_LSHIFT)) m_speed = 350.f * 0.5f;
	else m_speed = 350.f;

	if (INPUT->KeyPress(DIK_LEFT) && INPUT->KeyPress(DIK_RIGHT))
		m_nowPlayerStatus = pIDLE;
	else if (INPUT->KeyPress(DIK_LEFT) || INPUT->KeyPress(DIK_RIGHT)) {
		if(INPUT->KeyDown(DIK_LEFT) || INPUT->KeyDown(DIK_RIGHT))
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
	if (INPUT->KeyPress(DIK_DOWN)){
		if (m_pos.y + 10 < 50 + INGAMEY) m_pos.y += m_speed * D_TIME;
		else m_pos.y = 50 + INGAMEY - 10;
	}

	if (m_isShot == false && INPUT->KeyPress(DIK_Z)) {
		m_isShot = true;
		m_isSubShot = true;
	}
	if (m_isShot == true && m_bulletTimer->Update()) {
		//총알 발사
		SOUND->Copy("shotSND");
		char key[256];
		if (isMarisa == false) sprintf(key, "player_reimou_mainShot");
		else sprintf(key, "player_marisa_mainShot");

		VEC2 rotVec;
		float rot = -90.f;
		m_level = 7;

		if (isMarisa == false) {
			switch (m_level) {
			case 1:
			case 2:
				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos)
				);
				break;
			case 3:
				rotVec.x = cos(D3DXToRadian(rot - 5));
				rotVec.y = sin(D3DXToRadian(rot - 5));
				D3DXVec2Normalize(&rotVec, &rotVec);

				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos, rotVec)
				);

				rotVec.x = cos(D3DXToRadian(rot + 5));
				rotVec.y = sin(D3DXToRadian(rot + 5));
				D3DXVec2Normalize(&rotVec, &rotVec);

				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos, rotVec)
				);
				break;
			case 4:
			case 5:
			case 6:
				rotVec.x = cos(D3DXToRadian(rot - 10));
				rotVec.y = sin(D3DXToRadian(rot - 10));
				D3DXVec2Normalize(&rotVec, &rotVec);

				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos, rotVec)
				);

				rotVec.x = cos(D3DXToRadian(rot));
				rotVec.y = sin(D3DXToRadian(rot));
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
			case 7:
				rotVec.x = cos(D3DXToRadian(rot - 20));
				rotVec.y = sin(D3DXToRadian(rot - 20));
				D3DXVec2Normalize(&rotVec, &rotVec);

				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos, rotVec)
				);

				rotVec.x = cos(D3DXToRadian(rot - 10));
				rotVec.y = sin(D3DXToRadian(rot - 10));
				D3DXVec2Normalize(&rotVec, &rotVec);

				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos, rotVec)
				);

				rotVec.x = cos(D3DXToRadian(rot));
				rotVec.y = sin(D3DXToRadian(rot));
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

				rotVec.x = cos(D3DXToRadian(rot + 20));
				rotVec.y = sin(D3DXToRadian(rot + 20));
				D3DXVec2Normalize(&rotVec, &rotVec);

				((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet().push_back(
					new cPlayerBullet(key, m_pos, rotVec)
				);
				여기 부분 for문으로 대체하기
				break;
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


		if (m_nowBulletCnt > m_bulletCnt) m_isShot = m_nowBulletCnt = 0;
		else m_nowBulletCnt++;
	}

	if (m_isShot == true && m_subBulletTimer->Update()) {
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

		if (isMarisa == false) {
			if (isB == false) {
				//호밍 애뮬랫
				switch (m_level) {
				case 2:
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i])
						);
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
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i])
						);
					break;
				case 5:
					for (size_t i = 0; i < 2; i++)
						((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
							new cBallBullet(key, m_pos[i])
						);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, this->m_pos)
					);
					break;
				case 6:
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x - 5, m_pos[0].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[0].x + 5, m_pos[0].y))
					);

					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x - 5, m_pos[1].y))
					);
					((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet().push_back(
						new cBallBullet(key, VEC2(m_pos[1].x + 5, m_pos[1].y))
					);
					break;
				default:
					break;
				}
			}
		}

		if (m_nowSubBulletCnt > m_subBulletCnt) m_isSubShot = m_nowSubBulletCnt = 0;
		else m_nowSubBulletCnt++;
	}

	if (playerBomb > 0 && INPUT->KeyDown(DIK_X)) {
		playerBomb--;
	}
}

void cPlayer::Render()
{
	m_img = IMAGE->FindImage(m_pStatus[isMarisa][m_nowPlayerStatus], m_ani->m_nowFrame);
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cPlayer::Release()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_bulletTimer);
	SAFE_DELETE(m_subBulletTimer);
}

