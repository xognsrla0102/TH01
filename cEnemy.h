#pragma once
#include "cObject.h"

class cEnemy abstract : public cObject
{
protected:
	time_t m_patternTime = timeGetTime();
	time_t m_bulletTime = timeGetTime();

	INT m_kind;

	FLOAT m_dirRot = 0.f;
public:
	FLOAT m_hp = 0.f;
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() PURE;
	virtual void Render();
	virtual void OutMapChk();
	virtual BOOL CanFire();
	virtual void Pattern() PURE;
};

