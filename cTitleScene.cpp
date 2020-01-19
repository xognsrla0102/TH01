#include "DXUT.h"
#include "cTexture.h"
#include "cButton.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
	isMidi = true;
	SOUND->Play("th_01_%s", true, true);

	m_whiteEffect = IMAGE->FindImage("whiteBG");
	m_bg = IMAGE->FindImage("titleBG");

	for (int i = 0; i < 7; i++) {
		char str[256];
		sprintf(str, "title_text_%d", i);
		m_intro[i].m_img = IMAGE->FindImage(str);
	}

	//글자 세팅

	//동
	m_intro[0].m_pos = VEC2(WINSIZEX / 2, WINSIZEY + 100);
	m_intro[0].m_end = VEC2(WINSIZEX / 2, 100);
	//방
	m_intro[1].m_pos = VEC2(-100, 220);
	m_intro[1].m_end = VEC2(WINSIZEX / 2, 220);
	//홍
	m_intro[2].m_pos = m_intro[2].m_end = VEC2(WINSIZEX / 2, 340);
	m_intro[2].m_alpha = 0;
	m_intro[2].m_rot = 2080.f;
	//마
	m_intro[3].m_pos = VEC2(WINSIZEX + 100, 460);
	m_intro[3].m_end = VEC2(WINSIZEX / 2, 460);
	//향
	m_intro[4].m_pos = VEC2(WINSIZEX / 2, -100);
	m_intro[4].m_end = VEC2(WINSIZEX / 2, 580);

	//버튼 세팅

	for (int i = 0; i < 6; i++) {
		char str[256];
		sprintf(str, "title_bt_%d", i);
		m_buttons.push_back(new cButton(str));
		m_buttons[i]->SetPos(VEC2(1000 - i * 15, 200 + i * 70));
	}
	m_buttons[m_nowButton]->m_isOn = true;

	//버튼 이어주기
	않이 왜 버튼 안이어져 잘래 ㅅㅂ
	for(int i = 5; i > 0; i--)
		m_buttons[i]->Insert(&m_buttons[i]->m_up, &m_buttons[i - 1]);
	for (int i = 0; i < 5; i++)
		m_buttons[i]->Insert(&m_buttons[i]->m_down, &m_buttons[i + 1]);
} 

cTitleScene::~cTitleScene()
{
	for (auto iter : m_buttons)
		SAFE_DELETE(iter);
}

void cTitleScene::Init()
{
}

void cTitleScene::Update()
{
	for (auto iter : m_buttons)
		iter->Update();

	if (KEYDOWN(DIK_UP)) {
		m_buttons[m_nowButton]->m_isOn = false;
		if (m_buttons[m_nowButton]->m_up != nullptr) {
			m_buttons[m_nowButton]->m_up->m_isOn = true;
			m_nowButton--;
		}
		else {
			while (m_buttons[m_nowButton]->m_down != nullptr)
				m_nowButton++;
			m_buttons[m_nowButton]->m_isOn = true;
		}
	}
	if (KEYDOWN(DIK_DOWN)) {
		m_buttons[m_nowButton]->m_isOn = false;
	}

	if (KEYUP(DIK_RETURN) || KEYUP(DIK_Z) && isEnter == true) {
		switch (m_nowButton) {
		case BUTTON::START:
			SCENE->ChangeScene("startScene");
			break;
		case BUTTON::REPLAY:
			SCENE->ChangeScene("replayScene");
			break;
		case BUTTON::SCORE:
			SCENE->ChangeScene("scoreScene");
			break;
		case BUTTON::MUSIC:
			SCENE->ChangeScene("musicScene");
			break;
		case BUTTON::OPTION:
			SCENE->ChangeScene("optionScene");
			break;
		case BUTTON::EXIT:
			PostQuitMessage(23523);
			break;
		}
		isEnter = false;
	}

	if (KEYUP(DIK_ESCAPE) || KEYUP(DIK_X)) {
		m_buttons[m_nowButton]->m_isOn = false;
		m_nowButton = BUTTON::EXIT;
		m_buttons[m_nowButton]->m_isOn = true;
	}

	if (KEYUP(DIK_RETURN) || KEYUP(DIK_Z) && isEnter == false) {
		for (int i = 0; i < 5; i++)
			m_intro[i].m_end.x = 350;
		if (m_alpha > 80) m_alpha = 80;
		isEnter = true;
	}
	
	if (isEnter == true)
		Lerp(m_rgb, 150, 0.02);
		
	for (int i = 0; i < 7; i++) {
		//각각 시간차에 따라 움직이기 시작함
		if (timeGetTime() - m_intro[i].m_startTime > i * 300.f) {
			D3DXVec2Lerp(&m_intro[i].m_pos, &m_intro[i].m_pos, &m_intro[i].m_end, 0.03);
			if (i == 2) {
				Lerp(m_intro[i].m_alpha, 255, 0.05);
				Lerp(m_intro[i].m_rot, 0.f, 0.025);
			}
		}
	}
	Lerp(m_alpha, 0, 0.01);
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_XRGB(m_rgb, m_rgb, m_rgb, m_rgb));

	for (int i = 0; i < 7; i++)
		IMAGE->Render(m_intro[i].m_img, m_intro[i].m_pos, m_intro[i].m_size, m_intro[i].m_rot, true,
			D3DCOLOR_ARGB(m_intro[i].m_alpha, 255, 255, 255)
		);

	for (auto iter : m_buttons)
		iter->Render();

	IMAGE->Render(m_whiteEffect, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_alpha, 255, 255, 255));
}

void cTitleScene::Release()
{
}
