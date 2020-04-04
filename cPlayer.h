#pragma once
#include "cObject.h"

class cBullet;
class cPlayer : public cObject
{
public:
	cTexture* m_bombFace = nullptr;
	cTexture* m_bombName = nullptr;

	cImage* m_spellB_RED[2] = { nullptr };
	cImage* m_spellB_BLUE[2] = { nullptr };

	cImage* m_spellB_Razer = nullptr; 

	cTimer* m_bulletTimer = nullptr;
	cTimer* m_subBulletTimer = nullptr;
	
	time_t m_reimouA_BulletTime;
	time_t m_reimouB_SpreadTime;
	time_t m_marisaA_BulletTime;
	time_t m_marisaB_RazerTime;

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
	INT m_nowPlayerStatus = pIDLE;

	INT m_nowBulletCnt = 0;
	INT m_bulletCnt = 5;
	INT m_nowSubBulletCnt = 0;

	INT m_life = playerLife;
	INT m_bomb = playerBomb;

	INT m_level = 1;
	INT m_wasPower = 0;
	INT m_power = 0;
	INT m_graze = 0;
	INT m_jum = 0;

	INT m_bRot[2][3] = {
		{ -110, -130, -150 },
		{ -70, -50, -30 }
	};

	INT m_nowRot = 0;

	FLOAT m_score = 0.f;
	FLOAT m_pAlpha = 255.f;

	FLOAT m_shotAtk = 1.f;
	FLOAT m_subShotAtk = 1.f;

	BOOL m_hasBall = FALSE;
	BOOL m_isHit = FALSE;
	BOOL m_isNotDead = FALSE;
	BOOL m_isShot = FALSE;
	BOOL m_isSubShot = FALSE;
	BOOL m_isBomb = FALSE;
	BOOL m_isBombShot = FALSE; 
	BOOL m_isLevelUp = FALSE;
	BOOL m_isFullPower = FALSE;
	BOOL m_isExtend = FALSE;
public:
	cPlayer();
	~cPlayer();

	void Init();
	void Update();
	void Render();
	void Release();

	void Graze();

	void Hit();
	void NotDead();

	void Fire();
	void SubFire();

	void Bomb();

	void ReimouA();
	void ReimouB();
	void MarisaA();
	void MarisaB();

	void Move();
};

