#pragma once
#include "cBullet.h"
class cPlayerBullet : public cBullet
{
public:
	cPlayerBullet(string key, VEC2 pos, VEC2 size = VEC2(1.f, 1.f), FLOAT rot = 0.f);
	virtual ~cPlayerBullet();

	virtual void Update() override;
	virtual void Render() override;

	virtual void OutMapChk() override;
	virtual void Collision() override;
};

