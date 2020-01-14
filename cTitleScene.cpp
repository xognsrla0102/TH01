#include "DXUT.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
	LOADSND(DXUTGetHWND(), L"./resource/bgm/title.wav");

	m_whiteEffect = IMAGE->FindImage("whiteBG");
	m_bg = IMAGE->FindImage("titleBG");
} 

cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
}

void cTitleScene::Update()
{
	static VEC2 alphaVec(255, 0);
	D3DXVec2Lerp(&alphaVec, &alphaVec, &VEC2(0, 0), 0.01f);
	m_alpha = alphaVec.x;
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0));
	IMAGE->Render(m_whiteEffect, VEC2(0, 0), 1.f, 0.f, D3DCOLOR_ARGB(m_alpha, 255, 255, 255));
}

void cTitleScene::Release()
{
}
