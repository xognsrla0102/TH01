#pragma once

class cTexture;
class cPlayer
{
private:
	cTexture* m_img = nullptr;
	float rot = 0;
public:
	VEC2 m_pos = VEC2(200, WINSIZEY / 2);
	NEMO rtCol;
	bool isColl = false;
public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};

