#pragma once
class cTexture abstract
{
public:
	LPDIRECT3DTEXTURE9 m_text;
	D3DXIMAGE_INFO m_info;

	VEC2 m_pos = VEC2(0, 0);
	vector<VEC2> m_endPos;

	float m_a = 255;
	float m_r = 255;
	float m_g = 255;
	float m_b = 255;

	D3DXCOLOR m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b);

	cTexture();
	virtual ~cTexture() {}

	virtual void AddImage(string path, int cnt = 1) PURE;
	virtual cTexture* FindImage(int cnt = 0) PURE;

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b); }
};
