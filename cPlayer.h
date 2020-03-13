#pragma once
#include "cObject.h"

class cBullet;
class cPlayer : public cObject
{
public:
	cTexture* m_bombFace = nullptr;
	cTexture* m_bombName = nullptr;

	cTimer* m_bulletTimer = nullptr;
	cTimer* m_subBulletTimer = nullptr;
	
	time_t m_bombTime = timeGetTime();
	time_t m_notDeadTime = timeGetTime();

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

	int m_life = playerLife;
	int m_bomb = playerBomb;

	int m_level = 1;
	int m_power = 0;
	int m_graze = 0;
	int m_jum = 0;

	int m_bRot[2][3] = {
		{ -110, -130, -150 },
		{ -70, -50, -30 }
	};

	int m_nowRot = 0;

	float m_score = 0.f;
	float m_pAlpha = 255.f;

	bool m_hasBall = FALSE;
	bool m_isHit = FALSE;
	bool m_isNotDead = FALSE;
	bool m_isShot = FALSE;
	bool m_isSubShot = FALSE;
	bool m_isBomb = FALSE;
	bool m_isLevelUp = FALSE;
public:
	cPlayer();
	~cPlayer();

	void Init();
	void Update();
	void Render();
	void Release();

	void Hit();
	void NotDead();

	void Fire();
	void SubFire();

	void Bomb();

	void Move();
};

