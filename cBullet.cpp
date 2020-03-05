#include "DXUT.h"
#include "cBullet.h"

void cBullet::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, m_img->m_color);
}

