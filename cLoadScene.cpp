#include "DXUT.h"
#include "cTitleScene.h"
#include "cOptionScene.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->InsertImage("loadBG", "resource/scene/loadscene/bg.png");
	m_BG = IMAGE->FindImage("loadBG");
}

cLoadScene::~cLoadScene()
{
	for (auto iter : m_sounds)
		SAFE_DELETE(iter);
	for (auto iter : m_imgs)
		SAFE_DELETE(iter);
}

void cLoadScene::Init()
{
	//�Ҹ� �ε�

	//�������
	for (int i = 1; i < 4; i++) {
		char key[256];
		WCHAR path[256];

		//midi���� �߰�
		sprintf(key, "th_%02d_midi", i);
		wsprintf(path, L"./resource/sound/midi/th06_%02d.wav", i);

		Load(key, path);

		//wav���� �߰�
		sprintf(key, "th_%02d_wav", i);
		wsprintf(path, L"./resource/sound/wav/th06_%02d.wav", i);

		Load(key, path);
	}

	//ȿ���� �߰�
	Load("selectSND", L"./resource/soundeffect/select.wav");
	Load("keymoveSND", L"./resource/soundeffect/keymove.wav");
	Load("cancelSND", L"./resource/soundeffect/cancel.wav");

	//�̹��� �ε�

	//Ÿ��Ʋ �� �̹���
	Load("whiteBG", "./resource/scene/titleScene/whitebg.png");
	Load("titleBG", "./resource/scene/titleScene/bg.png");

	//����ȫ���� The embodiment of devil. ����
	for (int i = 0; i < 6; i++) {
		char key[256], path[256];
		sprintf(key, "title_text_%d", i);
		sprintf(path, "./resource/scene/titleScene/text/%d.png", i);

		Load(key, path);
	}

	//Ÿ��Ʋ �� ��ư
	Load("startBT", "./resource/button/start.png");
	Load("replayBT", "./resource/button/replay.png");
	Load("scoreBT", "./resource/button/score.png");
	Load("musicBT", "./resource/button/musicroom.png");
	Load("optionBT", "./resource/button/option.png");
	Load("quitBT", "./resource/button/quit.png");

	//�ɼ� �� ��ư
	//�� 18����
	Load("0BT", "./resource/button/0.png");
	Load("1BT", "./resource/button/1.png");
	Load("2BT", "./resource/button/2.png");
	Load("3BT", "./resource/button/3.png");
	Load("4BT", "./resource/button/4.png");
	Load("5BT", "./resource/button/5.png");

	Load("lifeBT", "./resource/button/player.png");
	Load("bombBT", "./resource/button/bomb.png");
	Load("bgmBT", "./resource/button/bgm.png");
	Load("wavBT", "./resource/button/wav.png");
	Load("midiBT", "./resource/button/midi.png");
	Load("soundBT", "./resource/button/sound.png");
	Load("modeBT", "./resource/button/mode.png");
	Load("windowBT", "./resource/button/window.png");
	Load("fullBT", "./resource/button/full.png");
	Load("restoreBT", "./resource/button/restore.png");
	Load("onBT", "./resource/button/on.png");
	Load("offBT", "./resource/button/off.png");
}

void cLoadScene::Update()
{
	//�Ҹ�
	if (m_nowLoad[0] < m_sounds.size()) {
		int& idx = m_nowLoad[0];
		SOUND->AddSound(m_sounds[idx]->m_idx1, m_sounds[idx]->m_idx2);
		idx++;
	}

	//�̹���
	if (m_nowLoad[1] < m_imgs.size()) {
		int& idx = m_nowLoad[1];
		IMAGE->InsertImage(m_imgs[idx]->m_idx1, m_imgs[idx]->m_idx2);
		idx++;
	}

	//�� �߰� (���� �ε��� �� ���� ���� ����)
	if (m_nowLoad[0] == m_sounds.size() &&
		m_nowLoad[1] == m_imgs.size()
		) {
		SCENE->AddScene("titleScene", new cTitleScene);
		SCENE->AddScene("optionScene", new cOptionScene);

		SCENE->ChangeScene("titleScene");
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0));
}

void cLoadScene::Release()
{
}