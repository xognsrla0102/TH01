#include "DXUT.h"

#include "cTimer.h"

#include "cPlayer.h"

#include "cBall.h"
#include "cBalls.h"

#include "cOne.h"
#include "cFairy.h"
#include "cBook.h"

#include "cBullet.h"
#include "cBulletAdmin.h"

#include "cEnemy.h"
#include "cEnemyAdmin.h"

#include "cButton.h"

#include "cItemAdmin.h"

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

	m_spellBlack = IMAGE->FindImage("spell_black");

	m_fullPower = IMAGE->FindImage("fullPowerMode");
	m_powerMax = IMAGE->FindImage("ingame_powerMax");

	m_pause.push_back(new cButton("pause_pauseBT", VEC2(0.7, 0.7)));
	m_pause.push_back(new cButton("pause_cancelBT", VEC2(1, 1), 0.2f));
	m_pause.push_back(new cButton("pause_exitBT", VEC2(1, 1), 0.2f));
	for (size_t i = 0; i < m_pause.size(); i++)
		m_pause[i]->SetPos(VEC2(50 + INGAMEX / 2, 50 + INGAMEY / 2 - 150 + i * 100));

	m_exit.push_back(new cButton("exit_sureBT", VEC2(0.7, 0.7)));
	m_exit.push_back(new cButton("exit_noBT", VEC2(1, 1), 0.2f));
	m_exit.push_back(new cButton("exit_yesBT", VEC2(1, 1), 0.2f));
	for (size_t i = 0; i < m_exit.size(); i++)
		m_exit[i]->SetPos(VEC2(50 + INGAMEX / 2, 50 + INGAMEY / 2 - 150 + i * 100));

	m_continue.push_back(new cButton("continueBT", VEC2(1, 1), 0.2f));
	m_continue.push_back(new cButton("exit_yesBT", VEC2(1, 1), 0.2f));
	m_continue.push_back(new cButton("exit_noBT", VEC2(1, 1), 0.2f));
	for (size_t i = 0; i < m_continue.size(); i++)
		m_continue[i]->SetPos(VEC2(50 + INGAMEX / 2, 50 + INGAMEY / 2 - 150 + i * 100));
}

cStage1Scene::~cStage1Scene()
{
	Release();

	for (auto iter : m_pause)
		SAFE_DELETE(iter);
	for (auto iter : m_exit)
		SAFE_DELETE(iter);
	for (auto iter : m_continue)
		SAFE_DELETE(iter);

	m_pause.clear();
	m_exit.clear();
	m_continue.clear();
}

void cStage1Scene::Init()
{
	SOUND->Play("th_02_%s", TRUE, TRUE);

	m_startTime = timeGetTime();
	m_pauseTime = 0;
	m_continueTime = 0;

	m_nowButton = 1;

	m_pause[0]->m_isOn = TRUE;
	m_pause[1]->m_isOn = TRUE;

	m_exit[0]->m_isOn = TRUE;
	m_exit[1]->m_isOn = TRUE;

	m_continue[0]->m_isOn = TRUE;
	m_continue[1]->m_isOn = TRUE;

	m_isPause = m_isExit = m_isContinue = FALSE;
	m_nowContinue = 3;

	((cBalls*)OBJFIND(BALLS))->Release();
	((cPlayer*)OBJFIND(PLAYER))->Release();
	((cPlayer*)OBJFIND(PLAYER))->Init();

	((cBulletAdmin*)OBJFIND(BULLETS))->Release();

	//ui���� �ִ� ���� �÷��� ������
	//745 X 620 �̰� ���� ��ġ�� 50,50���� 795, 670 ������
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

	m_spellBlack->m_a = 0.f;
	m_spellBlack->SetNowRGB();

	m_fullPower->m_a = 0.f;
	m_fullPower->SetNowRGB();
	m_fullPower->m_pos = VEC2(50 + INGAMEX / 2, 50 + INGAMEY / 2);

	m_img1Pos = m_img2Pos = VEC2(50, 0);

	m_mobSpawn.push_back(new cTimer(300));
	m_mobSpawn.push_back(new cTimer(0));

	if (extraMode == TRUE) m_extraDelay = 0.5f;
	else m_extraDelay = 1.f;
}

