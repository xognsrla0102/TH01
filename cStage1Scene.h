#pragma once
#include "cScene.h"

class cButton;
class cStage1Scene : public cScene
{
public:
	time_t m_startTime = timeGetTime();
	time_t m_pauseTime = 0;

	BOOL m_isPause = FALSE;
	BOOL m_isExit = FALSE;

	vector<cButton*> m_pause;
	vector<cButton*> m_exit;

	INT m_nowButton = 1;

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

	VEC2 m_img1Pos = VEC2(50, 50);
	VEC2 m_img2Pos = VEC2(50, 50);

	FLOAT m_scrool = 0.f;

	vector<cTimer*> m_mobSpawn;
public:
	cStage1Scene();
	virtual ~cStage1Scene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void PauseOrExit();

	void ScroolMap();

	void LevelDesign();
};

