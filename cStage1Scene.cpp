#include "DXUT.h"
#include "cPlayer.h"
#include "cBall.h"
#include "cBalls.h"
#include "cBulletAdmin.h"
#include "cPlayerBullet.h"
#include "cStage1Scene.h"

cStage1Scene::cStage1Scene()
{
	m_ui = IMAGE->FindImage("ingame_ui");
	m_life = IMAGE->FindImage("ingame_life");
	m_bomb = IMAGE->FindImage("ingame_bomb");
}

cStage1Scene::~cStage1Scene()
{
}

void cStage1Scene::Init()
{
	SOUND->Play("th_02_%s", true, true);

	((cBalls*)OBJFIND(BALLS))->Release();
	((cPlayer*)OBJFIND(PLAYER))->Release();
	((cPlayer*)OBJFIND(PLAYER))->Init();
	((cBulletAdmin*)OBJFIND(BULLETS))->Release();

	playerLife = stoi(FILEMANAGER->ReadFile("./gameInfo/LifeInfo.txt"));
	playerBomb = stoi(FILEMANAGER->ReadFile("./gameInfo/BombInfo.txt"));

	//ui내에 있는 게임 플레이 공간은
	//745 X 620 이고 시작 위치는 50,50에서 795, 670 까지임
	VEC2 playerPos = VEC2(50 + INGAMEX / 2, 50 + INGAMEY / 2);

	OBJFIND(PLAYER)->SetPos(playerPos);
}

void cStage1Scene::Update()
{
	if (KEYDOWN(DIK_ESCAPE)) {
		SOUND->Stop("th_02_%s");
		((cPlayer*)OBJFIND(PLAYER))->m_hasBall = false;
		SCENE->ChangeScene("titleScene");
		return;
	}

	OBJFIND(PLAYER)->Update();
	OBJFIND(BALLS)->Update();

	auto& pBullet = ((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet();
	auto& bBullet = ((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet();
	for (auto iter : pBullet) {
		iter->Update();
		iter->OutMapChk();
	}
	for (auto iter : bBullet) {
		iter->Update();
		iter->OutMapChk();
	}

	OBJFIND(BULLETS)->Update();
}

void cStage1Scene::Render()
{
	auto& pBullet = ((cBulletAdmin*)(OBJFIND(BULLETS)))->GetPlayerBullet();
	auto& bBullet = ((cBulletAdmin*)(OBJFIND(BULLETS)))->GetBallBullet();

	for (auto iter : pBullet)
		iter->Render();
	for (auto iter : bBullet)
		iter->Render();

	OBJFIND(PLAYER)->Render();
	OBJFIND(BALLS)->Render();

	//UI 출력
	IMAGE->ReBegin(true);
	IMAGE->Render(m_ui, VEC2(0, 0), 1.f);

	for (size_t i = 0; i < playerLife; i++)
		IMAGE->Render(m_life, VEC2(880 + i * 25, 200), 1.f);
	for(size_t i = 0; i < playerBomb; i++)
		IMAGE->Render(m_bomb, VEC2(880 + i * 25, 235), 1.f);

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
	IMAGE->ReBegin(false);
}

void cStage1Scene::Release()
{
	((cBalls*)OBJFIND(BALLS))->Release();
}
