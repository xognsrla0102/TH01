#include "DXUT.h"
#include "cEffect.h"

cEffect::cEffect(const string name, int imgCnt, VEC2 pos, VEC2 velSize, VEC2 size, VEC4 rgb)
{
	m_imgName = name;

	m_pos = pos;
	m_velSize = velSize;
	m_size = size;

	m_a = rgb.x;
	m_r = rgb.y;
	m_g = rgb.z;
	m_b = rgb.w;

	SetColor();

	m_ani = new cAnimation(m_delay, imgCnt);
}

cEffect::~cEffect()
{
	SAFE_DELETE(m_ani);
}

void cEffect::Update()
{
	m_ani->Update();

	if (m_size.x > 0.f) m_size += m_velSize * 10 * D_TIME;
	else if (m_size.x < 0.f) m_size = VEC2(0, 0);

	m_a -= 800.f * D_TIME;
	if (m_a < 0.f) m_isDone = true;

	SetColor();
}

void cEffect::Render()
{
	cTexture* nowImg = IMAGE->FindImage(m_imgName, m_ani->m_nowFrame);
	IMAGE->Render(nowImg, m_pos, m_size, 0.f, true, m_color);
}
