#pragma once
#include "cObject.h"

class cPath;
class cEnemy abstract : public cObject
{
public:
	cPath* m_path = nullptr;
	FLOAT m_hp = 0.f;
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void OutMapChk() PURE;
};

