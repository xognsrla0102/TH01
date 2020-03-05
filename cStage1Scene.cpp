#include "DXUT.h"

#include "cTimer.h"

#include "cPlayer.h"

#include "cBall.h"
#include "cBalls.h"

#include "cOne.h"
#include "cFairy.h"

#include "cBullet.h"
#include "cBulletAdmin.h"

#include "cEnemy.h"
#include "cEnemyAdmin.h"

#include "cStage1Scene.h"

cStage1Scene::cStage1Scene()
{
	m_ui = IMAGE->FindImage("ingame_ui");
	m_life = IMAGE->FindImage("ingame_life");
	m_bomb = IMAGE->FindImage("ingame_bomb");

	m_img = m_img2 = IMAGE->FindImage("ingame_bg");

	m_black = IMAGE->FindImage("ingame_black");
}

cStage1Scene::~cStage1Scene()
{
	Release();
}

void cStage1Scene::Init()
{
	SOUND->Play("th_02_%s", true, true);

	m_startTime = timeGetTime();

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

	m_img1Pos = m_img2Pos = VEC2(50, 0);

	m_mobSpawn.push_back(new cTimer(300));
}

void cStage1Scene::Update()
{
	ScroolMap();

	if (KEYDOWN(DIK_ESCAPE)) {
		SCENE->ChangeScene("titleScene");
		return;
	}

	EFFECT->Update();

	OBJFIND(PLAYER)->Update();
	OBJFIND(BALLS)->Update();
	OBJFIND(ENEMYS)->Update();
	OBJFIND(BULLETS)->Update();
}

void cStage1Scene::Render()
{
	IMAGE->Render(m_img, m_img1Pos, 1.f);
	IMAGE->Render(m_img2, m_img2Pos, 1.f);

	IMAGE->ReBegin(true);
	IMAGE->Render(m_black, VEC2(50, 50), 1.2f);
	IMAGE->ReBegin(false);

	OBJFIND(ENEMYS)->Render();

	OBJFIND(PLAYER)->Render();
	OBJFIND(BALLS)->Render();
	OBJFIND(BULLETS)->Render();

	LevelDesign();
	EFFECT->Render();

	//UI 출력
	IMAGE->ReBegin(true);
	IMAGE->Render(m_ui, VEC2(0, 0), 1.f);

	for (size_t i = 0; i < ((cPlayer*)OBJFIND(PLAYER))->m_life; i++)
		IMAGE->Render(m_life, VEC2(880 + i * 25, 200), 1.f);
	for(size_t i = 0; i < ((cPlayer*)OBJFIND(PLAYER))->m_bomb; i++)
		IMAGE->Render(m_bomb, VEC2(880 + i * 25, 235), 1.f);

	char scoreText[256];
	
	((cPlayer*)OBJFIND(PLAYER))->m_score = timeGetTime() - m_startTime;
	float score = ((cPlayer*)OBJFIND(PLAYER))->m_score;
	sprintf(scoreText, "%09d", (int)score);
	DRAW_NUM(string(scoreText), VEC2(880, 137));

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
	IMAGE->ReBegin(false);
}

void cStage1Scene::Release()
{
	SOUND->Stop("th_02_%s");
	((cPlayer*)OBJFIND(PLAYER))->m_hasBall = false;

	for (auto iter : m_mobSpawn)
		SAFE_DELETE(iter);
	m_mobSpawn.clear();

	((cBalls*)OBJFIND(BALLS))->Release();
	((cEnemyAdmin*)OBJFIND(ENEMYS))->Release();
	((cBulletAdmin*)OBJFIND(BULLETS))->Release();
}

void cStage1Scene::ScroolMap()
{
	//맵 스크롤
	m_scrool += 100.f * D_TIME;
	m_img1Pos.y = 50 + (int)m_scrool % m_img->m_info.Height;
	m_img2Pos.y = m_img1Pos.y - m_img->m_info.Height;
}

void cStage1Scene::LevelDesign()
{
	int nowTime = timeGetTime() - m_startTime;

	if (nowTime > 500 && nowTime < 5000) {
		if (m_mobSpawn[0]->Update()) {
			((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne().push_back(
				new cOne(2, 1, VEC2(50, 200))
			);
		}
	}
	else if (nowTime > 5000 && nowTime < 10000) {
		if (m_mobSpawn[0]->Update()) {
			((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne().push_back(
				new cOne(2, 2, VEC2(50 + INGAMEX, 200))
			);
		}
	}
	else if (nowTime > 10000 && nowTime < 15000) {
		if (m_mobSpawn[0]->Update()) {
			((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy().push_back(
				new cFairy(2, FAIRY_BLUE, 1, VEC2(50 + INGAMEX, 300))
			);
		}
	}
	else if (nowTime > 600000) {
	//10분 타이머가 다되면 게임 자동종료(?)
		SCENE->ChangeScene("titleScene");
	}
}
