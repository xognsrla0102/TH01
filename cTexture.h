#pragma once
class cTexture
{
private:
	LPDIRECT3DTEXTURE9 m_text;
	D3DXIMAGE_INFO m_info;
public:
	cTexture(LPDIRECT3DTEXTURE9 text, D3DXIMAGE_INFO info)
		: m_text(text), m_info(info) {}
	virtual ~cTexture() {}

	virtual void AddImage(string name, string path, int cnt = 0) PURE;
	virtual void FindImage(string name, int cnt = -1) PURE;
}
