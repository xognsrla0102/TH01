#pragma once
#include "cScene.h"

class cButton;
class cOptionScene : public cScene
{
private:
	cTexture* m_BG = nullptr;

	vector<vector<cButton*> > m_manyButtons;
	//2���� �迭�� ��ư ����
	vector<cButton*> m_buttons;
	//�� �ٸ��� ��ư �ְ� 2���� �迭�� �־���

	vector<int> optionValue;
	//�� ���θ��� ������ ��

	int m_nowLine = 0;

public:
	cOptionScene();
	virtual ~cOptionScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

