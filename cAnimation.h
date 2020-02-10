#pragma once

class cTimer;
class cAnimation
{
private:
	cTimer* m_timer = nullptr;
public:
	int m_nowFrame = 0;
	int m_endFrame;
public:
	cAnimation(int delay, int m_endFrame);
	~cAnimation();

	void Update();
};

