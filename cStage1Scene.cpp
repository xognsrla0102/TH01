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

	m_name = IMAGE->FindImage("ingame_name");
	m_musicName = IMAGE->FindImage("ingame_music");

	m_title = IMAGE->FindImage("ingame_title");
	m_circle = IMAGE->FindImage("ingame_circle");
}

cStage1Scene::~cStage1Scene()
{
	Release();
}

void cStage1Scene::Init()
{
	SOUND->Play("th_02_%s", TRUE, TRUE);

	m_startTime = timeGetTime();

	((cBalls*)OBJFIND(BALLS))->Release();
	((cPlayer*)OBJFIND(PLAYER))->Release();
	((cPlayer*)OBJFIND(PLAYER))->Init();

	((cBulletAdmin*)OBJFIND(BULLETS))->Release();

	playerLife = stoi(FILEMANAGER->ReadFile("./gameInfo/LifeInfo.txt"));
	playerBomb = stoi(FILEMANAGER->ReadFile("./gameInfo/BombInfo.txt"));

	//ui내에 있는 게임 플레이 공간은
	//745 X 620 이고 시작 위치는 50,50에서 795, 670 까지임
	VEC2 playerPos = VEC2(50 + INGAMEX / 2, 50 + INGAMEY - 100);
	OBJFIND(PLAYER)->SetPos(playerPos);

	m_name->m_a = 0.f;
	m_name->SetNowRGB();

	m_musicName->m_a = 0.f;
	m_musicName->SetNowRGB();

	m_title->m_a = 0.f;
	m_title->SetNowRGB();
	
	m_circle->m_a = 0.f;
	m_circle->m_rot = -1000.f;
	m_circle->SetNowRGB();

	m_img1Pos = m_img2Pos = VEC2(50, 0);

	m_mobSpawn.push_back(new cTimer(300));
	m_mobSpawn.push_back(new cTimer(0));
}

void cStage1Scene::Update()
{
	//if (OBJFIND(PLAYER)->GetLive() == FALSE){
		//SCENE->ChangeScene("gameoverScene");
		//return;
	//}

	if (KEYDOWN(DIK_ESCAPE)) {
		SCENE->ChangeScene("titleScene");
		return;
	}

	ScroolMap();
	LevelDesign();

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

	IMAGE->ReBegin(TRUE);
	IMAGE->Render(m_black, VEC2(50, 50), 1.2f);
	IMAGE->ReBegin(FALSE);

	OBJFIND(ENEMYS)->Render();

	OBJFIND(PLAYER)->Render();
	OBJFIND(BALLS)->Render();
	OBJFIND(BULLETS)->Render();

	EFFECT->Render();

	//UI 출력
	IMAGE->ReBegin(TRUE);

	if (timeGetTime() - m_startTime < 8000) {
		IMAGE->Render(m_name, VEC2(50 + INGAMEX / 2, 50 + 250), 1.f, 0.f, TRUE, m_name->m_color);
		IMAGE->Render(m_musicName, VEC2(50 + INGAMEX - 120, 50 + INGAMEY - 20), 1.f, 0.f, TRUE, m_musicName->m_color);
	}

	IMAGE->Render(m_ui, VEC2(0, 0), 1.f);

	IMAGE->Render(m_circle, VEC2(50 + INGAMEX + 150, 50 + INGAMEY - 130), 1.f, m_circle->m_rot, TRUE, m_circle->m_color);
	IMAGE->Render(m_title, VEC2(50 + INGAMEX + 150, 50 + INGAMEY - 130), 1.f, 0.f, TRUE, m_title->m_color);

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
	IMAGE->ReBegin(FALSE);
}

