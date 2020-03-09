#pragma once
#include "cBullet.h"
class cBallBullet : public cBullet
{
public:
	bool m_isHoming = FALSE;
public:
	cBallBullet(string key, VEC2 pos, VEC2 dir = VEC2(0, -1), VEC2 size = VEC2(1.f, 1.f), FLOAT rot = 0.f, BOOL isHoming = FALSE);
	virtual ~cBallBullet();

	virtual void Update() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;

	void Homing();
};

