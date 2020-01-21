#pragma once
#include "cScene.h"

class cButton;
class cOptionScene : public cScene
{
private:
	cTexture* m_BG = nullptr;
	vector<cButton*> m_buttons;

	int m_rgb = 0;
	int m_nowButton = 0;
public:
	cOptionScene();
	virtual ~cOptionScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

