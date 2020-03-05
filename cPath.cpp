#include "DXUT.h"
#include "cPath.h"

cPath::cPath(VEC2 startPos)
{
	AddPoint(startPos);
}

cPath::~cPath()
{
	m_endPos.clear();
}

void cPath::AddPoint(VEC2 newPos)
{
	m_endPos.push_back(newPos);
}

void cPath::Update()
{
	FLOAT d = DistPoint(m_endPos[m_nowPos], m_endPos[m_nowPos + 1]);

	if (isDone == TRUE) return;
	else if (m_nowPos == m_endPos.size() && d < 0.01f) isDone = true;
	else if (d < 0.01f) m_nowPos++;
}
