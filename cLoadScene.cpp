#include "DXUT.h"
#include "cTexture.h"
#include "cPlayer.h"
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
}

void cLoadScene::Update()
{
}

void cLoadScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0));
}

void cLoadScene::Release()
{
}