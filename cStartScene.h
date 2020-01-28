#pragma once
#include "cScene.h"

class cButton;
class cStartScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
	cTexture* m_img = nullptr;
	cButton* m_button = nullptr;

	vector<VEC2> m_buttonPos;

	int m_imgYpos = -150;
	int m_rgb = 0;
public:
	cStartScene();
	virtual ~cStartScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

