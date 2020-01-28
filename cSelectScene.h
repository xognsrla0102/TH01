#pragma once
#include "cScene.h"

class cButton;
class cSelectScene : public cScene
{
private:
	cTexture* m_bg = nullptr;

public:
	cSelectScene();
	virtual ~cSelectScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

