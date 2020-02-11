#include "DXUT.h"
#include "cTimer.h"
#include "cBallBullet.h"
#include "cBulletAdmin.h"
#include "cBall.h"

cBall::cBall(VEC2& pos, bool isLeft) : m_pPos(pos)
{
	m_pos = pos;

	m_img = IMAGE->FindImage(m_ballImg[isMarisa]);
	m_isLeft = isLeft;
}

cBall::~cBall()
{
	Release();
}

void cBall::Update()
{
	m_pos = m_pPos;

	if (m_isLeft) {
		m_pos.x = m_pPos.x - 50;
		m_rot -= 4;
	}
	else {
		m_pos.x = m_pPos.x + 45;
		m_rot += 4;
	}
}

void cBall::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cBall::Release()
{
}
