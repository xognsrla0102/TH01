#pragma once
#include "cEnemy.h"

class cOne : public cEnemy
{
public:
	FLOAT m_theta;

	INT m_bulletCnt;
public:
	cOne(INT hp, INT kind, VEC2 pos, FLOAT rot = 0.f, VEC2 size = VEC2(1, 1));
	virtual ~cOne();

	virtual void Update() override;
	virtual void Pattern() override;

	void Pattern1();
	void Pattern2();
};

