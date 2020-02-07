#include "DXUT.h"
#include "cTimer.h"
#include "cAnimation.h"

cAnimation::cAnimation(int delay, int endFrame)
	: m_endFrame(endFrame)
{
	m_timer = new cTimer(delay);
}

cAnimation::~cAnimation()
{
	SAFE_DELETE(m_timer);
}

void cAnimation::Update()
{
	if (m_timer->Update()) {
		if (m_nowFrame != m_endFrame) m_nowFrame++;
		else m_nowFrame = 0;
	}
}
