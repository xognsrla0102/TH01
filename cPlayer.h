#pragma once
#include "cObject.h"

class cTexture;
class cPlayer : public cObject
{
private:
	cTexture* m_img = nullptr;
public:
	VEC2 m_pos = VEC2(200, WINSIZEY / 2);
public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};
