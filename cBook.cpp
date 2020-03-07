#include "DXUT.h"
#include "cBook.h"

cBook::cBook(INT hp, INT color, INT kind, VEC2 pos, FLOAT rot, VEC2 size)
{
	m_hp = hp;
	m_color = color;
	m_kind = kind;
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

cBook::~cBook()
{
}

void cBook::Update()
{
}

void cBook::Render()
{
}

void cBook::Pattern()
{
}
