#include "DXUT.h"
#include "cTitleScene.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->InsertImage("loadBG", "resource/scene/loadscene/bg.png");

	m_BG = IMAGE->FindImage("loadBG");
}

cLoadScene::~cLoadScene()
{
	for (auto iter : m_datas)
		SAFE_DELETE(iter.second);
}

void cLoadScene::Init()
{
	//소리 로딩
	SOUND->AddSound("titleBGM", L"./resource/bgm/title.wav");

	//이미지 로딩
	IMAGE->InsertImage("whiteBG", "resource/scene/titleScene/whitebg.png");
	IMAGE->InsertImage("titleBG", "resource/scene/titleScene/bg.png");

	//씬 생성
	SCENE->AddScene("titleScene", new cTitleScene);
}

void cLoadScene::Update()
{
	SOUND->Play("titleBGM", true);
	SCENE->ChangeScene("titleScene");
}

void cLoadScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0));
}

void cLoadScene::Release()
{
}