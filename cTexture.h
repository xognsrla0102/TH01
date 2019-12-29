#pragma once
class cTexture abstract
{
public:
	LPDIRECT3DTEXTURE9 m_text;
	D3DXIMAGE_INFO m_info;

	cTexture();
	virtual ~cTexture() {}

	virtual void AddImage(string path, int cnt = 1) PURE;
	virtual cTexture* FindImage(int cnt = 0) PURE;
};
