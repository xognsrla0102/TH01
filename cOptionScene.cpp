#include "DXUT.h"
#include "cButton.h"
#include "cOptionScene.h"

cOptionScene::cOptionScene()
{
	m_BG = IMAGE->FindImage("optionBG");

	//목숨 버튼
	m_buttons.push_back(new cButton("lifeBT", VEC2(1.5f, 1.5f)));
	m_buttons.push_back(new cButton("1BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("2BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("3BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("4BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("5BT", VEC2(1.3f, 1.3f)));

	//위치 설정
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 100, 120));

	//새로운 라인 추가
	m_manyButtons.push_back(m_buttons);

	//이 배열은 이제 쓸 일이 없으므로 요소 없애주기(메모리 해제는 안 됨)
	//이전에 저장했던 버튼 메모리들은 m_manyButtons으로 옮겨짐
	m_buttons.clear();

	//폭탄 버튼
	m_buttons.push_back(new cButton("bombBT", VEC2(1.5f, 1.5f)));
	m_buttons.push_back(new cButton("0BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("1BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("2BT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("3BT", VEC2(1.3f, 1.3f)));

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 100, 200));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//BGM 버튼들
	m_buttons.push_back(new cButton("bgmBT", VEC2(1.5f, 1.5f)));
	m_buttons.push_back(new cButton("offBT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("wavBT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("midiBT", VEC2(1.3f, 1.3f)));
	
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 120, 280));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//SOUND 버튼
	m_buttons.push_back(new cButton("soundBT", VEC2(1.5f, 1.5f)));
	m_buttons.push_back(new cButton("offBT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("onBT", VEC2(1.3f, 1.3f)));

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 120, 360));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//WINDOW 버튼
	m_buttons.push_back(new cButton("modeBT", VEC2(1.5f, 1.5f)));
	m_buttons.push_back(new cButton("windowBT", VEC2(1.3f, 1.3f)));
	m_buttons.push_back(new cButton("fullBT", VEC2(1.3f, 1.3f)));

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 200, 440));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//RESTORE 버튼
	m_buttons.push_back(new cButton("restoreBT", VEC2(1.3f, 1.3f)));
	m_buttons[0]->SetPos(VEC2(300, 520));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//QUIT버튼
	m_buttons.push_back(new cButton("quitBT", VEC2(1.5f, 1.5f)));
	m_buttons[0]->SetPos(VEC2(300, 600));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//시작위치의 태그 활성화
	m_manyButtons[0][0]->m_isOn = TRUE;

	//각 라인에 해당 값을 할당하기 전 초기화
	for (size_t i = 0; i < oBUTTON_END; i++)
		optionValue.push_back(0);

	optionValue[oLIFE] = playerLife;

	//붐의 값이 2일 경우 버튼 상 위치는
	//태그, 0, 1 즉 1이 되어서 1을 더 더해줘야 위치가 2가 된다.
	optionValue[oBOMB] = playerBomb + 1;

	//BGM이 OFF면 1, ON이면 wav일 경우 2, midi면 3
	//0 위치는 태그임
	if (onBGM == TRUE) {
		if (isMidi == TRUE) optionValue[oBGM] = 3;
		else optionValue[oBGM] = 2;
	}
	else optionValue[oBGM] = 1;

	//SOUND가 OFF면 1 ON이면 2
	//마찬가지로 0은 태그 위치
	if (onSND == TRUE) optionValue[oSOUND] = 2;
	else optionValue[oSOUND] = 1;

	//MODE가 WINDOW면 1 FULL이면 2
	if (isWindowed == TRUE) optionValue[oWINDOWED] = 1;
	else optionValue[oWINDOWED] = 2;

	//씬이 시작될 때 첫 시작 위치는
	//첫 번째 라인에 선택된 항목이다.
	m_manyButtons[0][optionValue[0]]->m_isOn = TRUE;

	//각 라인에 선택된 항목들도 on시켜주기(QUIT, RESTORE 버튼은 제외)
	for (size_t i = 0; i < m_manyButtons.size() - 2; i++)
		m_manyButtons[i][optionValue[i]]->m_isOn = TRUE;

	//버튼 이어주기

	//상 잇기
	for (size_t i = m_manyButtons.size() - 1; i > 0; i--)
		for (size_t j = 0; j < m_manyButtons[i].size(); j++)
			m_manyButtons[i][j]->m_up = m_manyButtons[i - 1][optionValue[i - 1]];
	//하 잇기
	for (size_t i = 0; i < m_manyButtons.size() - 1; i++)
		for (size_t j = 0; j < m_manyButtons[i].size(); j++)
			m_manyButtons[i][j]->m_down = m_manyButtons[i + 1][optionValue[i + 1]];
	//좌 잇기
	for (size_t i = 0; i < m_manyButtons.size(); i++)
		for (size_t j = m_manyButtons[i].size() - 1; j > 0; j--)
			m_manyButtons[i][j]->m_left = m_manyButtons[i][j - 1];
	//우 잇기
	for (size_t i = 0; i < m_manyButtons.size(); i++)
		for (size_t j = 0; j < m_manyButtons[i].size() - 1; j++)
			m_manyButtons[i][j]->m_right = m_manyButtons[i][j + 1];
}

cOptionScene::~cOptionScene()
{
	for (auto iter : m_manyButtons) {
		for (auto jter : iter)
			SAFE_DELETE(jter);
		iter.clear();
	}
	m_manyButtons.clear();
}

