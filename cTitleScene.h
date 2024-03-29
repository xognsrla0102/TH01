#pragma once
#include "cScene.h"

struct sIntroObject {
	cTexture* m_img = nullptr;

	time_t m_startTime = timeGetTime();

	VEC2 m_pos;
	vector<VEC2> m_end;

	float m_alpha = 255.f;

	float m_speed = 300;
	float m_size = 1.3f;
	float m_rot = 0.f;
};

class cButton;
class cTitleScene : public cScene
{
private:
	cTexture* m_whiteEffect = nullptr;
	cTexture* m_bg = nullptr;

	time_t m_enterTime = timeGetTime();

	sIntroObject m_intro[6] = { nullptr };
	vector<cButton*> m_buttons;

	int nowIntroPos = MID_POS;

	int m_nowButton = 0;

	bool isEnter = false;
	bool isChangeScene = false;
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

