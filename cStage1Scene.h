#pragma once
#include "cScene.h"

class cButton;
class cStage1Scene : public cScene
{
public:
	time_t m_startTime = timeGetTime();
	time_t m_pauseTime = 0;
	time_t m_continueTime = 0;

	BOOL m_isPause = FALSE;
	BOOL m_isExit = FALSE;
	BOOL m_isContinue = FALSE;

	vector<cButton*> m_pause;
	vector<cButton*> m_exit;
	vector<cButton*> m_continue;

	INT m_nowButton = 1;
	INT m_nowContinue = 3;

	cTexture* m_img2 = nullptr;
	cTexture* m_black = nullptr;
	cTexture* m_ui = nullptr;

	cTexture* m_life = nullptr;
	cTexture* m_bomb = nullptr;

	cTexture* m_name = nullptr;
	cTexture* m_title = nullptr;
	cTexture* m_circle = nullptr;
	cTexture* m_musicName = nullptr;
	cTexture* m_spellBlack = nullptr;

	cTexture* m_fullPower = nullptr;
	cTexture* m_powerMax = nullptr;

	VEC2 m_img1Pos = VEC2(50, 50);
	VEC2 m_img2Pos = VEC2(50, 50);

	FLOAT m_scrool = 0.f;
	FLOAT m_extraDelay = 0.5f;

	vector<cTimer*> m_mobSpawn;
public:
	cStage1Scene();
	virtual ~cStage1Scene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Continue();
	void PauseOrExit();
	void ScroolMap();
	void LevelDesign();
};

