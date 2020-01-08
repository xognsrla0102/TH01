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
	rtCol = {
		m_pos.x - m_img->m_info.Width / 2.0,
		m_pos.y - m_img->m_info.Height / 2.0,
		(double)m_img->m_info.Height,
		(double)m_img->m_info.Width,
		(double)rot
	};

	if (isColl) m_img = IMAGE->FindImage("isColl");
	else m_img = IMAGE->FindImage("player");

	if (INPUT->KeyDown(DIK_A))
		m_pos.x -= 300 * D_TIME;
	if (INPUT->KeyDown(DIK_D))
		m_pos.x += 300 * D_TIME;
	if (INPUT->KeyDown(DIK_W))
		m_pos.y -= 300 * D_TIME;
	if (INPUT->KeyDown(DIK_S))
		m_pos.y += 300 * D_TIME;

	if (INPUT->KeyDown(DIK_PGUP))
		if (rot < 0) rot += 360;
		else rot -= 2;
	if (INPUT->KeyDown(DIK_PGDN))
		if (rot > 360) rot -= 360;
		else rot += 2;
}

void cPlayer::Render()
{
	IMAGE->Render(m_img, m_pos, 1.f, rot, D3DCOLOR_ARGB(255,255,255,255), true);
}
