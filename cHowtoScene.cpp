#include "DXUT.h"
#include "cHowtoScene.h"

cHowtoScene::cHowtoScene()
{
	for (size_t i = 0; i < 12; i++) {
		char key[256];
		sprintf(key, "howto_%d", i);
		m_bgs.push_back(IMAGE->FindImage(key));
	}
}

void cHowtoScene::Init()
{
	m_nowImg = 0;
	m_rgb = 0;
}

void cHowtoScene::Update()
{
	if (KEYDOWN(DIK_LEFT)) {
		SOUND->Play("keymoveSND");
		if(m_nowImg > 0)
			m_nowImg--;
	}

	if (KEYDOWN(DIK_RIGHT)) {
		SOUND->Play("keymoveSND");
		if(m_nowImg < m_bgs.size() - 1)
			m_nowImg++;
		else
			SCENE->ChangeScene("titleScene");
	}

	if (KEYDOWN(DIK_Z)) {
		SOUND->Copy("selectSND");
		if(m_nowImg == m_bgs.size() - 1)
			SCENE->ChangeScene("titleScene");
		else
			m_nowImg++;
	}

	if (KEYDOWN(DIK_X)) {
		SOUND->Copy("cancelSND");
		SCENE->ChangeScene("titleScene");
	}

	Lerp<int>(m_rgb, 255, 0.05);
}

void cHowtoScene::Render()
{
	IMAGE->Render(m_bgs[m_nowImg], VEC2(0, 0), 1.f, 0.f, false,
		D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb)
	);

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cHowtoScene::Release()
{
}
