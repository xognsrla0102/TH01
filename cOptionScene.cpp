#include "DXUT.h"
#include "cButton.h"
#include "cOptionScene.h"

cOptionScene::cOptionScene()
{
	m_BG = IMAGE->FindImage("titleBG");

	//��� ��ư
	m_buttons.push_back(new cButton("lifeBT"));
	m_buttons.push_back(new cButton("1BT"));
	m_buttons.push_back(new cButton("2BT"));
	m_buttons.push_back(new cButton("3BT"));
	m_buttons.push_back(new cButton("4BT"));
	m_buttons.push_back(new cButton("5BT"));

	//��ġ ����
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 100, 120));

	//���ο� ���� �߰�
	m_manyButtons.push_back(m_buttons);

	//�� �迭�� ���� �� ���� �����Ƿ� ��� �����ֱ�(�޸� ������ �� ��)
	//������ �����ߴ� ��ư �޸𸮵��� m_manyButtons���� �Ű���
	m_buttons.clear();

	//��ź ��ư
	m_buttons.push_back(new cButton("bombBT"));
	m_buttons.push_back(new cButton("0BT"));
	m_buttons.push_back(new cButton("1BT"));
	m_buttons.push_back(new cButton("2BT"));
	m_buttons.push_back(new cButton("3BT"));

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 100, 200));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//BGM ��ư��
	m_buttons.push_back(new cButton("bgmBT"));
	m_buttons.push_back(new cButton("offBT"));
	m_buttons.push_back(new cButton("wavBT"));
	m_buttons.push_back(new cButton("midiBT"));
	
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 120, 280));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//SOUND ��ư
	m_buttons.push_back(new cButton("soundBT"));
	m_buttons.push_back(new cButton("offBT"));
	m_buttons.push_back(new cButton("onBT"));

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 120, 360));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//WINDOW ��ư
	m_buttons.push_back(new cButton("modeBT"));
	m_buttons.push_back(new cButton("windowBT"));
	m_buttons.push_back(new cButton("fullBT"));

	for (size_t i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->SetPos(VEC2(300 + i * 200, 440));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//RESTORE ��ư
	m_buttons.push_back(new cButton("restoreBT", VEC2(1.3f, 1.3f)));
	m_buttons[0]->SetPos(VEC2(300, 520));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//QUIT��ư
	m_buttons.push_back(new cButton("quitBT"));
	m_buttons[0]->SetPos(VEC2(300, 600));
	m_manyButtons.push_back(m_buttons);
	m_buttons.clear();

	//������ġ�� �±� Ȱ��ȭ
	m_manyButtons[0][0]->m_isOn = true;

	//�� ���ο� �ش� ���� �Ҵ��ϱ� �� �ʱ�ȭ
	for (size_t i = 0; i < oBUTTON_END; i++)
		optionValue.push_back(0);

	optionValue[oLIFE] = playerLife;

	//���� ���� 2�� ��� ��ư �� ��ġ��
	//�±�, 0, 1 �� 1�� �Ǿ 1�� �� ������� ��ġ�� 2�� �ȴ�.
	optionValue[oBOMB] = playerBomb + 1;

	//BGM�� OFF�� 1, ON�̸� wav�� ��� 2, midi�� 3
	//0 ��ġ�� �±���
	if (onBGM == true) {
		if (isMidi == true) optionValue[oBGM] = 3;
		else optionValue[oBGM] = 2;
	}
	else optionValue[oBGM] = 1;

	//SOUND�� OFF�� 1 ON�̸� 2
	//���������� 0�� �±� ��ġ
	if (onSND == true) optionValue[oSOUND] = 2;
	else optionValue[oSOUND] = 1;

	//MODE�� WINDOW�� 1 FULL�̸� 2
	if (isWindowed == true) optionValue[oWINDOWED] = 1;
	else optionValue[oWINDOWED] = 2;

	//���� ���۵� �� ù ���� ��ġ��
	//ù ��° ���ο� ���õ� �׸��̴�.
	m_manyButtons[0][optionValue[0]]->m_isOn = true;

	//�� ���ο� ���õ� �׸�鵵 on�����ֱ�(QUIT, RESTORE ��ư�� ����)
	for (size_t i = 0; i < m_manyButtons.size() - 2; i++)
		m_manyButtons[i][optionValue[i]]->m_isOn = true;

	//��ư �̾��ֱ�

	//�� �ձ�
	for (size_t i = m_manyButtons.size() - 1; i > 0; i--)
		for (size_t j = 0; j < m_manyButtons[i].size(); j++)
			m_manyButtons[i][j]->m_up = m_manyButtons[i - 1][optionValue[i - 1]];
	//�� �ձ�
	for (size_t i = 0; i < m_manyButtons.size() - 1; i++)
		for (size_t j = 0; j < m_manyButtons[i].size(); j++)
			m_manyButtons[i][j]->m_down = m_manyButtons[i + 1][optionValue[i + 1]];
	//�� �ձ�
	for (size_t i = 0; i < m_manyButtons.size(); i++)
		for (size_t j = m_manyButtons[i].size() - 1; j > 0; j--)
			m_manyButtons[i][j]->m_left = m_manyButtons[i][j - 1];
	//�� �ձ�
	for (size_t i = 0; i < m_manyButtons.size(); i++)
		for (size_t j = 0; j < m_manyButtons[i].size() - 1; j++)
			m_manyButtons[i][j]->m_right = m_manyButtons[i][j + 1];
}

