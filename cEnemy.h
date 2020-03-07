#pragma once
#include "cObject.h"

class cEnemy abstract : public cObject
{
protected:
	time_t m_bulletTime = timeGetTime();

	INT m_kind;

	INT m_bulletDelay;

	FLOAT m_bulletSpeed;
	FLOAT m_dirRot = 0.f;
public:
	FLOAT m_hp = 0.f;

	BOOL m_isAccel = FALSE;
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() PURE;
	virtual void Render();
	virtual void OutMapChk();
	virtual BOOL CanFire();
	virtual void Pattern() PURE;

	void SetDelay(INT delay) { m_bulletDelay = delay; }
	void SetSpeed(INT speed) { m_bulletSpeed = speed; }
};

