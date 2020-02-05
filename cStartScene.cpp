#include "DXUT.h"
#include "cButton.h"
#include "cStartScene.h"

cStartScene::cStartScene()
{
	m_img = IMAGE->FindImage("startBG");

	m_mode = IMAGE->FindImage("startSELECT_MODE");
	m_char = IMAGE->FindImage("startSELECT_CHARACTER");
	m_weapon = IMAGE->FindImage("startSELECT_WEAPON");

	m_mode->m_endPos.push_back(VEC2(WINSIZEX / 2, -100));
	m_char->m_endPos.push_back(VEC2(WINSIZEX / 2, -100));
	m_weapon->m_endPos.push_back(VEC2(400, 0));

	m_mode->m_endPos.push_back(VEC2(WINSIZEX / 2, 100));
	m_char->m_endPos.push_back(VEC2(WINSIZEX / 2, 100));
	m_weapon->m_endPos.push_back(VEC2(400, 150));

	m_buttons.push_back(new cModeButton);
	m_buttons.push_back(new cModeButton);

	m_buttons[mLUNATIC]->m_button = new cButton("lunaticBT", VEC2(1.5f, 1.5f), 0.2f);
	m_buttons[mEXTRA]->m_button = new cButton("extraBT", VEC2(1.5f, 1.5f), 0.2f);

	m_charButtons.push_back(new cButton("reimouBT", VEC2(1.f, 1.f), 0.f));
	m_charButtons.push_back(new cButton("marisaBT", VEC2(1.f, 1.f), 0.f));

	m_charWeapon[0].push_back(new cButton("reimou1BT", VEC2(1.f, 1.f), 0.15f));
	m_charWeapon[0].push_back(new cButton("reimou2BT", VEC2(1.f, 1.f), 0.15f));
	m_charWeapon[1].push_back(new cButton("marisa1BT", VEC2(1.f, 1.f), 0.15f));
	m_charWeapon[1].push_back(new cButton("marisa2BT", VEC2(1.f, 1.f), 0.15f));

	//mSTART_POS
	if (isExtra == true)
		m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 300));
	else
		m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 400));
	//mLEFT_POS
	m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(350, 400));
	//mENTER_POS
	m_buttons[mLUNATIC]->m_butEndPos.push_back(VEC2(350, 600));

	//mSTART_POS
	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(WINSIZEX / 2, 500));
	//mLEFT_POS
	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(350, 400));
	//mENTER_POS
	m_buttons[mEXTRA]->m_butEndPos.push_back(VEC2(350, 600));
}

cStartScene::~cStartScene()
{
	for (auto iter : m_buttons) {
		SAFE_DELETE(iter->m_button);
		SAFE_DELETE(iter);
	}
	m_buttons.clear();

	for (auto iter : m_charButtons)
		SAFE_DELETE(iter);
	m_charButtons.clear();

	for (auto iter : m_charWeapon[0])
		SAFE_DELETE(iter);
	for (auto iter : m_charWeapon[1])
		SAFE_DELETE(iter);
	m_charWeapon[0].clear();
	m_charWeapon[1].clear();
}