void cStage1Scene::Update()
{
	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));

	if (m_isContinue == TRUE) {
		Lerp(m_spellBlack->m_a, 150.f, 0.05);
		m_spellBlack->SetNowRGB();
		Continue();
		return;
	}
	else if ((INT)m_spellBlack->m_a != 0) {
		Lerp(m_spellBlack->m_a, 0.f, 0.02);
		m_spellBlack->SetNowRGB();
	}

	if (KEYDOWN(DIK_ESCAPE)) {
		if (m_isExit == TRUE) {
			m_isExit = m_isPause = FALSE;
			m_startTime += timeGetTime() - m_pauseTime;

			m_exit[m_nowButton]->m_isOn = FALSE;
			m_nowButton = 1;
			m_exit[m_nowButton]->m_isOn = TRUE;

			CAMERA->m_isPause = FALSE;
		}
		else {
			m_isPause = !m_isPause;
			//�Ͻ������� ���۵Ǵ� ���� �Ͻ����� �Ǵ� ��ŭ�� �ð��� ���
			if (m_isPause == TRUE) {
				m_pauseTime = timeGetTime();
				CAMERA->m_isPause = TRUE;
			}

			//�Ͻ������� Ǯ���� ����
			//���ӽ����� �ð��� �Ͻ������� �ð���ŭ ���� ������ �ٿ���
			//���� ������ �ð��� timeGetTime() - m_startTime �̱� ������ m_startTime�� Ŀ�� ���� ���� �ð��� �پ��
			//������ �̰� 1���������� ���� �����ΰ��� Ÿ�̸Ӹ� �Ͻ������� ������
			//�ٸ� ��ü�� Ÿ�̸Ӵ� ������ ���ư��Ƿ� �Ϻ��� �Ͻ������� �ƴ�. ������ ������ �� �����Ƿ� �ӽù���...
			//��ٸ��� ���� �ʹݿ� �������� �̸��� ������ �ʴ� �� ���� ���׵��� ����
			//�������ʹ� ��ŸŸ���� �� ����
			else {
				m_startTime += timeGetTime() - m_pauseTime;

				m_pause[m_nowButton]->m_isOn = FALSE;
				m_nowButton = 1;
				m_pause[m_nowButton]->m_isOn = TRUE;

				CAMERA->m_isPause = FALSE;
			}
		}
	}
	
	if (player->m_isBomb == TRUE || m_isPause == TRUE || m_isExit == TRUE ) {
		Lerp(m_spellBlack->m_a, 150.f, 0.05);
		m_spellBlack->SetNowRGB();
	}
	else if ((INT)m_spellBlack->m_a != 0) {
		Lerp(m_spellBlack->m_a, 0.f, 0.02);
		m_spellBlack->SetNowRGB();
	}

	if (m_isPause == TRUE || m_isExit == TRUE) {
		PauseOrExit();
		return;
	}

	ScroolMap();
	LevelDesign();

	EFFECT->Update();

	player->m_wasPower = player->m_power;
	OBJFIND(ITEMS)->Update();
	OBJFIND(ENEMYS)->Update();
	OBJFIND(PLAYER)->Update();
	OBJFIND(BALLS)->Update();
	OBJFIND(BULLETS)->Update();

	if (player->GetLive() == FALSE){
		if (m_nowContinue > 0) {
			m_isContinue = TRUE;
			CAMERA->m_isPause = TRUE;
			m_continueTime = timeGetTime();
		}
		else {
			player->GetRefLive() = TRUE;
			SCENE->ChangeScene("titleScene");
		}
		return;
	}

	if (player->m_isFullPower == TRUE) {
		Lerp(m_fullPower->m_a, 256.f, 0.03);
		m_fullPower->SetNowRGB();

		if ((INT)m_fullPower->m_a == 255) {
			player->m_isFullPower = FALSE;
			m_fullPower->m_a = 0.f;
			m_fullPower->SetNowRGB();
		}
	}
}

