#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(int delay) : m_delay(delay)
{
}

bool cTimer::Update()
{
	if (timeGetTime() - m_start > m_delay) {
		m_start = timeGetTime();
		return true;
	}
	return false;
}