cOptionScene::~cOptionScene()
{
	for (auto iter : m_manyButtons)
		for (auto jter : iter)
			SAFE_DELETE(jter);
}

void cOptionScene::Init()
{
	m_nowLine = 0;
	m_rgb = 0;
	m_manyButtons[m_nowLine][0]->m_isOn = true;
}

void cOptionScene::Update()
{
	for (auto iter : m_manyButtons)
		for (auto jter : iter)
			jter->Update();

	if (KEYDOWN(DIK_UP)) {
		SOUND->Play("keymoveSND");
		//�±� ��ġ ����
		m_manyButtons[m_nowLine][0]->m_isOn = false;

		if (m_nowLine > 0) m_nowLine--;
		else while (m_nowLine < m_manyButtons.size() - 1) m_nowLine++;

		m_manyButtons[m_nowLine][0]->m_isOn = true;
		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = true;
	}

	if (KEYDOWN(DIK_DOWN)) {
		SOUND->Play("keymoveSND");
		m_manyButtons[m_nowLine][0]->m_isOn = false;

		if (m_nowLine < m_manyButtons.size() - 1) m_nowLine++;
		else while (m_nowLine > 0) m_nowLine--;

		m_manyButtons[m_nowLine][0]->m_isOn = true;
		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = true;
	}

	if (KEYDOWN(DIK_LEFT) || KEYDOWN(DIK_RIGHT)) {
		SOUND->Play("keymoveSND");

		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = false;

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
			SOUND->Stop("th_01_%s");
			switch (optionValue[m_nowLine]) {
			//off
			case 1:
				onBGM = false;
				break;
			//wav
			case 2:
				onBGM = true;
				isMidi = false;
				break;
			//midi
			case 3:
				onBGM = true;
				isMidi = true;
				break;
			}
			SOUND->Play("th_01_%s", true, true);
			break;
		case oSOUND:
			//off
			if (optionValue[m_nowLine] == 1) onSND = false;
			//on
			else if (optionValue[m_nowLine] == 2) onSND = true;
			break;
		case oWINDOWED:
			if (optionValue[m_nowLine] == 1 || optionValue[m_nowLine] == 2) {
				isWindowed = !isWindowed;
				DXUTToggleFullScreen();
			}
			break;
		}
		m_manyButtons[m_nowLine][optionValue[m_nowLine]]->m_isOn = true;
	}

	if (KEYDOWN(DIK_RETURN) || KEYDOWN(DIK_Z)) {
		SOUND->Play("selectSND");
		bool wasWindowed = isWindowed;

		switch (m_nowLine) {
		case oRESTORE:
			SOUND->Stop("th_01_%s");

			for (size_t i = 0; i < m_manyButtons.size() - 1; i++)
				m_manyButtons[i][optionValue[i]]->m_isOn = false;

			isWindowed = true;
			if (isWindowed != wasWindowed) {
				DXUTToggleFullScreen();
			}

			onBGM = true;
			isMidi = false;
			onSND = true;
			playerLife = 3;
			playerBomb = 3;

			optionValue[oLIFE] = playerLife;
			optionValue[oBOMB] = playerBomb + 1;

			if (onBGM == true) {
				if (isMidi == true) optionValue[oBGM] = 3;
				else optionValue[oBGM] = 2;
			}
			else optionValue[oBGM] = 1;

			if (onSND == true) optionValue[oSOUND] = 2;
			else optionValue[oSOUND] = 1;

			if (isWindowed == true) optionValue[oWINDOWED] = 1;
			else optionValue[oWINDOWED] = 2;

			for (size_t i = 0; i < m_manyButtons.size() - 1; i++)
				m_manyButtons[i][optionValue[i]]->m_isOn = true;
			SOUND->Play("th_01_%s", true, true);
			break;
		case oQUIT:
			m_manyButtons[m_nowLine][0]->m_isOn = false;
			SCENE->ChangeScene("titleScene");

			//���� �� ���� ������
			FILEMANAGER->OptionSave();
			return;
			break;
		}
	}

	if (KEYDOWN(DIK_ESCAPE) || KEYDOWN(DIK_X)) {
		SOUND->Copy("cancelSND");
		m_manyButtons[m_nowLine][0]->m_isOn = false;
		m_manyButtons[oQUIT][0]->m_isOn = true;
		m_nowLine = oQUIT;
	}

	Lerp<int>(m_rgb, 255, 0.05);
}

void cOptionScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0), 1.f, 0.f, false, D3DCOLOR_ARGB(m_rgb, m_rgb, m_rgb, m_rgb));

	for (auto iter : m_manyButtons)
		for(auto jter : iter)
			jter->Render();
}

void cOptionScene::Release()
{
}
