#pragma once
#include "cScene.h"

class cButton;
class cModeButton {
public:
	cButton* m_button = nullptr;
	vector<VEC2> m_butEndPos;
};

class cStartScene : public cScene
{
private:
	cTexture* m_mode = nullptr;
	cTexture* m_char = nullptr;
	cTexture* m_weapon = nullptr;

	vector<cModeButton*> m_buttons;

	int m_nowButton = 0;
	int m_nowButPosState = mSTART_POS;

	int m_nowEnter = 0;
	bool m_isNextEnter[3] = { false };

public:
	cStartScene();
	virtual ~cStartScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

