#pragma once
#include "cScene.h"

class cButton;
class cMusicScene : public cScene
{
private:
	cTexture* m_bg = nullptr;

	vector<cTexture*> m_comments;
	vector<cButton*> m_buttons;
	vector<string> m_musicNames;

	int m_nowLine = 0;
	int m_nowPlayMusic = 0;

public:
	cMusicScene();
	virtual ~cMusicScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

