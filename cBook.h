#pragma once
#include "cEnemy.h"
class cBook : public cEnemy
{
private:
	string m_colorKey[3] = {
		"enemy_book_red",
		"enemy_book_green",
		"enemy_book_pink"
	};
	INT m_color;
public:
	cPath*	m_path = nullptr;
	INT		m_circleCnt;
	BOOL	m_isRandShot = FALSE;
public:
	cBook(INT hp, INT color, INT kind, VEC2 pos, FLOAT rot = 0.f, VEC2 size = VEC2(1, 1));
	virtual ~cBook();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Pattern() override;

	void Pattern1(INT cnt);
	void Pattern2();
};

