#include "DXUT.h"
#include "cSingleTexture.h"

cSingleTexture::~cSingleTexture()
{
	SAFE_RELEASE(m_text);
}

void cSingleTexture::AddImage(string path, int cnt)
{
	D3DXCreateTextureFromFileExA(
		g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 236, 0, 140), &m_info, nullptr, &m_text
	);
}

cTexture* cSingleTexture::FindImage(int cnt)
{
	return this;
}
