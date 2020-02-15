#pragma once

class cEffect
{
private:
	cAnimation* m_ani;
	string m_imgName;

	VEC2 m_pos = VEC2(0, 0);
	float m_size = 1.f;

	bool m_isDone = false;
public:
	cEffect(const string name, VEC2 pos, float size = 1.f);
	~cEffect();

	void Update();
	void Render();
};