void cStage1Scene::Release()
{
	SOUND->Stop("th_02_%s");
	((cPlayer*)OBJFIND(PLAYER))->m_hasBall = FALSE;

	for (auto iter : m_mobSpawn)
		SAFE_DELETE(iter);
	m_mobSpawn.clear();

	((cBalls*)OBJFIND(BALLS))->Release();
	((cEnemyAdmin*)OBJFIND(ENEMYS))->Release();
	((cBulletAdmin*)OBJFIND(BULLETS))->Release();
	EFFECT->Reset();
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

	if (nowTime < 8000) {
		Lerp(m_title->m_a, 255.f, 0.02);
		Lerp(m_circle->m_a, 255.f, 0.02);
		Lerp(m_circle->m_rot, 0.f, 0.01);

		if (nowTime > 1000 && nowTime < 5000) {
			Lerp(m_name->m_a, 255.f, 0.02);
			Lerp(m_musicName->m_a, 255.f, 0.02);
		}
		else if (nowTime > 5000 && nowTime < 8000) {
			Lerp(m_name->m_a, 0.f, 0.04);
			Lerp(m_musicName->m_a, 0.f, 0.04);
		}
		m_name->SetNowRGB();
		m_musicName->SetNowRGB();
		m_title->SetNowRGB();
		m_circle->SetNowRGB();
	}

	if (nowTime > 5000 && nowTime < 12000) {
		if (m_mobSpawn[0]->Update()) {
			auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
			one.push_back(new cOne(2, 1, VEC2(50, 200)));
			INT idx = one.size() - 1;
			cOne* nowOne = ((cOne*)(one[idx]));
			nowOne->m_theta = 15;
			nowOne->m_bulletCnt = 8;
			nowOne->SetDelay(500 + rand() % 21 * 10);
			nowOne->SetSpeed(70);

			one.push_back(new cOne(2, 2, VEC2(50 + INGAMEX, 200)));
			idx = one.size() - 1;
			nowOne = ((cOne*)(one[idx]));
			nowOne->m_theta = 15;
			nowOne->m_bulletCnt = 8;
			nowOne->SetDelay(500 + rand() % 21 * 10);
			nowOne->SetSpeed(70);
		}
	}

	else if (nowTime > 15000 && nowTime < 15020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		for (size_t i = 1; i <= 3; i++) {
			fairy.push_back(new cFairy(10, FAIRY_RED, 1, VEC2(50 + INGAMEX / 4 * i, 0)));
			INT idx = fairy.size() - 1;
			cFairy* nowFairy = ((cFairy*)(fairy[idx]));

			nowFairy->m_path = new cPath(nowFairy->GetPos());
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 100), 0.03, 0);
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 100), 0, 1000);
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y - 100), 0.02, 0);
			nowFairy->m_circleCnt = 10;
			nowFairy->SetDelay(300);
			nowFairy->SetSpeed(500.f);
		}
	}

	else if (nowTime > 20000 && nowTime < 20020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		fairy.push_back(new cFairy(30, FAIRY_BLUE, 1, VEC2(50 + INGAMEX / 2, 0)));
		INT idx = fairy.size() - 1;
		cFairy* nowFairy = ((cFairy*)(fairy[idx]));

		nowFairy->m_path = new cPath(nowFairy->GetPos());
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0.03, 0);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0, 1000);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y - 100), 0.02, 0);
		nowFairy->m_circleCnt = 10;
		nowFairy->SetDelay(200);
		nowFairy->SetSpeed(300.f);
		nowFairy->m_isRandShot = TRUE;
		nowFairy->m_isAccel = TRUE;
	}

	else if (nowTime > 25000 && nowTime < 25020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		fairy.push_back(new cFairy(100, FAIRY_BLUE, 2, VEC2(50 + INGAMEX / 2, 0)));
		INT idx = fairy.size() - 1;
		cFairy* nowFairy = ((cFairy*)(fairy[idx]));

		nowFairy->m_path = new cPath(nowFairy->GetPos());
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0.03, 0);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0, 3000);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y - 100), 0.02, 0);
		nowFairy->SetDelay(50);
		nowFairy->SetSpeed(250.f);
		nowFairy->m_isAccel = TRUE;
	}

	//10분이 되면 게임종료
	else if (nowTime > 600000) {
		//클리어시엔 엑스트라 개방
		isExtra = TRUE;
		SCENE->ChangeScene("titleScene");
	}
}
