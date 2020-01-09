#include "DXUT.h"
#include "cTexture.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_img = IMAGE->FindImage("player");
}

cPlayer::~cPlayer()
{
}

void cPlayer::Update()
{
	if (INPUT->KeyDown(DIK_A))
		m_pos.x -= 300 * D_TIME;
	if (INPUT->KeyDown(DIK_D))
		m_pos.x += 300 * D_TIME;
	if (INPUT->KeyDown(DIK_W))
		m_pos.y -= 300 * D_TIME;
	if (INPUT->KeyDown(DIK_S))
		m_pos.y += 300 * D_TIME;
}

void cPlayer::Render()
{
	IMAGE->CenterRender(m_img, m_pos, VEC2(m_img->m_info.Width / 2, m_img->m_info.Height / 2));
}
