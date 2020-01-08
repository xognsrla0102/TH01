#pragma once
#include "cObject.h"

class cTexture;
class cScene abstract : public cObject
{
private:
	cTexture* m_BG = nullptr;
public:
	cScene() {}
	virtual ~cScene() {}

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

