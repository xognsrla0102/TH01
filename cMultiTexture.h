#pragma once
#include "cTexture.h"

class cMultiTexture : public cTexture
{
private:
	vector<cTexture*> m_multiImgs;
public:
	cMultiTexture() {}
	virtual ~cMultiTexture();

	virtual void AddImage(string path, int cnt = 1) override;
	virtual cTexture* FindImage(int cnt = 0) override;
};