void cStartScene::Init()
{
	m_nowEnter = 0;

	m_charButton = 0;
	m_weaponButton = 0;

	for (auto iter : m_isNextEnter)
		iter = false;
	m_isNextEnter[0] = true;

	m_img->m_a = 0;

	m_mode->m_a = 255;
	m_char->m_a = 255;
	m_weapon->m_a = 255;

	m_mode->m_pos = m_mode->m_endPos[0];
	m_char->m_pos = m_char->m_endPos[0];
	m_weapon->m_pos = m_weapon->m_endPos[0];

	m_nowButPosState = mSTART_POS;

	cButton* nowBut = m_buttons[m_nowButton]->m_button;
	nowBut->SetSize(VEC2(1.5f, 1.5f));
	nowBut->m_oldSize = nowBut->GetSize().x;

	m_buttons[m_nowButton]->m_button->m_isOn = false;
	m_nowButton = 0;
	m_buttons[0]->m_button->m_isOn = true;

	m_buttons[mLUNATIC]->m_button->SetPos(VEC2(WINSIZEX + 300, m_buttons[mLUNATIC]->m_butEndPos[mSTART_POS].y));
	m_buttons[mEXTRA]->m_button->SetPos(VEC2(WINSIZEX + 300, 500));

	m_charButtons[0]->SetPos(VEC2(800, 350));
	m_charButtons[1]->SetPos(VEC2(0, 0));

	m_charButtons[0]->m_alpha = 0;
	m_charButtons[1]->m_alpha = 0;

	m_charButtons[0]->m_isOn = -1;
	m_charButtons[1]->m_isOn = -1;

	for (size_t i = 0; i < sizeof(m_charWeapon) / sizeof(m_charWeapon[0]); i++) {
		m_charWeapon[0][i]->SetPos(VEC2(400, 300 + i * 120));
		m_charWeapon[1][i]->SetPos(VEC2(400, 300 + i * 120));

		m_charWeapon[0][i]->m_alpha = 0;
		m_charWeapon[1][i]->m_alpha = 0;
	}
	m_charWeapon[0][0]->m_isOn = true;
	m_charWeapon[1][0]->m_isOn = true;
}

