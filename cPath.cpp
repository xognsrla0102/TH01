#include "DXUT.h"
#include "cPath.h"

cPath::~cPath()
{
	ResetPath();
}

void cPath::AddPos(VEC2 pos)
{
	m_endPos.push_back(pos);
}

void cPath::ErasePos(INT idx)
{
	m_endPos.erase(m_endPos.begin() + idx);
}

void cPath::ResetPath()
{
	m_endPos.clear();
}
