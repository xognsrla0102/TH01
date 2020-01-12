#include "DXUT.h"
#include "cTexture.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_pos = VEC2(200, WINSIZEY / 2);
	m_size = VEC2(1.f, 1.f);
	m_tag = TAGS::PLAYER;

	m_img = IMAGE->FindImage("player");
}

cPlayer::~cPlayer()
{
}

void cPlayer::Update()
{
	if (INPUT->KeyDown(DIK_A))
		m_pos.x -= speed * D_TIME;
	if (INPUT->KeyDown(DIK_D))
		m_pos.x += speed * D_TIME;
	if (INPUT->KeyDown(DIK_W))
		m_pos.y -= speed * D_TIME;
	if (INPUT->KeyDown(DIK_S))
		m_pos.y += speed * D_TIME;
}

void cPlayer::Render()
{
	IMAGE->CenterRender(m_img, m_pos, VEC2(m_img->m_info.Width / 2, m_img->m_info.Height / 2));
}
