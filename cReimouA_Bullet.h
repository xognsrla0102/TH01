#pragma once
#include "cBullet.h"

class cTimer;
class cReimouA_Bullet : public cBullet
{ 
private:
	time_t m_start = timeGetTime();
	cTimer* m_rgbTimers[3] = { nullptr };
	cImage* m_img = nullptr;
	INT m_rgbDir[3] = { 1, 1, 1 };
	INT m_life = 3;
	FLOAT m_accel = 0.f;
public:
	cReimouA_Bullet(VEC2 pos);
	virtual ~cReimouA_Bullet();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;

	void Homing();
};