void cStage1Scene::Render()
{
	IMAGE->Render(m_img, m_img1Pos, 1.f);
	IMAGE->Render(m_img2, m_img2Pos, 1.f);

	IMAGE->Render(m_black, VEC2(50, 50), 1.2f);
	IMAGE->Render(m_spellBlack, VEC2(50, 50), 1.f, 0.f, FALSE, m_spellBlack->m_color);

	OBJFIND(ENEMYS)->Render();

	OBJFIND(PLAYER)->Render();
	OBJFIND(BALLS)->Render();
	OBJFIND(ITEMS)->Render();
	OBJFIND(BULLETS)->Render();

	EFFECT->Render();

	//UI ���
	IMAGE->ReBegin(TRUE);

	if (timeGetTime() - m_startTime < 8000) {
		IMAGE->Render(m_name, VEC2(50 + INGAMEX / 2, 50 + 250), 1.f, 0.f, TRUE, m_name->m_color);
		IMAGE->Render(m_musicName, VEC2(50 + INGAMEX - 120, 50 + INGAMEY - 20), 1.f, 0.f, TRUE, m_musicName->m_color);
	}

	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));
	if (player->m_isBomb == TRUE) {
		IMAGE->Render(player->m_bombFace, player->m_bombFace->m_pos, player->m_bombFace->m_size, 0.f, TRUE, player->m_bombFace->m_color);
		IMAGE->Render(player->m_bombName, player->m_bombName->m_pos, 1.f, 0.f, TRUE, player->m_bombName->m_color);
	}

	IMAGE->Render(m_fullPower, m_fullPower->m_pos, VEC2(1, 1), 0.f, TRUE, m_fullPower->m_color);

	IMAGE->Render(m_ui, VEC2(0, 0), 1.f);

	IMAGE->Render(m_circle, VEC2(50 + INGAMEX + 180, 50 + INGAMEY - 130), 1.f, m_circle->m_rot, TRUE, m_circle->m_color);
	IMAGE->Render(m_title, VEC2(50 + INGAMEX + 180, 50 + INGAMEY - 130), 1.f, 0.f, TRUE, m_title->m_color);

	for (INT i = 0; i < player->m_life - 1; i++)
		IMAGE->Render(m_life, VEC2(880 + i * 25, 200), 1.f);
	for(INT i = 0; i < player->m_bomb; i++)
		IMAGE->Render(m_bomb, VEC2(880 + i * 25, 235), 1.f);

	CHAR numText[256];
	
	FLOAT score = player->m_score;
	sprintf(numText, "%09d", (INT)score);
	DRAW_NUM(string(numText), VEC2(880, 137));

	INT power = player->m_power;
	INT graze = player->m_graze;
	INT jum = player->m_jum;

	if (power != 128) {
		sprintf(numText, "%d", (INT)power);
		DRAW_NUM(string(numText), VEC2(890, 300));
	}
	else IMAGE->Render(m_powerMax, VEC2(890, 300), 1.f);

	sprintf(numText, "%d", (INT)graze);
	DRAW_NUM(string(numText), VEC2(890, 340));

	sprintf(numText, "%d", (INT)jum);
	DRAW_NUM(string(numText), VEC2(890, 380));

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));

	if (m_isPause == TRUE || m_isExit == TRUE || m_isContinue == TRUE) {
		IMAGE->Render(m_spellBlack, VEC2(50, 50), 1.f, 0.f, FALSE, m_spellBlack->m_color);

		if (m_isPause == TRUE) {
			for (auto iter : m_pause)
				iter->Render();
		}
		else if (m_isExit == TRUE) {
			for (auto iter : m_exit)
				iter->Render();
		}
		else if (m_isContinue == TRUE) {
			for (auto iter : m_continue)
				iter->Render();
			sprintf(numText, "%d", (INT)m_nowContinue);
			DRAW_NUM_SIZE(string(numText), VEC2(50 + INGAMEX / 2 + 30, 225), 1.3f);
		}
	}
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
	((cItemAdmin*)OBJFIND(ITEMS))->Release();
	EFFECT->Reset();
}

