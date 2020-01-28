#include "DXUT.h"
#include "cButton.h"
#include "cMusicScene.h"

cMusicScene::cMusicScene()
{
	m_bg = IMAGE->FindImage("musicBG");

	for (size_t i = 1; i <= 4; i++) {
		char key[256], path[256];
		sprintf(key, "music_th%d", i);
		m_comments.push_back(IMAGE->FindImage(key));
	}

	m_buttons.push_back(new cButton("th01BT", VEC2(1.f, 1.f), 0.1f));
	m_buttons.push_back(new cButton("th02BT", VEC2(1.f, 1.f), 0.1f));
	m_buttons.push_back(new cButton("th03BT", VEC2(1.f, 1.f), 0.1f));
	m_buttons.push_back(new cButton("th04BT", VEC2(1.f, 1.f), 0.1f));

	for (size_t i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->SetPos(VEC2(350, 150 + 80 * i));
		if (i == m_buttons.size() - 1)
			m_buttons[i]->SetPos(VEC2(400, 150 + 80 * i));
	}

	m_buttons[0]->m_isOn = true;

	for (size_t i = 0; i < m_buttons.size(); i++) {
		char name[256];
		sprintf(name, "th_%02d_", i + 1);

		//i°¡ 0ÀÌ¸é
		//result = "th_01_%s";
		string result = name + ((string)("%s"));

		m_musicNames.push_back(result);
	}
}

cMusicScene::~cMusicScene()
{
	for (auto iter : m_buttons)
		SAFE_DELETE(iter);
}

void cMusicScene::Init()
{
	m_rgb = 0;
	m_nowLine = 0;
	m_buttons[0]->m_isOn = true;

	m_nowPlayMusic = 0;
}

void cMusicScene::Update()
{
	for (auto iter : m_buttons)
		iter->Update();

	if (KEYDOWN(DIK_UP) || KEYDOWN(DIK_DOWN)) {
		SOUND->Play("keymoveSND");
		m_buttons[m_nowLine]->m_isOn = false;
		if (KEYDOWN(DIK_DOWN)) {
			if (m_nowLine < m_buttons.size() - 1)
				m_nowLine++;
			else
				m_nowLine = 0;
		}
		if (KEYDOWN(DIK_UP)) {
			if (m_nowLine > 0)
				m_nowLine--;
			else
				m_nowLine = m_buttons.size() - 1;
		}
		m_buttons[m_nowLine]->m_isOn = true;
	}

	if (KEYDOWN(DIK_RETURN)) {
		SOUND->Play("selectSND");
		SOUND->Stop(m_musicNames[m_nowPlayMusic]);
		m_nowPlayMusic = m_nowLine;
		SOUND->Play(m_musicNames[m_nowPlayMusic], true, true);
	}

	if (KEYDOWN(DIK_X) || KEYDOWN(DIK_ESCAPE)) {
		SOUND->Copy("cancelSND");

		SOUND->Stop(m_musicNames[m_nowPlayMusic]);
		m_buttons[m_nowLine]->m_isOn = false;

		SCENE->ChangeScene("titleScene");
	}

	Lerp<int>(m_rgb, 255, 0.05);
}

void cMusicScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb));
	IMAGE->Render(m_comments[m_nowPlayMusic], VEC2(300, 480));

	for (auto iter : m_buttons)
		iter->Render();

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cMusicScene::Release()
{
}
