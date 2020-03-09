#pragma once
class cTimer
{
private:
	time_t m_start = timeGetTime();
public:
	INT m_delay = 0;
public:
	cTimer(INT delay);
	~cTimer() {}

	BOOL Update();
};