void cStage1Scene::Continue()
{
	if (INPUT->KeyDown(DIK_UP) || INPUT->KeyDown(DIK_DOWN)) {
		SOUND->Play("keymoveSND");
		m_continue[m_nowButton]->m_isOn = FALSE;
		m_nowButton = (m_nowButton != 1) ? 1 : 2;
		m_continue[m_nowButton]->m_isOn = TRUE;
	}
	else if (INPUT->KeyDown(DIK_RETURN) || INPUT->KeyDown(DIK_Z)) {
		SOUND->Play("selectSND");
		switch (m_nowButton) {
		case 1:
			SOUND->Copy("deadSND");
			m_nowContinue--;
			//��Ƽ���� ��ŭ�� �ð��� ��ŸƮ���� ���������. �Ͻ�����ó��
			m_startTime += timeGetTime() - m_continueTime;
			break;
		case 2:
			//�ϴ� Ÿ��Ʋ������ �̵�. ������ ���ӿ��������� �̵��ؾ���
			SCENE->ChangeScene("titleScene");
			break;
		}
		OBJFIND(PLAYER)->GetRefLive() = TRUE;
		m_isContinue = FALSE;
		m_continue[1]->m_isOn = TRUE;
		m_continue[2]->m_isOn = FALSE;
		m_nowButton = 1;
		CAMERA->m_isPause = FALSE;
	}

	for (auto iter : m_continue)
		iter->Update();
}

void cStage1Scene::PauseOrExit()
{
	if (INPUT->KeyDown(DIK_UP) || INPUT->KeyDown(DIK_DOWN)) {
		SOUND->Play("keymoveSND");
		if (m_isPause == TRUE) m_pause[m_nowButton]->m_isOn = FALSE;
		else m_exit[m_nowButton]->m_isOn = FALSE;
		m_nowButton = (m_nowButton != 1) ? 1 : 2;
		if (m_isPause == TRUE) m_pause[m_nowButton]->m_isOn = TRUE;
		else m_exit[m_nowButton]->m_isOn = TRUE;
	}
	else if (INPUT->KeyDown(DIK_RETURN) || INPUT->KeyDown(DIK_Z)) {
		SOUND->Play("selectSND");
		if (m_isPause == TRUE) {
			switch (m_nowButton) {
			case 1:
				m_startTime += timeGetTime() - m_pauseTime;
				CAMERA->m_isPause = FALSE;
				break;
			case 2:
				m_isExit = TRUE;
				break;
			}
			m_isPause = FALSE;
			m_pause[1]->m_isOn = TRUE;
			m_pause[2]->m_isOn = FALSE;
		}
		else {
			switch (m_nowButton) {
			case 1:
				m_isPause = TRUE;
				break;
			case 2:
				m_isPause = FALSE;
				CAMERA->m_isPause = FALSE;
				CAMERA->m_isShake = FALSE;
				SCENE->ChangeScene("titleScene");
				break;
			}
			m_isExit = FALSE;
			m_exit[1]->m_isOn = TRUE;
			m_exit[2]->m_isOn = FALSE;
		}
		m_nowButton = 1;
	}
	else if (INPUT->KeyDown(DIK_X)) {
		SOUND->Play("cancelSND");
		if (m_isPause == TRUE) {
			m_isPause = FALSE;
			CAMERA->m_isPause = FALSE;
			m_pause[1]->m_isOn = TRUE;
			m_pause[2]->m_isOn = FALSE;
		}
		else {
			m_isExit = FALSE;
			m_exit[1]->m_isOn = TRUE;
			m_exit[2]->m_isOn = FALSE;
			m_isPause = TRUE;
		}
		m_nowButton = 1;
	}

	if (m_isPause == TRUE) {
		for (auto iter : m_pause)
			iter->Update();
	}
	else {
		for (auto iter : m_exit)
			iter->Update();
	}
}

void cStage1Scene::ScroolMap()
{
	//�� ��ũ��
	m_scrool += 100.f * D_TIME;
	m_img1Pos.y = 50 + (INT)m_scrool % m_img->m_info.Height;
	m_img2Pos.y = m_img1Pos.y - m_img->m_info.Height;
}

