#pragma once

class cEffect
{
public:
	cAnimation* m_ani;
	string m_imgName;

	VEC2 m_pos = VEC2(0, 0);
	VEC2 m_velSize = VEC2(0, 0);
	VEC2 m_size = VEC2(1, 1);

	float m_a = 255.f;
	float m_r = 255.f;
	float m_g = 255.f;
	float m_b = 255.f;

	bool m_isDone = false;

	int m_delay = 100;

	D3DCOLOR m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b);

public:
	cEffect(const string name, int imgCnt, VEC2 pos, VEC2 velSize = VEC2(1, 1), VEC2 size = VEC2(1, 1), VEC4 argb = VEC4(255, 255, 255, 255));
	~cEffect();

	void Update();
	void Render();

	void SetColor() { m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b); }
};

