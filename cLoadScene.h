#pragma once
#include "cScene.h"

class cTexture;
class cLoadScene : public cScene
{
private:
	cTexture* m_BG = nullptr;
	map<string, cTexture*> m_datas;
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

