#pragma once
#include "cScene.h"
class cHowtoScene : public cScene
{
private:
	vector<cTexture*> m_bgs;
	int m_nowImg = 0;
	int m_rgb = 0;
public:
	cHowtoScene();
	virtual ~cHowtoScene() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

