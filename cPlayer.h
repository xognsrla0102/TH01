#pragma once
#include "cObject.h"

class cBullet;
class cPlayer : public cObject
{
public:
	bool isHit = false;
public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};

