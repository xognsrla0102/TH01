#pragma once

class cTexture
{
public:
	//같은 이미지를 여러개의 변수에 할당할 때
	//개별적인 위치를 가지지 못하므로 구조상 문제가 있지만
	//시간이 없다... 일단 보류

	LPDIRECT3DTEXTURE9 m_text = nullptr;
	D3DXIMAGE_INFO m_info;

	VEC2 m_pos = VEC2(0, 0);
	VEC2 m_size = VEC2(1, 1);

	vector<VEC2> m_endPos;

	float m_a = 255;
	float m_r = 255;
	float m_g = 255;
	float m_b = 255;

	float m_rot = 0.f;

	D3DXCOLOR m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b);

	cTexture() {}
	cTexture(const char* sz);
	virtual ~cTexture();

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b); }
};