void cStartScene::Update()
{
	if (m_isNextEnter[0] == true)
		for (auto iter : m_buttons)
			iter->m_button->Update();
	else if (m_isNextEnter[1] == true)
		for (auto iter : m_charButtons)
			iter->Update();
	else
		for (auto iter : m_charWeapon[m_charButton])
			iter->Update();

	//난이도 선택씬
	if (m_isNextEnter[0] == true && isExtra == true && (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))) {
		SOUND->Play("keymoveSND");
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
	//캐릭터 선택씬
	else if (m_isNextEnter[1] == true && (isCharUp == false && isCharDown == false)
		&& (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))
		) {
		SOUND->Play("keymoveSND");
		if (KEYDOWN(DIK_UP)) {
			isCharUp = true;
			//새로 올라올 캐릭터 아래로 보내기
			m_charButtons[!m_charButton]->SetPos(VEC2(800, 700));
		}
		else {
			isCharDown = true;
			//새로 올라올 캐릭터 위로 보내기
			m_charButtons[!m_charButton]->SetPos(VEC2(800, 0));
		}
	}
	//무기 선택씬
	else if (m_isNextEnter[2] == true && (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN))) {
		SOUND->Play("keymoveSND");
		m_charWeapon[m_charButton][m_weaponButton]->m_isOn = false;
		m_weaponButton = !m_weaponButton;
		m_charWeapon[m_charButton][m_weaponButton]->m_isOn = true;
	}
	
	if (isCharUp == true) {
		//현재 선택된 버튼 올라가면서 사라짐
		Lerp(m_charButtons[m_charButton]->GetRefPos().y, 100.f, 0.1);
		Lerp(m_charButtons[m_charButton]->m_alpha, 0.f, 0.1);

		//아닌 버튼 아래에서 올라옴
		Lerp(m_charButtons[!m_charButton]->GetRefPos().y, 350.f, 0.2);
		Lerp(m_charButtons[!m_charButton]->m_alpha, 255.f, 0.1);

		if (m_charButtons[!m_charButton]->GetPos().y < 351.f) {
			m_charButtons[!m_charButton]->GetRefPos().y = 350.f;
			m_charButtons[m_charButton]->m_alpha = 0.f;
			m_charButton = !m_charButton;
			isCharUp = false;
		}
	}
	else if (isCharDown == true) {
		//현재 선택된 버튼 내려가면서 사라짐
		Lerp(m_charButtons[m_charButton]->GetRefPos().y, 700.f, 0.1);
		Lerp(m_charButtons[m_charButton]->m_alpha, 0.f, 0.1);

		//아닌 버튼 위에서 내려옴
		Lerp(m_charButtons[!m_charButton]->GetRefPos().y, 350.f, 0.2);
		Lerp(m_charButtons[!m_charButton]->m_alpha, 255.f, 0.1);

		if (m_charButtons[!m_charButton]->GetPos().y > 349.f) {
			m_charButtons[!m_charButton]->GetRefPos().y = 350.f;
			m_charButtons[m_charButton]->m_alpha = 0.f;
			m_charButton = !m_charButton;
			isCharDown = false;
		}
	}
	else if (m_isNextEnter[1] == true && (isCharUp == false && isCharDown == false))
		Lerp(m_charButtons[m_charButton]->m_alpha, 255.f, 0.03);

	if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
		SOUND->Copy("selectSND");

		if (m_isNextEnter[0] == true) {
			m_char->m_pos = m_char->m_endPos[0];
			m_nowButPosState = mLEFT_POS;

			cButton* nowBut = m_buttons[m_nowButton]->m_button;
			nowBut->SetSize(VEC2(1.3f, 1.3f));
			nowBut->m_oldSize = nowBut->GetSize().x;
		}
		else if (m_isNextEnter[1] == true) {
			m_weapon->m_pos = m_weapon->m_endPos[0];
			m_nowButPosState = mENTER_POS;

			cButton* nowBut = m_buttons[m_nowButton]->m_button;
			nowBut->SetSize(VEC2(1.f, 1.f));
			nowBut->m_oldSize = nowBut->GetSize().x;

			if (isCharUp == true || isCharDown == true) {
				isCharUp = isCharDown = false;
				m_charButton = !m_charButton;
			}
			m_charButtons[m_charButton]->SetPos(VEC2(800, 350));
			m_charButtons[!m_charButton]->SetPos(VEC2(0, 0));
			m_charButtons[m_charButton]->m_alpha = 255.f;
			m_charButtons[!m_charButton]->m_alpha = 0.f;

			for (size_t i = 0; i < sizeof(m_charWeapon) / sizeof(m_charWeapon[0]); i++) {
				m_charWeapon[0][i]->m_alpha = 0;
				m_charWeapon[1][i]->m_alpha = 0;
			}
			m_charWeapon[0][m_weaponButton]->m_isOn = false;
			m_charWeapon[1][m_weaponButton]->m_isOn = false;
			m_charWeapon[0][0]->m_isOn = true;
			m_charWeapon[1][0]->m_isOn = true;
			//레이무
			//if(m_charButton == 0)

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

			m_charButtons[0]->m_alpha = 0.f;
			m_charButtons[1]->m_alpha = 0.f;
			m_charButtons[0]->SetPos(VEC2(800, 350));
			m_charButtons[1]->SetPos(VEC2(0, 0));

			m_charButton = 0;
			isCharUp = isCharDown = false;
		}
		else {
			m_char->m_pos = m_char->m_endPos[0];
			m_nowButPosState = mLEFT_POS;

			cButton* nowBut = m_buttons[m_nowButton]->m_button;
			nowBut->SetSize(VEC2(1.3f, 1.3f));
			nowBut->m_oldSize = nowBut->GetSize().x;
		}
	}

	for (size_t i = 0; i < m_buttons.size(); i++)
		Lerp(m_buttons[i]->m_button->GetRefPos(), m_buttons[i]->m_butEndPos[m_nowButPosState], 0.08);

	if (m_isNextEnter[0] == true)
		Lerp(m_mode->m_pos, m_mode->m_endPos[1], 0.05);
	else if (m_isNextEnter[1] == true)
		Lerp(m_char->m_pos, m_char->m_endPos[1], 0.05);
	else
		Lerp(m_weapon->m_pos, m_weapon->m_endPos[1], 0.05);

	Lerp(m_img->m_a, 255.f, 0.05);
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
		if (m_isNextEnter[0] != true) {
			for (auto iter : m_charButtons)
				iter->Render();
			if (m_isNextEnter[2] == true) {
				for (auto iter : m_charWeapon[m_charButton])
					iter->Render();
			}
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
