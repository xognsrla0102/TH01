#include "DXUT.h"
#include "cTexture.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->InsertImage("loadBG", "resource/Scene/LoadScene/bg.png");
	m_BG = IMAGE->FindImage("loadBG");
}

cLoadScene::~cLoadScene()
{
	for (auto iter : m_datas)
		SAFE_DELETE(iter.second);
	m_datas.clear();
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
	SAFE_DELETE(m_BG);
}
