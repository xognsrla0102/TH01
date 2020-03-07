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

	INT m_endframes[5] = { 8,8,4,8,4 };

	INT m_color;
public:
	cPath* m_path = nullptr;
	INT m_circleCnt;
	BOOL m_isRandShot = FALSE;
public:
	cFairy(INT hp, INT color, INT kind, VEC2 pos, FLOAT rot = 0.f, VEC2 size = VEC2(1, 1));
	virtual ~cFairy();

	virtual void Update() override;
	virtual void Pattern() override;

	void Pattern1(INT cnt);
	void Pattern2();
};

