#pragma once
#include "cScene.h"

class cButton;
class cOptionScene : public cScene
{
private:
	cTexture* m_BG = nullptr;

	vector<vector<cButton*> > m_manyButtons;
	//2차원 배열로 버튼 관리
	vector<cButton*> m_buttons;
	//한 줄마다 버튼 넣고 2차원 배열에 넣어줌

	int m_rgb = 0;

	int m_nowLine = 0;
	int m_nowButton = 1;
public:
	cOptionScene();
	virtual ~cOptionScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

