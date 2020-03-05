#pragma once
#include "cScene.h"
class cStage1Scene : public cScene
{
public:
	time_t m_startTime = timeGetTime();

	cTexture* m_img2 = nullptr;
	cTexture* m_black = nullptr;
	cTexture* m_ui = nullptr;

	cTexture* m_life = nullptr;
	cTexture* m_bomb = nullptr;

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

	void ScroolMap();

	void LevelDesign();
};

