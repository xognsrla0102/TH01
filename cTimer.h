#pragma once
class cTimer
{
private:
	time_t m_start = timeGetTime();
	int m_delay = 0;
public:
	cTimer(int delay);
	~cTimer() {}

	bool Update();
};

