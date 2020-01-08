#pragma once
#include "cSingleton.hpp"

class cTexture;
class cImageManager : public cSingleton<cImageManager>
{
private:
	friend class cSingleton<cImageManager>;
private:
	map<string, cTexture*> m_imgs;
	LPD3DXSPRITE m_sprite;
public:
	cImageManager();
	virtual ~cImageManager();

	void Begin();
	void End();

	void LostDevice();
	void ResetDevice();

	void InsertImage(string name, string path, int cnt = 1);
	cTexture* FindImage(string name, int cnt = 0);

	void Render(cTexture* text, VEC2 pos, float size = 1, float rot = 0, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255), bool center = false);
	void CenterRender(cTexture* text, VEC2 pos, VEC2 center, float size = 1, float rot = 0, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
};

#define IMAGE cImageManager::GetInst()