void cOptionScene::Init()
{
	SOUND->Play("th_04_%s", TRUE, TRUE);

	m_nowLine = 0;
	m_BG->m_a = 0;
	m_manyButtons[m_nowLine][0]->m_isOn = TRUE;
}

void cOptionScene::Update()
{
	for (auto iter : m_manyButtons)
		for (auto jter : iter)
			jter->Update();

	if (KEYDOWN(DIK_UP)) {
		SOUND->Play("keymoveSND");
		//태그 위치 변경
		m_manyButtons[m_nowLine][0]->m_isOn = FALSE;

		if (m_nowLine > 0) m_nowLine--;
		else while (m_nowLine < m_manyButtons.size() - 1) m_nowLine++;

		m_manyButtons[m_nowLine][0]->m_isOn = TRUE;
		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = TRUE;
	}

	if (KEYDOWN(DIK_DOWN)) {
		SOUND->Play("keymoveSND");
		m_manyButtons[m_nowLine][0]->m_isOn = FALSE;

		if (m_nowLine < m_manyButtons.size() - 1) m_nowLine++;
		else while (m_nowLine > 0) m_nowLine--;

		m_manyButtons[m_nowLine][0]->m_isOn = TRUE;
		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = TRUE;
	}

	if (KEYDOWN(DIK_LEFT) || KEYDOWN(DIK_RIGHT)) {
		SOUND->Play("keymoveSND");

		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = FALSE;

		if (KEYDOWN(DIK_LEFT)) {
			if (optionValue[m_nowLine] > 1) optionValue[m_nowLine]--;
			else optionValue[m_nowLine] = m_manyButtons[m_nowLine].size() - 1;
		}
		else {
			if (optionValue[m_nowLine] < m_manyButtons[m_nowLine].size() - 1)
				optionValue[m_nowLine]++;
			else optionValue[m_nowLine] = 1;
		}

		switch (m_nowLine) {
		case oLIFE:
			playerLife = optionValue[m_nowLine];
			break;
		case oBOMB:
			playerBomb = optionValue[m_nowLine] - 1;
			break;
		case oBGM:
			SOUND->Stop("th_04_%s");
			switch (optionValue[m_nowLine]) {
			//off
			case 1:
				onBGM = FALSE;
				break;
			//wav
			case 2:
				onBGM = TRUE;
				isMidi = FALSE;
				break;
			//midi
			case 3:
				onBGM = TRUE;
				isMidi = TRUE;
				break;
			}
			SOUND->Play("th_04_%s", TRUE, TRUE);
			break;
		case oSOUND:
			//off
			if (optionValue[m_nowLine] == 1) onSND = FALSE;
			//on
			else if (optionValue[m_nowLine] == 2) onSND = TRUE;
			break;
		case oWINDOWED:
			if (optionValue[m_nowLine] == 1 || optionValue[m_nowLine] == 2) {
				isWindowed = !isWindowed;
				DXUTPause(TRUE, TRUE);
				DXUTToggleFullScreen();
				DXUTPause(FALSE, FALSE);
			}
			break;
		}
		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = TRUE;
	}

	if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
		SOUND->Play("selectSND");
		SOUND->Stop("th_04_%s");
		bool wasWindowed = isWindowed;

		switch (m_nowLine) {
		case oRESTORE:
			for (size_t i = 0; i < m_manyButtons.size() - 1; i++)
				m_manyButtons[i][optionValue[i]]->m_isOn = FALSE;

			isWindowed = TRUE;
			if (isWindowed != wasWindowed) {
				DXUTPause(TRUE, TRUE);
				DXUTToggleFullScreen();
				DXUTPause(FALSE, FALSE);
			}

			onBGM = TRUE;
			isMidi = FALSE;
			onSND = TRUE;
			playerLife = 3;
			playerBomb = 3;

			optionValue[oLIFE] = playerLife;
			optionValue[oBOMB] = playerBomb + 1;

			if (onBGM == TRUE) {
				if (isMidi == TRUE) optionValue[oBGM] = 3;
				else optionValue[oBGM] = 2;
			}
			else optionValue[oBGM] = 1;

			if (onSND == TRUE) optionValue[oSOUND] = 2;
			else optionValue[oSOUND] = 1;

			if (isWindowed == TRUE) optionValue[oWINDOWED] = 1;
			else optionValue[oWINDOWED] = 2;

			for (size_t i = 0; i < m_manyButtons.size() - 1; i++)
				m_manyButtons[i][optionValue[i]]->m_isOn = TRUE;
			SOUND->Play("th_04_%s", TRUE, TRUE);
			break;
		case oQUIT:
			m_manyButtons[m_nowLine][0]->m_isOn = FALSE;
			SCENE->ChangeScene("titleScene");

			//나갈 때 설정 저장함
			FILEMANAGER->OptionSave();
			return;
			break;
		}
	}

	if (KEYDOWN(DIK_ESCAPE) || KEYDOWN(DIK_X)) {
		SOUND->Copy("cancelSND");
		m_manyButtons[m_nowLine][0]->m_isOn = FALSE;
		m_manyButtons[oQUIT][0]->m_isOn = TRUE;
		m_nowLine = oQUIT;
	}

	Lerp(m_BG->m_a, 255.f, 0.05);
	m_BG->SetNowRGB();
}

void cOptionScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0), 1.f, 0.f, FALSE, m_BG->m_color);

	for (auto iter : m_manyButtons)
		for(auto jter : iter)
			jter->Render();

	DRAW_FRAME(to_string(DXUTGetFPS()), VEC2(1000, 680));
}

void cOptionScene::Release()
{
}
