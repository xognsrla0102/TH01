#include "DXUT.h"
#include "cEnemy.h"

cEnemy::cEnemy()
{
}

cEnemy::~cEnemy()
{
}

void cEnemy::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cEnemy::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 * m_size.x > 50 + INGAMEX + 300 ||
		m_pos.x + m_img->m_info.Width / 2 * m_size.x < 50 - 300 ||
		m_pos.y - m_img->m_info.Height / 2 * m_size.y > 50 + INGAMEY + 300 ||
		m_pos.y + m_img->m_info.Height / 2 * m_size.y < 50 - 300
		) m_isLive = false;
	else return;
}

BOOL cEnemy::CanFire()
{
	if (m_pos.x - m_img->m_info.Width / 2 > 50 + INGAMEX ||
		m_pos.x + m_img->m_info.Width / 2 < 50 ||
		m_pos.y - m_img->m_info.Height / 2 > 50 + INGAMEY ||
		m_pos.y + m_img->m_info.Height / 2 < 50
		) return false;
	return true;
}

