#pragma once
class cTexture abstract
{
protected:
	LPDIRECT3DTEXTURE9 m_text;
	D3DXIMAGE_INFO m_info;
public:
	cTexture();
	virtual ~cTexture() {}

	virtual void AddImage(string path, int cnt = 1) PURE;
	virtual cTexture* FindImage(int cnt = 0) PURE;
};
