#pragma once
#include "cObject.h"

class cBullet;
class cPlayer : public cObject
{
public:
	cTimer* m_bulletTimer = nullptr;
	cTimer* m_subBulletTimer = nullptr;

	string m_pStatus[2][3] = {
		{
			"player_reimou_idle",
			"player_reimou_left",
			"player_reimou_right"
		},
		{
			"player_marisa_idle",
			"player_marisa_left",
			"player_marisa_right"
		}
	};
	int m_nowPlayerStatus = pIDLE;

	int m_nowBulletCnt = 0;
	int m_bulletCnt = 5;
	int m_nowSubBulletCnt = 0;

	int m_level = 1;

	int m_bRot[2][3] = {
		{ -110, -130, -150 },
		{ -70, -50, -30 }
	};

	int m_nowRot = 0;

	float m_score = 0.f;

	bool m_hasBall = false;
	bool m_isHit = false;
	bool m_isShot = false;
	bool m_isSubShot = false;

public:
	cPlayer();
	~cPlayer();

	void Init();
	void Update();
	void Render();
	void Release();
};

