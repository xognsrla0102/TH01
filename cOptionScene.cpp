#include "DXUT.h"
#include "cButton.h"
#include "cOptionScene.h"

cOptionScene::cOptionScene()
{
	m_BG = IMAGE->FindImage("titleBG");

	//BGM������ ��ư��
	m_buttons.push_back(new cButton("bgmBT"));
	m_buttons.push_back(new cButton("onBT"));
	m_buttons.push_back(new cButton("offBT"));

	//��ġ ����
	for (int i = 0; i < 3; i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 150, 200));

	//���ο� ���� �߰�
	m_manyButtons.push_back(m_buttons);

	//�� �迭�� ���� �� ���� �����Ƿ� ��� �����ֱ�
	//������ �����ߴ� ��ư �޸𸮵��� m_manyButtons���� �Ű���
	m_buttons.clear();

	//SOUND������ ��ư��
	m_buttons.push_back(new cButton("soundBT"));
	m_buttons.push_back(new cButton("onBT"));
	m_buttons.push_back(new cButton("offBT"));

	for (int i = 0; i < 3; i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 150, 300));

	
	m_manyButtons.push_back(m_buttons);

	m_buttons.clear();

	//QUIT��ư
	m_buttons.push_back(new cButton("quitBT"));
	m_buttons[0]->SetPos(VEC2(300, 400));

	m_manyButtons.push_back(m_buttons);

	m_buttons.clear();

	m_manyButtons[m_nowLine][m_nowButton]->m_isOn = true;

	//��ư �̾��ֱ�

	//0��° ���� ��ư
	for (int i = 2; i > 1; i--)
		m_manyButtons[0][i]->m_left = m_manyButtons[0][i - 1];
	for (int i = 1; i < 2; i++)
		m_manyButtons[0][i]->m_right = m_manyButtons[0][i + 1];

	//1��° ���� ��ư
	for (int i = 2; i > 1; i--)
		m_manyButtons[1][i]->m_left = m_manyButtons[1][i - 1];
	for (int i = 1; i < 2; i++)
		m_manyButtons[1][i]->m_right = m_manyButtons[1][i + 1];

	//0 ~ 1��° ���� ��ư
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
