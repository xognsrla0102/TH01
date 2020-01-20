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

	//�̹��� �ε�

	//Ÿ��Ʋ �� �̹���
	string key, path;

	key = "whiteBG", path = "resource/scene/titleScene/whitebg.png";
	Load(key, path);
	key = "titleBG", path = "resource/scene/titleScene/bg.png";
	Load(key, path);

	for (int i = 0; i < 6; i++) {
		char key[256], path[256];
		sprintf(key, "title_text_%d", i);
		sprintf(path, "resource/scene/titleScene/text/%d.png", i);

		Load(key, path);
	}

	//Ÿ��Ʋ �� ��ư
	for (int i = 0; i < 6; i++) {
		char key[256], path[256];
		sprintf(key, "title_bt_%d", i);
		sprintf(path, "resource/button/%d.png", i);

		Load(key, path);
	}
}

void cLoadScene::Update()
{
	if (m_nowLoad[0] < m_sounds.size()) {
		int& idx = m_nowLoad[0];
		SOUND->AddSound(m_sounds[idx]->m_idx1, m_sounds[idx]->m_idx2);
		idx++;
	}
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