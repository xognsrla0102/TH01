#pragma once
#include "cScene.h"

class cTexture;
class cPlayer;
class cLoadScene : public cScene
{
private:
	cTexture* m_BG = nullptr;

	cPlayer* m_player = nullptr;
	cTexture* obj2 = nullptr;
	NEMO rtCol2;
	VEC2 d;

	map<string, cTexture*> m_datas;
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	VEC2 getDistance(NEMO a, NEMO b);
	VEC2 getHeight(NEMO a);
	VEC2 getWidth(NEMO a);
	bool OBB(NEMO a, NEMO b);
};

