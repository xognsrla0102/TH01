#pragma once
#include "cObject.h"

class cTexture;
class cPlayer : public cObject
{
private:
	cTexture* m_img = nullptr;
	FLOAT speed = 300.f;
public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};

