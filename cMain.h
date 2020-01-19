#pragma once
class cMain
{
private:
	cTexture* m_fps[5] = { nullptr };
public:
	cMain();
	~cMain();

	void Update();
	void Render();

	void LostDevice();
	void ResetDevice();
};

