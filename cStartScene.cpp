#include "DXUT.h"
#include "cButton.h"
#include "cStartScene.h"

cStartScene::cStartScene()
{
	m_bg = IMAGE->FindImage("startBG");
	m_img = IMAGE->FindImage("startSELECT");

	m_button = new cButton("lunaticBT", VEC2(2.f, 2.f));

	m_buttonPos.push_back(VEC2(WINSIZEX + 300, WINSIZEY / 2));
	m_buttonPos.push_back(VEC2(WINSIZEX / 2, WINSIZEY / 2));

	m_button->SetPos(m_buttonPos[0]);
	m_button->m_isOn = true;
}

cStartScene::~cStartScene()
{
	SAFE_DELETE(m_button);
}

void cStartScene::Init()
{
	m_rgb = 0;
	m_imgYpos = -150;
	m_button->SetPos(m_buttonPos[0]);
}

void cStartScene::Update()
{
	if (KEYDOWN(DIK_X) || KEYDOWN(DIK_ESCAPE)) {
		SOUND->Copy("cancelSND");
		SCENE->ChangeScene("titleScene");
	}

	int nowPos = m_button->GetPos().x;
	Lerp<int>(nowPos, m_buttonPos[1].x, 0.05);

	Lerp<int>(m_imgYpos, 250, 0.03);

	m_button->SetPos(VEC2(nowPos, WINSIZEY / 2));

	Lerp<int>(m_rgb, 255, 0.05);
}

void cStartScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb));
	IMAGE->Render(m_img, VEC2(WINSIZEX / 2, m_imgYpos), 1.5f, 0.f, true);

	m_button->Render();

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cStartScene::Release()
{
}
