#pragma once
#include "cEnemy.h"
class cBook : public cEnemy
{
private:
	cImage* m_magicZone = nullptr;

	string m_colorKey[3] = {
		"enemy_book_red",
		"enemy_book_green",
		"enemy_book_pink"
	};

	string m_bullet_colorOne[3] = {
		"bullet_redOne",
		"bullet_greenOne",
		"bullet_pinkOne"
	};

	string m_bullet_colorRazer[3] = {
		"bullet_redRazer",
		"bullet_greenRazer",
		"bullet_pinkRazer"
	};

	VEC4 m_colorEffect[3] = {
		VEC4(255, 255, 150, 150),
		VEC4(255, 130, 220, 140),
		VEC4(255, 255, 150, 253)
	};

	INT m_color;
	FLOAT m_alpha = 0.f;
	BOOL m_onlyMagicZone;
public:
	cPath*	m_path = nullptr;
	INT		m_circleCnt;
	INT     m_startDelay;
	INT     m_atkDelay;
	BOOL	m_isRandShot = FALSE;
public:
	cBook(INT hp, INT color, INT kind, BOOL onlyMagicZone, VEC2 pos, FLOAT rot = 0.f, VEC2 size = VEC2(1, 1));
	virtual ~cBook();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Pattern() override;

	void Pattern1(INT cnt);
	void Pattern2();
};

