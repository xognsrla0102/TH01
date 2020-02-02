#include "DXUT.h"
#include "cTitleScene.h"
#include "cStartScene.h"
#include "cHowtoScene.h"
#include "cMusicScene.h"
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
	//���� �ε�

	//������ ���� ��� ������ ������ ������ ���丮 ����� ���� ������
	if (FILEMANAGER->MakeDir("./gameInfo"))
		FILEMANAGER->OptionSave();
	//������ ��������
	else {
		//������ ���� �� �����Ŀ� ������ �����Ƿ� ���� ��ȯ ���������
		FILEMANAGER->OptionLoad();
		//����Ʈ ������ ��尡 â���(isWindowed = true)�̹Ƿ�
		//������ �޾��� �� ��üȭ���� ��쿡�� ��ȯ�����ְ�
		//â����� ���� ���� ó�������� �ʿ䰡 ����
		if (isWindowed != true) {
			DXUTPause(true, true);
			DXUTToggleFullScreen();
			DXUTPause(false, false);
		}
	}

	//�Ҹ� �ε�

	//�������
	for (size_t i = 1; i <= 4; i++) {
		char key[256];
		WCHAR path[256];

		//midi���� �߰�
		sprintf(key, "th_%02d_midi", i);
		wsprintf(path, L"./resource/music/midi/th06_%02d.wav", i);

		Load(key, path);

		//wav���� �߰�
		sprintf(key, "th_%02d_wav", i);
		wsprintf(path, L"./resource/music/wav/th06_%02d.wav", i);

		Load(key, path);
	}

	//ȿ���� �߰�
	Load("selectSND", L"./resource/sound/select.wav");
	Load("keymoveSND", L"./resource/sound/keymove.wav");
	Load("cancelSND", L"./resource/sound/cancel.wav");

	//�̹��� �ε�

	//���� �̹��� �ε�
	for (size_t i = 0; i < 10; i++) {
		char key[256], path[256];
		sprintf(key, "num_%d", i);
		sprintf(path, "./resource/number/%d.png", i);

		Load(key, path);
	}
	Load("num_dot", "./resource/number/dot.png");

	//Ÿ��Ʋ �� �̹���
	Load("whiteBG", "./resource/scene/titleScene/whitebg.png");
	Load("titleBG", "./resource/scene/titleScene/bg.png");

	//����ȫ���� The embodiment of devil. ����
	for (size_t i = 0; i < 6; i++) {
		char key[256], path[256];
		sprintf(key, "title_text_%d", i);
		sprintf(path, "./resource/scene/titleScene/text/%d.png", i);

		Load(key, path);
	}

	//��ŸƮ �� �̹���
	Load("startBG", "./resource/scene/startScene/bg.png");
	Load("startSELECT_MODE", "./resource/scene/startScene/selectMode.png");
	Load("startSELECT_CHARACTER", "./resource/scene/startScene/selectMode.png");
	Load("startSELECT_WEAPON", "./resource/scene/startScene/selectWeapon.png");

	//�Ͽ��� �� �̹���
	for (size_t i = 0; i < 12; i++) {
		char key[256], path[256];
		sprintf(key, "howto_%d", i);
		sprintf(path, "./resource/scene/howtoScene/%d.png", i);

		Load(key, path);
	}

	//���� �� �� �̹���
	Load("musicBG", "./resource/scene/musicScene/bg.png");
	for (size_t i = 1; i <= 4; i++) {
		char key[256], path[256];
		sprintf(key, "music_th%d", i);
		sprintf(path, "./resource/scene/musicScene/%d.png", i);
		Load(key, path);
	}

	//�ɼ� �� �̹���
	Load("optionBG", "./resource/scene/optionScene/bg.png");

	//Ÿ��Ʋ �� ��ư
	Load("startBT", "./resource/button/start.png");
	Load("howtoBT", "./resource/button/howto.png");
	Load("replayBT", "./resource/button/replay.png");
	Load("scoreBT", "./resource/button/score.png");
	Load("musicBT", "./resource/button/musicroom.png");
	Load("optionBT", "./resource/button/option.png");
	Load("quitBT", "./resource/button/quit.png");

	//��ŸƮ �� ��ư
	Load("lunaticBT", "./resource/scene/startScene/lunatic.png");
	Load("extraBT", "./resource/scene/startScene/extra.png");

	//���� �� �� ��ư
	Load("th01BT", "./resource/button/th01.png");
	Load("th02BT", "./resource/button/th02.png");
	Load("th03BT", "./resource/button/th03.png");
	Load("th04BT", "./resource/button/th04.png");

	//�ɼ� �� ��ư
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
		SCENE->AddScene("startScene", new cStartScene);
		SCENE->AddScene("howtoScene", new cHowtoScene);
		SCENE->AddScene("musicScene", new cMusicScene);
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