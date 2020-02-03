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

cHowtoScene::~cHowtoScene()
{
	m_bgs.clear();
}

void cHowtoScene::Init()
{
	for (auto iter : m_bgs)
		iter->m_a = 0;

	m_nowImg = 0;
}

void cHowtoScene::Update()
{
	if (KEYDOWN(DIK_LEFT)) {
		SOUND->Play("keymoveSND");
		if (m_nowImg > 0) {
			m_bgs[m_nowImg]->m_a = 0;
			m_nowImg--;
		}
		else
			SCENE->ChangeScene("titleScene");
	}

	if (KEYDOWN(DIK_RIGHT)) {
		SOUND->Play("keymoveSND");
		if (m_nowImg < m_bgs.size() - 1) {
			m_bgs[m_nowImg]->m_a = 0;
			m_nowImg++;
		}
		else
			SCENE->ChangeScene("titleScene");
	}

	if (KEYDOWN(DIK_Z) || KEYDOWN(DIK_RETURN)) {
		SOUND->Copy("selectSND");
		if(m_nowImg == m_bgs.size() - 1)
			SCENE->ChangeScene("titleScene");
		else {
			m_bgs[m_nowImg]->m_a = 0;
			m_nowImg++;
		}
	}

	if (KEYDOWN(DIK_X)) {
		SOUND->Copy("cancelSND");
		SCENE->ChangeScene("titleScene");
	}

	Lerp(m_bgs[m_nowImg]->m_a, 255.f, 0.04);
	m_bgs[m_nowImg]->SetNowRGB();
}

void cHowtoScene::Render()
{
	IMAGE->Render(m_bgs[m_nowImg], VEC2(0, 0), 1.f, 0.f, false, m_bgs[m_nowImg]->m_color);

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cHowtoScene::Release()
{
}
