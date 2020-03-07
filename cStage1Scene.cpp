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

	//ui���� �ִ� ���� �÷��� ������
	//745 X 620 �̰� ���� ��ġ�� 50,50���� 795, 670 ������
	VEC2 playerPos = VEC2(50 + INGAMEX / 2, 50 + INGAMEY - 100);
	OBJFIND(PLAYER)->SetPos(playerPos);

	m_img1Pos = m_img2Pos = VEC2(50, 0);

	m_mobSpawn.push_back(new cTimer(300));
	m_mobSpawn.push_back(new cTimer(0));
}

void cStage1Scene::Update()
{
	//if (OBJFIND(PLAYER)->GetLive() == FALSE)
		//SCENE->ChangeScene("gameoverScene");

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

	//UI ���
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
	EFFECT->Reset();
}

void cStage1Scene::ScroolMap()
{
	//�� ��ũ��
	m_scrool += 100.f * D_TIME;
	m_img1Pos.y = 50 + (int)m_scrool % m_img->m_info.Height;
	m_img2Pos.y = m_img1Pos.y - m_img->m_info.Height;
}

void cStage1Scene::LevelDesign()
{
	int nowTime = timeGetTime() - m_startTime;

	if (nowTime > 1000 && nowTime < 5000) {
		if (m_mobSpawn[0]->Update()) {
			auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
			one.push_back(new cOne(2, 1, VEC2(50, 200)));
			INT idx = one.size() - 1;
			cOne* nowOne = ((cOne*)(one[idx]));
			nowOne->m_theta = 15;
			nowOne->m_bulletCnt = 8;
			nowOne->SetDelay(500 + rand() % 200);
			nowOne->SetSpeed(100);
		}
	}

	else if (nowTime > 5000 && nowTime < 10000) {
		if (m_mobSpawn[0]->Update()) {
			auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
			one.push_back(new cOne(2, 2, VEC2(50 + INGAMEX, 200)));
			INT idx = one.size() - 1;
			cOne* nowOne = ((cOne*)(one[idx]));
			nowOne->m_theta = 15;
			nowOne->m_bulletCnt = 8;
			nowOne->SetDelay(500 + rand() % 200);
			nowOne->SetSpeed(100);
		}
	}

	else if (nowTime > 15000 && nowTime < 15020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		for (size_t i = 1; i <= 3; i++) {
			fairy.push_back(new cFairy(10, FAIRY_BLUE, 1, VEC2(50 + INGAMEX / 4 * i, 0)));
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
		nowFairy->SetSpeed(200.f);
		nowFairy->m_isAccel = TRUE;
	}

	//10���� �Ǹ� ��������
	else if (nowTime > 600000) {
		//Ŭ����ÿ� ����Ʈ�� ����
		isExtra = TRUE;
		SCENE->ChangeScene("titleScene");
	}
}
