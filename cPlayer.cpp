#include "DXUT.h"
#include "cPlayerBullet.h"
#include "cBulletAdmin.h"
#include "cTimer.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_bulletTimer = new cTimer(100);

	m_pos = VEC2(200, WINSIZEY / 2);
	m_size = VEC2(1.f, 1.f);
	m_tag = TAGS::PLAYER;
	m_speed = 350.f;
	m_ani = new cAnimation(100, 4);
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_bulletTimer);
}

void cPlayer::Update()
{
	m_ani->Update();

	nowPlayerStatus = pIDLE;

	//shift������ �ӵ� 50% ��
	if (INPUT->KeyPress(DIK_LSHIFT)) m_speed = 350.f * 0.5f;
	else m_speed = 350.f;

	if(INPUT->KeyDown(DIK_LEFT) || INPUT->KeyDown(DIK_RIGHT))
		m_ani->m_nowFrame = 0;

	if (INPUT->KeyPress(DIK_LEFT)) {
		//�������� ���� �ִϸ��̼����� ���������� ��
		nowPlayerStatus = pLEFT;
		m_pos.x -= m_speed * D_TIME;
	}
	if (INPUT->KeyPress(DIK_RIGHT)) {
		//���������� ���� �ִϸ��̼����� ���������� ��
		nowPlayerStatus = pRIGHT;
		m_pos.x += m_speed * D_TIME;
	}

	if (INPUT->KeyPress(DIK_UP))
		m_pos.y -= m_speed * D_TIME;
	if (INPUT->KeyPress(DIK_DOWN))
		m_pos.y += m_speed * D_TIME;

	if (m_bulletTimer->Update() && INPUT->KeyPress(DIK_Z)) {
		SOUND->Copy("shotSND");
		//�Ѿ� �߻�
		char key[256] = "";
		if (isReimou == true)
			sprintf(key, "player_reimou_mainShot");
		else
			sprintf(key, "player_marisa_mainShot");

		((cBulletAdmin*)(OBJFIND(BULLET)))->GetPlayerBullet().push_back(
			new cPlayerBullet(key, m_pos)
		);
	}
}

void cPlayer::Render()
{
	m_img = IMAGE->FindImage(pStatus[isReimou][nowPlayerStatus], m_ani->m_nowFrame);
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, m_img->m_color);
}
