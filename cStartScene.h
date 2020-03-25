#pragma once
#include "cScene.h"

class cButton;
class cModeButton {
public:
	cButton* m_button = nullptr;
	vector<VEC2> m_butEndPos;
};

class cStartScene : public cScene
{
private:
	cTexture* m_mode = nullptr;
	cTexture* m_char = nullptr;
	cTexture* m_weapon = nullptr;

	vector<cModeButton*> m_buttons;
	vector<cButton*> m_charButtons;

	vector<cButton*> m_charWeapon[2];

	INT m_nowButton = 0;
	INT m_nowButPosState = mSTART_POS;

	INT m_charButton = 0;
	INT m_weaponButton = 0;

	INT m_nowEnter = 0;

	BOOL m_isNextEnter[3] = { FALSE };
	BOOL isCharUp = FALSE;
	BOOL isCharDown = FALSE;
public:
	cStartScene();
	virtual ~cStartScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

