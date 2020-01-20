#pragma once
#include "cScene.h"
class cOptionScene : public cScene
{
private:
	cTexture* m_BG = nullptr;
public:
	cOptionScene();
	virtual ~cOptionScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

