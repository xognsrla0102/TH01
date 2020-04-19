#pragma once
#include "cBullet.h"
class cEnemyRazer : public cBullet
{
private:
	time_t m_start = timeGetTime();
	time_t m_atk = 0;

	BOOL m_isDone = FALSE;

	INT	   m_startDelay;
	INT	   m_atkDelay;
public:
	cEnemyRazer(string key, VEC2 pos, INT startDelay, INT atkDelay, VEC2 size = VEC2(0.1f, 1.f), FLOAT rot = 0.f);
	virtual ~cEnemyRazer();

	virtual void Update() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;
};

