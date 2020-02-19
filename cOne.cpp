#include "DXUT.h"
#include "cPath.h"
#include "cOne.h"

cOne::cOne(VEC2 pos, FLOAT rot, VEC2 size)
{
	m_path = new cPath;

	m_hp = 300.f;

	m_img = IMAGE->FindImage("enemy_one");
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

cOne::~cOne()
{
	SAFE_DELETE(m_path);
}

void cOne::Update()
{
	m_rot += 10;
	if (m_rot > 360.f) m_rot -= 360.f;
	m_pos.y += 500.f * D_TIME;
}

void cOne::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cOne::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > 50 + INGAMEX + 300 ||
		m_pos.x + m_img->m_info.Width / 2 < 50 - 300 ||
		m_pos.y - m_img->m_info.Height / 2 > 50 + INGAMEY + 300 ||
		m_pos.y + m_img->m_info.Height / 2 < 50 - 300
		) m_isLive = false;
	else return;
}
