#include "DXUT.h"
#include "cFairy.h"

cFairy::cFairy(INT hp, INT color, INT kind, VEC2 pos, FLOAT rot, VEC2 size)
{
	m_hp = hp;
	m_color = color;
	m_kind = kind;
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	m_ani = new cAnimation(100, m_endframes[m_color]);
} 

cFairy::~cFairy()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_path);
}

void cFairy::Update()
{
	m_ani->Update();
	m_img = IMAGE->FindImage(m_colorKey[m_color], m_ani->m_nowFrame);
	
	if(m_isMove == TRUE)
		m_path->Update();
	
	Pattern();
}

void cFairy::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cFairy::Pattern()
{
	INT nowTime = timeGetTime() - m_patternTime;

	이제 업데이트에 따라서 다음 위치로 러프시켜주기만 하면 됨
	Lerp(m_pos, m_path->m_endPos[m_path->m_nowPos], 0.03);
}

