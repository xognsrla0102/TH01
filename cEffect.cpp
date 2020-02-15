#include "DXUT.h"
#include "cEffect.h"

cEffect::cEffect(const string name, VEC2 pos, float size)
{
	m_imgName = name;
	m_pos = pos;
	m_size = size;
}

cEffect::~cEffect()
{
}

void cEffect::Update()
{
}

void cEffect::Render()
{
	cTexture* nowImg = IMAGE->FindImage(m_imgName, m_ani->m_nowFrame);
	IMAGE->Render(nowImg, m_pos, m_size, 0.f, true);
}
