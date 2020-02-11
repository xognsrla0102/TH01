#pragma once
#include "cObject.h"

class cBullet abstract : public cObject
{
public:
	VEC2 m_dir = VEC2(0, -1);
	vector<VEC2> m_endPos;

	float m_atk = 0.f;
public:
	cBullet() {}
	virtual ~cBullet() {}

	virtual void Update() PURE;
	virtual void Render();

	virtual void OutMapChk() PURE;
	virtual void Collision() PURE;
};

