#include "DXUT.h"
#include "cButton.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
	SOUND->Play("th_01_%s", true, true);

	m_whiteEffect = IMAGE->FindImage("whiteBG");
	m_bg = IMAGE->FindImage("titleBG");

	for (int i = 0; i < 6; i++) {
		char str[256];
		sprintf(str, "title_text_%d", i);
		m_intro[i].m_img = IMAGE->FindImage(str);
	}

	//글자 세팅

	//동
	m_intro[0].m_pos = VEC2(WINSIZEX / 2, WINSIZEY + 100);
	m_intro[0].m_end.push_back(m_intro[0].m_pos); //START_POS
	m_intro[0].m_end.push_back(VEC2(WINSIZEX / 2, 100)); //ENTER_POS

	//방
	m_intro[1].m_pos = VEC2(-100, 220);
	m_intro[1].m_end.push_back(m_intro[1].m_pos);
	m_intro[1].m_end.push_back(VEC2(WINSIZEX / 2, 220));
	//홍
	m_intro[2].m_pos = VEC2(WINSIZEX / 2, 340);
	m_intro[2].m_end.push_back(m_intro[2].m_pos);
	m_intro[2].m_end.push_back(VEC2(WINSIZEX / 2, 340));
	m_intro[2].m_alpha = 0;
	m_intro[2].m_rot = 2080.f;
	//마
	m_intro[3].m_pos = VEC2(WINSIZEX + 100, 460);
	m_intro[3].m_end.push_back(m_intro[3].m_pos);
	m_intro[3].m_end.push_back(VEC2(WINSIZEX / 2, 460));
	//향
	m_intro[4].m_pos = VEC2(WINSIZEX / 2, -100);
	m_intro[4].m_end.push_back(m_intro[4].m_pos);
	m_intro[4].m_end.push_back(VEC2(WINSIZEX / 2, 580));

	//영어
	m_intro[5].m_pos = VEC2(400, -300);
	m_intro[5].m_end.push_back(m_intro[5].m_pos);
	m_intro[5].m_end.push_back(VEC2(WINSIZEX / 2, WINSIZEY / 2));
	m_intro[5].m_rot = 70;

	//IsEnter 진입했을 때(메뉴판 떳을 때)
	//LEFT_POS
	for (auto& iter : m_intro)
		iter.m_end.push_back(VEC2(330, iter.m_end[INTRO_POS::MID_POS].y));

	//FADE_OUT_POS
	m_intro[0].m_end.push_back(
		VEC2(m_intro[0].m_end[INTRO_POS::LEFT_POS].x, WINSIZEY + 100)
	);
	m_intro[4].m_end.push_back(
		VEC2(m_intro[4].m_end[INTRO_POS::LEFT_POS].x, -100)
	);

	m_intro[1].m_end.push_back(
		VEC2(-100, m_intro[1].m_end[INTRO_POS::LEFT_POS].y)
	);
	m_intro[3].m_end.push_back(
		VEC2(-100, m_intro[3].m_end[INTRO_POS::LEFT_POS].y)
	);

	m_intro[2].m_end.push_back(VEC2(m_intro[2].m_end[INTRO_POS::LEFT_POS]));
	m_intro[5].m_end.push_back(VEC2(m_intro[5].m_end[INTRO_POS::LEFT_POS]));

	//버튼 세팅
	m_buttons.push_back(new cButton("startBT"));
	m_buttons.push_back(new cButton("replayBT"));
	m_buttons.push_back(new cButton("scoreBT"));
	m_buttons.push_back(new cButton("musicBT"));
	m_buttons.push_back(new cButton("optionBT"));
	m_buttons.push_back(new cButton("quitBT"));

	for(int i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(1000 - i * 15, 200 + i * 70));

	m_buttons[m_nowButton]->m_isOn = true;

	//버튼 이어주기
	for (int i = 5; i > 0; i--)
		m_buttons[i]->m_up = m_buttons[i - 1];
	for (int i = 0; i < 5; i++)
		m_buttons[i]->m_down = m_buttons[i + 1];
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
	//게임 프레임
	DEBUG_LOG("%.2f\n", DXUTGetFPS());

	for (auto iter : m_buttons)
		iter->Update();

	//버튼 나타났을 때
	if (isEnter == true) {
		if (KEYDOWN(DIK_UP)) {
			m_buttons[m_nowButton]->m_isOn = false;
			if (m_buttons[m_nowButton]->m_up != nullptr) {
				m_nowButton--;
				m_buttons[m_nowButton]->m_isOn = true;
			}
			else {
				while (m_buttons[m_nowButton]->m_down != nullptr)
					m_nowButton++;
				m_buttons[m_nowButton]->m_isOn = true;
			}
			SOUND->Play("keymoveSND");
		}
		if (KEYDOWN(DIK_DOWN)) {
			m_buttons[m_nowButton]->m_isOn = false;
			if (m_buttons[m_nowButton]->m_down != nullptr) {
				m_nowButton++;
				m_buttons[m_nowButton]->m_isOn = true;
			}
			else {
				while (m_buttons[m_nowButton]->m_up != nullptr)
					m_nowButton--;
				m_buttons[m_nowButton]->m_isOn = true;
			}
			SOUND->Play("keymoveSND");
		}

		//현재 위치의 씬으로 이동하기 전
		if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
			SOUND->Play("selectSND");

			//다시 타이틀 씬으로 돌아왔을 때 인트로가 시작되야 하므로
			isEnter = false;

			isChangeScene = true;
			nowIntroPos = INTRO_POS::FADE_OUT_POS;
		}

		if (KEYDOWN(DIK_ESCAPE) || KEYDOWN(DIK_X)) {
			SOUND->Copy("cancelSND");
			m_buttons[m_nowButton]->m_isOn = false;
			m_nowButton = BUTTON::EXIT;
			m_buttons[m_nowButton]->m_isOn = true;
		}
	}

	//버튼 나올 때 진입하기 전
	if ((KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) && 
		(isEnter == false && isChangeScene == false)
		) {
		SOUND->Play("selectSND");
		nowIntroPos = INTRO_POS::LEFT_POS;
		if (m_alpha > 80) m_alpha = 80;
		isEnter = true;
	}
	
	//버튼 나올 때 살짝 어두워짐
	if (isEnter == true)
		Lerp(m_rgb, 150, 0.04);

	//씬 바꿀 때 페이드아웃
	if (isChangeScene == true) {
		static time_t chkTime = timeGetTime();

		Lerp(m_rgb, 0, 0.08);
		Lerp(m_intro[2].m_alpha, 0, 0.08);
		Lerp(m_intro[5].m_alpha, 0, 0.08);

		if (timeGetTime() - chkTime > 800) {
			isChangeScene = false;
			m_nowButton = 0;
			m_alpha = 255;
			m_rgb = 255;
			INTRO_POS nowIntroPos = INTRO_POS::MID_POS;

			switch (m_nowButton) {
			case BUTTON::START:
				DEBUG_LOG("리플레이는 아직 미구현...\n");
				PostQuitMessage(0);
				//SCENE->ChangeScene("startScene");
				break;
			case BUTTON::REPLAY:
				DEBUG_LOG("리플레이는 아직 미구현...\n");
				PostQuitMessage(0);
				//SCENE->ChangeScene("replayScene");
				break;
			case BUTTON::SCORE:
				DEBUG_LOG("점수는 아직 미구현...\n");
				PostQuitMessage(0);
				//SCENE->ChangeScene("scoreScene");
				break;
			case BUTTON::MUSIC:
				DEBUG_LOG("점수는 아직 미구현...\n");
				PostQuitMessage(0);
				//SCENE->ChangeScene("musicScene");
				break;
			case BUTTON::OPTION:
				SCENE->ChangeScene("optionScene");
				break;
			case BUTTON::EXIT:
				PostQuitMessage(0);
				break;
			}
			return;
		}
	}

	for (int i = 0; i < sizeof(m_intro) / sizeof(m_intro[0]); i++) {
		//각각의 버튼이 시간차에 따라 움직이기 시작함
		if (timeGetTime() - m_intro[i].m_startTime > i * 300.f) {
			D3DXVec2Lerp(&m_intro[i].m_pos, &m_intro[i].m_pos, &m_intro[i].m_end[nowIntroPos], 0.05);
			//씬 바꿀 땐 이렇게 적용시키면 안됨
			if (i == 2 && isChangeScene == false) {
				//홍 글자의 경우엔 점점 나타나면서 회전이 약해짐
				Lerp(m_intro[i].m_alpha, 255, 0.05);
				Lerp(m_intro[i].m_rot, 0.f, 0.03);
			}
		}
	}

	//인트로 페이드 인
	Lerp(m_alpha, 0, 0.01);
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_XRGB(m_rgb, m_rgb, m_rgb, m_rgb));

	for (int i = 0; i < 6; i++)
		IMAGE->Render(m_intro[i].m_img, m_intro[i].m_pos, m_intro[i].m_size, m_intro[i].m_rot, true,
			D3DCOLOR_ARGB(m_intro[i].m_alpha, 255, 255, 255)
		);

	if(isEnter == true)
		for (auto iter : m_buttons)
			iter->Render();

	IMAGE->Render(m_whiteEffect, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_alpha, 255, 255, 255));
}

void cTitleScene::Release()
{
}
