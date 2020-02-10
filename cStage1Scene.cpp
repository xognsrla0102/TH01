#include "DXUT.h"
#include "cPlayer.h"
#include "cBulletAdmin.h"
#include "cPlayerBullet.h"
#include "cStage1Scene.h"

cStage1Scene::cStage1Scene()
{
	m_ui = IMAGE->FindImage("ingame_ui");
}

cStage1Scene::~cStage1Scene()
{
}

void cStage1Scene::Init()
{
	SOUND->Play("th_02_%s", true, true);
	OBJFIND(PLAYER)->SetPos(VEC2(WINSIZEX / 2, 650));
}

void cStage1Scene::Update()
{
	if (KEYDOWN(DIK_ESCAPE)) {
		SOUND->Stop("th_02_%s");
		SCENE->ChangeScene("titleScene");
	}

	OBJFIND(PLAYER)->Update();
	auto& pBullet = ((cBulletAdmin*)(OBJFIND(BULLET)))->GetPlayerBullet();
	for (auto iter : pBullet)
		iter->Update();
	OBJFIND(BULLET)->Update();
}

void cStage1Scene::Render()
{
	auto& pBullet = ((cBulletAdmin*)(OBJFIND(BULLET)))->GetPlayerBullet();
	for (auto iter : pBullet) {
		iter->Render();
		iter->OutMapChk();
	}
	OBJFIND(PLAYER)->Render();

	IMAGE->ReBegin(true);
	IMAGE->Render(m_ui, VEC2(0, 0), 1.f);
	IMAGE->ReBegin(false);
}

void cStage1Scene::Release()
{
}
