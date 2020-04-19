#pragma once
#include "cEnemy.h"

class cPath;
class cFairy : public cEnemy
{
private:
	string m_colorKey[5] = {
		"enemy_fairy_red",
		"enemy_fairy_orange",
		"enemy_fairy_green",
		"enemy_fairy_blue",
		"enemy_fairy_purple"
	};

	string m_bullet_colorOne[5] = {
		"bullet_redOne",
		"bullet_orangeOne",
		"bullet_greenOne",
		"bullet_blueOne",
		"bullet_purpleOne"
	};

	string m_bulet_colorMeal[5] = {
		"bullet_redMeal",
		"bullet_orangeMeal",
		"bullet_greenMeal",
		"bullet_blueMeal",
		"bullet_purpleMeal"
	};

	VEC4 m_colorEffect[5] = {
		VEC4(255, 255, 150, 150),
		VEC4(255, 255, 127, 0),
		VEC4(255, 150, 230, 150),
		VEC4(255, 150, 150, 255),
		VEC4(255, 200, 135, 255)
	};

	INT m_endframes[5] = { 8,8,4,8,4 };

	INT m_color;
public:
	INT m_circleCnt;
	INT m_divDelta = 2;
	BOOL m_isRandShot = FALSE;
	BOOL m_isAccelCurve = FALSE;
	FLOAT m_accelCurve = 0.f;
public:
	cFairy(INT hp, INT color, INT kind, VEC2 pos, FLOAT rot = 0.f, VEC2 size = VEC2(1, 1));
	virtual ~cFairy();

	virtual void Update() override;
	virtual void Pattern() override;

	void Pattern1(INT cnt);
	void Pattern2();
};

