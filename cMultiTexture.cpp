#include "DXUT.h"
#include "cSingleTexture.h"
#include "cMultiTexture.h"

cMultiTexture::~cMultiTexture()
{
	for (auto iter : m_multiImgs)
		SAFE_DELETE(iter);
	m_multiImgs.clear();
}

void cMultiTexture::AddImage(string path, int cnt)
{
	char sz[128] = "";
	for (int i = 0; i < cnt; i++) {
		sprintf_s(sz, strlen(sz), path.c_str(), i);
		cTexture* text = new cSingleTexture;
		text->AddImage(sz);
		m_multiImgs.push_back(text);
	}
}

cTexture* cMultiTexture::FindImage(int cnt)
{
	if (cnt == 0) return this;
	return m_multiImgs[cnt - 1];
}
