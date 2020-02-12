#pragma once
#include "cObject.h"

class cTimer;
class cBall : public cObject
{
private:
	cTimer* m_bulletTimer = nullptr;

	VEC2 m_pPos;

	string m_ballImg[2] = {
		"player_reimou_ball",
		"player_marisa_ball"
	};

	string m_bulletImg[2][2] = {
		{
			"player_reimou_subShot0",
			"player_reimou_subShot1"
		},
		{
			"player_marisa_subShot0",
			"player_marisa_subShot1"
		}
	};
	bool m_isLeft = false;
	bool m_isShot = false;

public:
	cBall(VEC2 pos, bool isLeft = false);
	virtual ~cBall();

	virtual void Update() override;
	virtual void Render() override;
	void Release();
};

