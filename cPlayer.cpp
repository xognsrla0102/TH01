#include "DXUT.h"
#include "cPlayerBullet.h"
#include "cBulletAdmin.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_pos = VEC2(200, WINSIZEY / 2);
	m_size = VEC2(1.f, 1.f);
	m_tag = TAGS::PLAYER;
	m_speed = 300.f;
	m_ani = new cAnimation(100, 4);
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_ani);
}

void cPlayer::Update()
{
	m_ani->Update();

	//shift누르면 속도 80% 됨
	if (INPUT->KeyPress(DIK_LSHIFT)) m_speed = 300.f * 0.8f;
	else m_speed = 300.f;

	if (INPUT->KeyPress(DIK_LEFT)) {
		//왼쪽으로 가는 애니메이션으로 변경시켜줘야 함

		m_pos.x -= m_speed * D_TIME;
	}
	if (INPUT->KeyPress(DIK_RIGHT)) {
		//오른쪽으로 가는 애니메이션으로 변경시켜줘야 함

		m_pos.x += m_speed * D_TIME;
	}

	if (INPUT->KeyPress(DIK_UP))
		m_pos.y -= m_speed * D_TIME;
	if (INPUT->KeyPress(DIK_DOWN))
		m_pos.y += m_speed * D_TIME;

	if (INPUT->KeyPress(DIK_Z)) {
		//총알 발사
		char key[256] = "";

		if (character[0][0] == true) sprintf(key, "player_reimou_mainShot");
		else if (character[1][0] == true) sprintf(key, "player_marisa_mainShot");

		((cBulletAdmin*)(OBJFIND(BULLET)))->GetPlayerBullet().push_back(
			new cPlayerBullet(key, m_pos)
		);
	}
}

void cPlayer::Render()
{
	cTexture* nowImg = m_img->FindImage(m_ani->m_nowFrame);

	IMAGE->Render(nowImg, m_pos, m_size, m_rot, true, m_img->m_color);
}
