#pragma once
#include "cBullet.h"
class cEnemyBullet : public cBullet
{
private:
	INT m_kind;
public:
	cEnemyBullet(string key, VEC2 pos, INT kind, FLOAT speed, VEC2 dir = VEC2(0, -1), VEC2 size = VEC2(1.f, 1.f), FLOAT rot = 0.f);
	virtual ~cEnemyBullet();

	virtual void Update() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;

	void Straight();
	void Follow();
};

