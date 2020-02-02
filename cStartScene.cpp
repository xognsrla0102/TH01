#include "DXUT.h"
#include "cButton.h"
#include "cStartScene.h"

cStartScene::cStartScene()
{
	m_img = IMAGE->FindImage("startBG");
	m_mode = IMAGE->FindImage("startSELECT_MODE");
	m_char = IMAGE->FindImage("startSELECT_CHARACTER");
	m_weapon = IMAGE->FindImage("startSELECT_WEAPON");

	m_buttons.push_back(new cModeButton);
	m_buttons.push_back(new cModeButton);

	m_buttons[mLUNATIC]->m_button = new cButton("lunaticBT", VEC2(1.5f, 1.5f), 0.3f);
	m_buttons[mEXTRA]->m_button = new cButton("extraBT", VEC2(1.5f, 1.5f), 0.3f);

	if (isExtra == true)
		m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 300));
	else
		m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 400));
	m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(300, 600));

	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 500));
	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(300, 600));

	if (isExtra == true)
		m_buttons[mLUNATIC]->m_button->SetPos(VEC2(WINSIZEX + 300, 300));
	else
		m_buttons[mLUNATIC]->m_button->SetPos(VEC2(WINSIZEX + 300, 400));
	m_buttons[mEXTRA]->m_button->SetPos(VEC2(WINSIZEX + 300, 500));

	m_buttons[mLUNATIC]->m_button->m_isOn = true;
}

cStartScene::~cStartScene()
{
}

void cStartScene::Init()
{
	m_rgb = 0;

	m_buttons[m_nowButton]->m_isOn = false;
	m_nowButton = 0;

	if (isExtra == true)
		m_buttons[0]->SetPos(VEC2(WINSIZEX + 300, 300));
	else
		m_buttons[0]->SetPos(VEC2(WINSIZEX + 300, 400));
	m_buttons[1]->SetPos(VEC2(WINSIZEX + 300, 500));

	m_buttons[0]->m_isOn = true;
}

void cStartScene::Update()
{
	for (auto iter : m_buttons)
		iter->Update();

	if (isExtra == true && (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))) {
		m_buttons[m_nowButton]->m_isOn = false;
		if (KEYDOWN(DIK_UP)) {
			if (m_nowButton > 0) m_nowButton--;
			else m_nowButton = m_buttons.size() - 1;
		}
		else {
			if (m_nowButton < m_buttons.size() - 1) m_nowButton++;
			else m_nowButton = 0;
		}
		m_buttons[m_nowButton]->m_isOn = true;
	}

	if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
		SOUND->Play("selectSND");
	}

	if (KEYDOWN(DIK_X) || KEYDOWN(DIK_ESCAPE)) {
		SOUND->Copy("cancelSND");
		SCENE->ChangeScene("titleScene");
	}

	for (size_t i = 0; i < m_buttons.size(); i++)
		Lerp<VEC2>(m_buttons[i]->GetRefPos(), m_butEndPos[i], 0.08);

	Lerp<int>(m_rgb, 255, 0.05);
}

void cStartScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb));

	if (isExtra == true)
		for (auto iter : m_buttons)
			iter->Render();
	else
		m_buttons[0]->Render();

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cStartScene::Release()
{
}