void cStage1Scene::LevelDesign()
{
	INT nowTime = timeGetTime() - m_startTime;

	if (nowTime < 8000) {
		Lerp(m_title->m_a, 255.f, 0.02);
		Lerp(m_circle->m_a, 255.f, 0.02);
		Lerp(m_circle->m_rot, 0.f, 0.01);

		if (1000 < nowTime && nowTime < 5000) {
			Lerp(m_name->m_a, 255.f, 0.02);
			Lerp(m_musicName->m_a, 255.f, 0.02);
		}
		else if (5000 < nowTime && nowTime < 8000) {
			Lerp(m_name->m_a, 0.f, 0.04);
			Lerp(m_musicName->m_a, 0.f, 0.04);
		}
		m_name->SetNowRGB();
		m_musicName->SetNowRGB();
		m_title->SetNowRGB();
		m_circle->SetNowRGB();
	}

	if (5000 < nowTime && nowTime < 8000) {
		if (m_mobSpawn[0]->Update()) {
			auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
			one.push_back(new cOne(2, 1, VEC2(50, 200)));
			INT idx = one.size() - 1;
			cOne* nowOne = ((cOne*)one[idx]);

			nowOne->m_theta = 15;
			nowOne->m_bulletCnt = 8;
			nowOne->SetDelay((300 + rand() % 21 * 50) * m_extraDelay);
			nowOne->SetSpeed(70);
			nowOne->GetItemNames().push_back("item_smallPower");
		}
	}

	else if (10000 < nowTime && nowTime < 13000) {
		if (m_mobSpawn[0]->Update()) {
			auto& one = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetOne();
			one.push_back(new cOne(2, 2, VEC2(50 + INGAMEX, 200)));
			INT idx = one.size() - 1;
			cOne* nowOne = ((cOne*)one[idx]);

			nowOne->m_theta = 15;
			nowOne->m_bulletCnt = 8;
			nowOne->SetDelay((300 + rand() % 21 * 50) * m_extraDelay);
			nowOne->SetSpeed(70);
			nowOne->GetItemNames().push_back("item_smallPower");
		}
	}

	else if (18000 < nowTime && nowTime < 18020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		for (size_t i = 1; i <= 3; i++) {
			fairy.push_back(new cFairy(10, FAIRY_RED, 1, VEC2(50 + INGAMEX / 4 * i, 0)));
			INT idx = fairy.size() - 1;
			cFairy* nowFairy = ((cFairy*)fairy[idx]);

			nowFairy->m_path = new cPath(nowFairy->GetPos());
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 100), 0.03, 0);
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 100), 0, 1000);
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y - 100), 0.02, 0);

			nowFairy->m_circleCnt = 10;
			nowFairy->SetDelay(500 * m_extraDelay);
			nowFairy->SetSpeed(300.f);
			nowFairy->m_isRandShot = TRUE;
			nowFairy->m_isAccel = TRUE;
			nowFairy->GetItemNames().push_back("item_smallPower");
		}
	}

	else if (22000 < nowTime && nowTime < 22020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		fairy.push_back(new cFairy(30, FAIRY_PURPLE, 1, VEC2(50 + INGAMEX / 2, 0)));
		INT idx = fairy.size() - 1;
		cFairy* nowFairy = ((cFairy*)fairy[idx]);

		nowFairy->m_path = new cPath(nowFairy->GetPos());
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0.03, 0);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0, 1000);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y - 100), 0.02, 0);

		nowFairy->m_circleCnt = 10;
		nowFairy->SetDelay(200 * m_extraDelay);
		nowFairy->SetSpeed(300.f);
		nowFairy->m_isRandShot = TRUE;
		nowFairy->m_isAccel = TRUE;
	}

	else if (25000 < nowTime && nowTime < 25020) {
		auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
		fairy.push_back(new cFairy(100, FAIRY_BLUE, 2, VEC2(50 + INGAMEX / 2, 0)));
		INT idx = fairy.size() - 1;
		cFairy* nowFairy = ((cFairy*)fairy[idx]);

		nowFairy->m_path = new cPath(nowFairy->GetPos());
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0.03, 0);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0, 3000);
		nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y - 100), 0.02, 0);

		nowFairy->SetDelay(100 * m_extraDelay);
		nowFairy->SetSpeed(250.f);
		nowFairy->m_isAccel = TRUE;
	}

	else if (30000 < nowTime && nowTime < 35000) {
		if (m_mobSpawn[0]->Update()) {
			auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
			fairy.push_back(new cFairy(30, FAIRY_GREEN, 1, VEC2(50 + INGAMEX / 2, 0)));
			INT idx = fairy.size() - 1;
			cFairy* nowFairy = ((cFairy*)fairy[idx]);

			nowFairy->m_path = new cPath(nowFairy->GetPos());
			nowFairy->m_path->AddCurve(nowFairy->GetPos(), VEC2(50, 100), VEC2(50 + INGAMEX / 2, 200), 1000);
			nowFairy->m_path->AddCurve(VEC2(50 + INGAMEX / 2, 200), VEC2(50 + INGAMEX, 300), VEC2(50 + INGAMEX / 2, 400), 1000);
			nowFairy->m_path->AddCurve(VEC2(50 + INGAMEX / 2, 400), VEC2(50, 500), VEC2(50 + INGAMEX / 2, 600), 1000);
			nowFairy->m_path->AddCurve(VEC2(50 + INGAMEX / 2, 600), VEC2(50 + INGAMEX, 700), VEC2(50 + INGAMEX / 2, 800), 1000);
			nowFairy->m_isAccelCurve = TRUE;
			nowFairy->m_divDelta = 10;

			nowFairy->m_circleCnt = 10;
			nowFairy->SetDelay(1500 * m_extraDelay);
			nowFairy->SetSpeed(100.f);
			nowFairy->m_isRandShot = TRUE;
			nowFairy->m_isAccel = TRUE;
		}
	}
	
	if (38000 < nowTime && nowTime < 38020) {
		for (size_t i = 1; i <= 5; i++) {
			auto& fairy = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetFairy();
			fairy.push_back(new cFairy(30, FAIRY_BLUE, 1, VEC2(50 + 100 * i, 0)));
			INT idx = fairy.size() - 1;
			cFairy* nowFairy = ((cFairy*)fairy[idx]);

			nowFairy->m_path = new cPath(nowFairy->GetPos());
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0.03, 0);
			nowFairy->m_path->AddPoint(VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150), 0, 200 * i);
			nowFairy->m_path->AddCurve(
				VEC2(nowFairy->GetPos().x, nowFairy->GetPos().y + 50 + 150),
				VEC2(nowFairy->GetPos().x + 100 * i, 50 + INGAMEY - 50),
				VEC2(50 + INGAMEX + 100 * i, 50 + INGAMEY),
				1500
			);
			nowFairy->m_isAccelCurve = TRUE;

			nowFairy->m_circleCnt = 10;
			nowFairy->SetDelay(1500 * m_extraDelay);
			nowFairy->SetSpeed(100.f);
			nowFairy->m_isRandShot = TRUE;
			nowFairy->m_isAccel = TRUE;
		}
	}

	//å �������� �׽�Ʈ
	if (40000 < nowTime && nowTime < 40020) {
		auto& book = ((cEnemyAdmin*)OBJFIND(ENEMYS))->GetBook();
		book.push_back(new cBook(50, BOOK_PINK, 2, FALSE, VEC2(WINSIZEX / 2, 100)));
		INT idx = book.size() - 1;
		cBook* nowBook = ((cBook*)book[idx]);
		nowBook->m_startDelay = 1000;
		nowBook->m_atkDelay = 1000;

		book.push_back(new cBook(50, BOOK_GREEN, 1, FALSE, VEC2(WINSIZEX / 3, 100)));
		idx = book.size() - 1;
		nowBook = ((cBook*)book[idx]);
		nowBook->m_circleCnt = 10;
		nowBook->SetDelay(1500 * m_extraDelay);
		nowBook->SetSpeed(100.f);
		nowBook->m_isRandShot = TRUE;
		nowBook->m_isAccel = TRUE;
	}

	//10���� �Ǹ� ��������
	else if (600000 < nowTime) {
		//Ŭ����ÿ� ����Ʈ�� ����
		isExtra = TRUE;
		SCENE->ChangeScene("titleScene");
	}
}
