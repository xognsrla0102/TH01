#include "DXUT.h"
#include "cButton.h"
#include "cOptionScene.h"

cOptionScene::cOptionScene()
{
	m_BG = IMAGE->FindImage("titleBG");

	m_buttons.push_back(new cButton("bgmBT"));
	m_buttons.push_back(new cButton("onBT"));
	m_buttons.push_back(new cButton("offBT"));

	for (int i = 0; i < 3; i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 15, 200));

	m_buttons[m_nowButton]->m_isOn = true;

	for (int i = 2; i > 0; i--)
		m_buttons[i]->m_left = m_buttons[i - 1];
	for (int i = 0; i < 2; i++)
		m_buttons[i]->m_right = m_buttons[i + 1];
}

cOptionScene::~cOptionScene()
{
	for (auto iter : m_buttons)
		SAFE_DELETE(iter);
}

void cOptionScene::Init()
{
}

void cOptionScene::Update()
{
	for (auto iter : m_buttons)
		iter->Update();

	if (KEYDOWN(DIK_UP)) {
	/*	m_buttons[m_nowButton]->m_isOn = false;
		if (m_buttons[m_nowButton]->m_up != nullptr) {
			m_nowButton--;
			m_buttons[m_nowButton]->m_isOn = true;
		}
		else {
			while (m_buttons[m_nowButton]->m_down != nullptr)
				m_nowButton++;
			m_buttons[m_nowButton]->m_isOn = true;
		}*/
		SOUND->Play("keymoveSND");
	}
	if (KEYDOWN(DIK_DOWN)) {
		/*m_buttons[m_nowButton]->m_isOn = false;
		if (m_buttons[m_nowButton]->m_down != nullptr) {
			m_nowButton++;
			m_buttons[m_nowButton]->m_isOn = true;
		}
		else {
			while (m_buttons[m_nowButton]->m_up != nullptr)
				m_nowButton--;
			m_buttons[m_nowButton]->m_isOn = true;
		}*/
		SOUND->Play("keymoveSND");
	}
	if (KEYDOWN(DIK_LEFT)) {
		//m_buttons[m_nowButton]->m_isOn = false;
		//if (m_buttons[m_nowButton]->m_left != nullptr) {
		//	m_nowButton++;
		//	m_buttons[m_nowButton]->m_isOn = true;
		//}
		//else {
		//	while (m_buttons[m_nowButton]->m_right != nullptr)
		//		//m_nowButton; ?? 어케 처리함
		//	//m_buttons[m_nowButton]->m_isOn = true;
		//}
		SOUND->Play("keymoveSND");
	}
	if (KEYDOWN(DIK_RIGHT)) {
	/*	m_buttons[m_nowButton]->m_isOn = false;
		if (m_buttons[m_nowButton]->m_down != nullptr) {
			m_nowButton++;
			m_buttons[m_nowButton]->m_isOn = true;
		}
		else {
			while (m_buttons[m_nowButton]->m_up != nullptr)
				m_nowButton--;
			m_buttons[m_nowButton]->m_isOn = true;
		}*/
		SOUND->Play("keymoveSND");
	}


	Lerp<int>(m_rgb, 255, 0.05);
}

void cOptionScene::Render()
{
	for (auto iter : m_buttons)
		iter->Render();

	IMAGE->Render(m_BG, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb));
}

void cOptionScene::Release()
{
}
