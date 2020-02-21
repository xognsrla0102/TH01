#pragma once
#include "cObject.h"

class cEnemy abstract : public cObject
{
protected:
	time_t m_patternTime = timeGetTime();
	time_t m_bulletTime  = timeGetTime();

	INT m_kind;
public:
	FLOAT m_hp = 0.f;
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void OutMapChk() PURE;
	virtual void Pattern(INT kind) PURE;
};

