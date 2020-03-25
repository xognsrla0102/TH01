#pragma once
#include "cBullet.h"
class cBallBullet : public cBullet
{
private:
	cImage* m_img = nullptr;
	FLOAT m_accel = 1.f;
	BOOL m_isFadeIn = FALSE;
	time_t m_atkTime = 0;
public:
	INT m_atkDelay;
	BOOL m_isHoming = FALSE;
	INT m_index;
public:
	cBallBullet(string key, VEC2 pos, VEC2 dir = VEC2(0, -1), VEC2 size = VEC2(1.f, 1.f), FLOAT rot = 0.f, BOOL isHoming = FALSE);
	virtual ~cBallBullet();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OutMapChk() override;
	virtual void Collision() override;

	void Homing();
};

