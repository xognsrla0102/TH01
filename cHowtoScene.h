#pragma once
#include "cScene.h"
class cHowtoScene : public cScene
{
private:
	vector<cTexture*> m_bgs;
public:
	cHowtoScene() {}
	virtual ~cHowtoScene() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

