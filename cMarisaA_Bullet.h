#pragma once
#include "cBullet.h"

class cTimer;
class cMarisaA_Bullet : public cBullet
{
private:
	cImage* m_img = nullptr;
	BOOL m_rotLeft;
public:
	cMarisaA_Bullet(VEC2 pos, VEC2 dir, VEC2 size, BOOL rotLeft, VEC4 color);
	virtual ~cMarisaA_Bullet();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;
};