#pragma once
#include "cObject.h"

class cBullet abstract : public cObject
{
private:
	VEC2 dir;
	vector<VEC2> endPos;
public:
	cBullet() {}
	virtual ~cBullet() {}

	virtual void Update() PURE;
	virtual void Render();
};

