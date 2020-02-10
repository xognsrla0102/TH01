#pragma once
#include "cObject.h"

class cBullet;
class cPlayer : public cObject
{
public:
	cTimer* m_bulletTimer = nullptr;

	string pStatus[2][3] = {
		{
			"player_marisa_idle",
			"player_marisa_left",
			"player_marisa_right"
		},
		{
			"player_reimou_idle",
			"player_reimou_left",
			"player_reimou_right"
		}
	};
	bool isHit = false;

	int nowPlayerStatus = pIDLE;
public:
	cPlayer();
	~cPlayer();

	void Update();
	void Render();
};

