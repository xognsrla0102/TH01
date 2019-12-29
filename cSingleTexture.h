#pragma once
#include "cTexture.h"
class cSingleTexture : public cTexture
{
public:
	cSingleTexture() {}
	virtual ~cSingleTexture();

	virtual void AddImage(string path, int cnt = 1) override;
	virtual cTexture* FindImage(int cnt = 0) override;
};

