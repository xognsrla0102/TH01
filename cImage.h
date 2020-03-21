#pragma once
class cImage
{
public:
	//cTexture클래스에서 개별적으로 위치를 못 가지는 것에 대한
	//임시방편 클래스 구조를 바꾸기엔 시간이 너무 많이 걸리므로
	//지금부터라도 cImage클래스를 사용
	cTexture* m_img;

	VEC2 m_pos = VEC2(0, 0);
	vector<VEC2> m_endPos;

	FLOAT m_a = 255;
	FLOAT m_r = 255;
	FLOAT m_g = 255;
	FLOAT m_b = 255;

	FLOAT m_rot = 0.f;

	D3DXCOLOR m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b);

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b); }
};

