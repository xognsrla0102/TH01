#include "DXUT.h"
#include "cButton.h"
#include "cStartScene.h"

cStartScene::cStartScene()
{
	m_isNextEnter[0] = true;

	m_img = IMAGE->FindImage("startBG");

	m_mode = IMAGE->FindImage("startSELECT_MODE");
	m_char = IMAGE->FindImage("startSELECT_CHARACTER");
	m_weapon = IMAGE->FindImage("startSELECT_WEAPON");

	m_img->m_a = 0;

	m_mode->m_endPos.push_back(VEC2(WINSIZEX / 2, -100));
	m_char->m_endPos.push_back(VEC2(WINSIZEX / 2, -100));
	m_weapon->m_endPos.push_back(VEC2(800, 0));

	m_mode->m_endPos.push_back(VEC2(WINSIZEX / 2, 100));
	m_char->m_endPos.push_back(VEC2(WINSIZEX / 2, 100));
	m_weapon->m_endPos.push_back(VEC2(800, 150));

	m_mode->m_pos = m_mode->m_endPos[0];
	m_char->m_pos = m_char->m_endPos[0];
	m_weapon->m_pos = m_weapon->m_endPos[0];

	m_mode->m_a = 0;
	m_char->m_a = 0;
	m_weapon->m_a = 0;

	m_buttons.push_back(new cModeButton);	 
	m_buttons.push_back(new cModeButton);

	m_buttons[mLUNATIC]->m_button = new cButton("lunaticBT", VEC2(1.5f, 1.5f), 0.2f);
	m_buttons[mEXTRA]->m_button = new cButton("extraBT", VEC2(1.5f, 1.5f), 0.2f);

	//mSTART_POS
	if (isExtra == true)
		m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 300));
	else
		m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 400));
	//mENTER_POS
	m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(350, 600));

	//mSTART_POS
	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 500));
	//mENTER_POS
	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(350, 600));

	m_buttons[mLUNATIC]->m_button->SetPos(VEC2(WINSIZEX + 300, m_buttons[mLUNATIC]->m_butEndPos[mSTART_POS].y));
	m_buttons[mEXTRA]->m_button->SetPos(VEC2(WINSIZEX + 300, 500));

	m_buttons[0]->m_button->m_isOn = true;
}

cStartScene::~cStartScene()
{
	for (auto iter : m_buttons) {
		SAFE_DELETE(iter->m_button);
		SAFE_DELETE(iter);
	}
	m_buttons.clear();
}

void cStartScene::Init()
{
	m_nowEnter = 0;

	for (auto iter : m_isNextEnter)
		iter = false;
	m_isNextEnter[0] = true;

	m_img->m_a = 0;

	m_mode->m_pos = m_mode->m_endPos[0];
	m_char->m_pos = m_char->m_endPos[0];
	m_weapon->m_pos = m_weapon->m_endPos[0];

	m_mode->m_a = 255;
	m_char->m_a = 255;
	m_weapon->m_a = 255;

	m_nowButPosState = mSTART_POS;

	cButton* nowBut = m_buttons[m_nowButton]->m_button;
	nowBut->SetSize(VEC2(1.5f, 1.5f));
	nowBut->m_oldSize = nowBut->GetSize().x;

	m_buttons[m_nowButton]->m_button->m_isOn = false;
	m_nowButton = 0;

	m_buttons[mLUNATIC]->m_button->SetPos(VEC2(WINSIZEX + 300, m_buttons[mLUNATIC]->m_butEndPos[mSTART_POS].y));
	m_buttons[mEXTRA]->m_button->SetPos(VEC2(WINSIZEX + 300, 500));

	m_buttons[0]->m_button->m_isOn = true;
}

