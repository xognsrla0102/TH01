#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(INT delay) : m_delay(delay)
{
}

BOOL cTimer::Update()
{
	if (timeGetTime() - m_start > m_delay) {
		m_start = timeGetTime();
		return TRUE;
	}
	return FALSE;
}
