#pragma once
#include "cObject.h"

class cTexture;
class cPlayer : public cObject
{
public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};

