#pragma once
#include "cScene.h"
class cStage1Scene : public cScene
{
public:
	cStage1Scene();
	virtual ~cStage1Scene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