void cStartScene::Update()
{
	for (auto iter : m_buttons)
		iter->m_button->Update();

	if (m_isNextEnter[0] == true && isExtra == true && (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))) {
		m_buttons[m_nowButton]->m_button->m_isOn = false;
		if (KEYDOWN(DIK_UP)) {
			if (m_nowButton > 0) m_nowButton--;
			else m_nowButton = m_buttons.size() - 1;
		}
		else {
			if (m_nowButton < m_buttons.size() - 1) m_nowButton++;
			else m_nowButton = 0;
		}
		m_buttons[m_nowButton]->m_button->m_isOn = true;
	}
	else if (m_isNextEnter[1] == true && isExtra == true && (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))) {
		
	}
	else if (m_isNextEnter[2] == true && isExtra == true && (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))) {

	}

	if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
		SOUND->Copy("selectSND");

		if (m_isNextEnter[0] == true) {
			m_char->m_pos = m_char->m_endPos[0];

			m_nowButPosState = mENTER_POS;
			cButton* nowBut = m_buttons[m_nowButton]->m_button;
			nowBut->SetSize(VEC2(1.f, 1.f));
			nowBut->m_oldSize = nowBut->GetSize().x;
		}
		else if (m_isNextEnter[1] == true) {
			m_weapon->m_pos = m_weapon->m_endPos[0];
			//레이무
			//if(m_nowButton == 0)

			//마리사
			//else
		}
		else {
			SCENE->ChangeScene("stage1Scene");
			return;
		}

		m_isNextEnter[m_nowEnter] = false;
		m_nowEnter++;
		m_isNextEnter[m_nowEnter] = true;
	}

	if (KEYDOWN(DIK_X) || KEYDOWN(DIK_ESCAPE)) {
		SOUND->Copy("cancelSND");
		if (m_nowEnter != 0) {
			m_isNextEnter[m_nowEnter] = false;
			m_nowEnter--;
			m_isNextEnter[m_nowEnter] = true;
		}
		else SCENE->ChangeScene("titleScene");

		if (m_isNextEnter[0] == true) {
			m_mode->m_pos = m_mode->m_endPos[0];

			m_nowButPosState = mSTART_POS;
			cButton* nowBut = m_buttons[m_nowButton]->m_button;
			nowBut->SetSize(VEC2(1.5f, 1.5f));
			nowBut->m_oldSize = nowBut->GetSize().x;
		}
		else if (m_isNextEnter[1] == true) {
			m_char->m_pos = m_char->m_endPos[0];
			//레이무
			//if(m_nowButton == 0)

			//마리사
			//else
		}
	}

	for (size_t i = 0; i < m_buttons.size(); i++)
		Lerp<VEC2>(m_buttons[i]->m_button->GetRefPos(), m_buttons[i]->m_butEndPos[m_nowButPosState], 0.08);

	if (m_isNextEnter[0] == true)
		Lerp<VEC2>(m_mode->m_pos, m_mode->m_endPos[1], 0.05);
	else if (m_isNextEnter[1] == true)
		Lerp<VEC2>(m_char->m_pos, m_char->m_endPos[1], 0.05);
	else
		Lerp<VEC2>(m_weapon->m_pos, m_weapon->m_endPos[1], 0.05);

	Lerp(m_img->m_a, 255.f, 0.05);
	m_img->m_a += 0.5f;
	m_img->SetNowRGB();
}

void cStartScene::Render()
{
	IMAGE->Render(m_img, VEC2(0, 0), 1.f, 0.f, false, m_img->m_color);

	if (m_isNextEnter[0] == true) {
		m_buttons[mLUNATIC]->m_button->Render();
		if (isExtra == true) m_buttons[mEXTRA]->m_button->Render();
	}
	else {
		m_buttons[m_nowButton]->m_button->Render();
		if (m_isNextEnter[1] == true) {

		}
		else {

		}
	}

	if(m_isNextEnter[0] == true)
		IMAGE->Render(m_mode, m_mode->m_pos, 1.5f, 0.f, true);
	else if (m_isNextEnter[1] == true)
		IMAGE->Render(m_char, m_char->m_pos, 1.5f, 0.f, true);
	else
		IMAGE->Render(m_weapon, m_weapon->m_pos, 1.5f, 0.f, true);

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cStartScene::Release()
{
}
