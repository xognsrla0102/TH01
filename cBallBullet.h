#pragma once
#include "cBullet.h"
class cBallBullet : public cBullet
{
public:
	cBallBullet(string key, VEC2 pos, VEC2 dir = VEC2(0, -1), VEC2 size = VEC2(1.f, 1.f), FLOAT rot = 0.f);
	virtual ~cBallBullet();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;
};

