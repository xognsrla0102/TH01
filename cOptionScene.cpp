#include "DXUT.h"
#include "cButton.h"
#include "cOptionScene.h"

cOptionScene::cOptionScene()
{
	m_BG = IMAGE->FindImage("titleBG");

	//BGM라인의 버튼들
	m_buttons.push_back(new cButton("bgmBT"));
	m_buttons.push_back(new cButton("onBT"));
	m_buttons.push_back(new cButton("offBT"));

	//위치 설정
	for (int i = 0; i < 3; i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 150, 200));

	//새로운 라인 추가
	m_manyButtons.push_back(m_buttons);

	//이 배열은 이제 쓸 일이 없으므로 요소 없애주기
	//이전에 저장했던 버튼 메모리들은 m_manyButtons으로 옮겨짐
	m_buttons.clear();

	//SOUND라인의 버튼들
	m_buttons.push_back(new cButton("soundBT"));
	m_buttons.push_back(new cButton("onBT"));
	m_buttons.push_back(new cButton("offBT"));

	for (int i = 0; i < 3; i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 150, 300));

	
	m_manyButtons.push_back(m_buttons);

	m_buttons.clear();

	//QUIT버튼
	m_buttons.push_back(new cButton("quitBT"));
	m_buttons[0]->SetPos(VEC2(300, 400));

	m_manyButtons.push_back(m_buttons);

	m_buttons.clear();

	m_manyButtons[m_nowLine][m_nowButton]->m_isOn = true;

	//버튼 이어주기

	//0번째 라인 버튼
	for (int i = 2; i > 1; i--)
		m_manyButtons[0][i]->m_left = m_manyButtons[0][i - 1];
	for (int i = 1; i < 2; i++)
		m_manyButtons[0][i]->m_right = m_manyButtons[0][i + 1];

	//1번째 라인 버튼
	for (int i = 2; i > 1; i--)
		m_manyButtons[1][i]->m_left = m_manyButtons[1][i - 1];
	for (int i = 1; i < 2; i++)
		m_manyButtons[1][i]->m_right = m_manyButtons[1][i + 1];

	//0 ~ 1번째 라인 버튼
	for (int i = 0; i < 3; i++)
		m_manyButtons[0][i]->m_down = m_manyButtons[1][1];
	for (int i = 0; i < 3; i++) {
		m_manyButtons[1][i]->m_up = m_manyButtons[0][1];
		m_manyButtons[1][i]->m_down = m_manyButtons[2][0];
	}

	m_manyButtons[2][0]->m_up = m_manyButtons[1][1];

	m_buttons.clear();
}

cOptionScene::~cOptionScene()
{
	for (auto iter : m_manyButtons)
		for (auto jter : iter)
			SAFE_DELETE(jter);
}

void cOptionScene::Init()
{
}

void cOptionScene::Update()
{
	for (auto iter : m_manyButtons)
		for(auto jter : iter)
			jter->Update();

	if (KEYDOWN(DIK_UP)) {
		SOUND->Play("keymoveSND");
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = false;
		if (m_manyButtons[m_nowLine][m_nowButton]->m_up != nullptr) {
			m_nowLine--;
			m_nowButton = 1;
		}
		else {
			while (m_manyButtons[m_nowLine][m_nowButton]->m_down != nullptr) {
				m_nowLine++;
				if (m_nowLine != 0) m_nowButton = 1;
				else m_nowButton = 0;
			}
		}
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = true;
	}
	if (KEYDOWN(DIK_DOWN)) {
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = false;
		if (m_manyButtons[m_nowLine][m_nowButton]->m_down != nullptr) {
			m_nowLine++;
			
			if (m_nowLine != 2) m_nowButton = 1;
			else m_nowButton = 0;
		}
		else {
			while (m_manyButtons[m_nowLine][m_nowButton]->m_up != nullptr) {
				m_nowLine--;
				m_nowButton = 1;
			}
		}
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = true;
		SOUND->Play("keymoveSND");
	}
	if (KEYDOWN(DIK_LEFT)) {
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = false;
		if (m_manyButtons[m_nowLine][m_nowButton]->m_left != nullptr)
			m_nowButton--;
		else
			while (m_manyButtons[m_nowLine][m_nowButton]->m_right != nullptr)
				m_nowButton++;
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = true;
		SOUND->Play("keymoveSND");
	}
	if (KEYDOWN(DIK_RIGHT)) {
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = false;
		if (m_manyButtons[m_nowLine][m_nowButton]->m_right != nullptr)
			m_nowButton++;
		else
			while (m_manyButtons[m_nowLine][m_nowButton]->m_left != nullptr)
				m_nowButton--;
		m_manyButtons[m_nowLine][m_nowButton]->m_isOn = true;
		SOUND->Play("keymoveSND");
	}

	if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
		SOUND->Play("selectSND");
	}

	if (KEYDOWN(DIK_ESCAPE) || KEYDOWN(DIK_X)) {
		SOUND->Copy("cancelSND");
	}

	Lerp<int>(m_rgb, 255, 0.05);
}

void cOptionScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb));

	for (auto iter : m_manyButtons)
		for(auto jter : iter)
			jter->Render();
}

void cOptionScene::Release()
{
}
