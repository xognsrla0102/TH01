#pragma once
#include "cEnemy.h"

class cOne : public cEnemy
{
public:
	cOne(INT kind, VEC2 pos, FLOAT rot = 0.f, VEC2 size = VEC2(1, 1));
	virtual ~cOne();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OutMapChk() override;
	virtual void Pattern(INT kind) override;
};

