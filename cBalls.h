#pragma once
#include "cObject.h"

class cBall;
class cBalls : public cObject
{
private:
	vector<cBall*> m_balls;
public:
	cBalls();
	virtual ~cBalls();

	virtual void Update() override;
	virtual void Render() override;
	void Release();

	vector<cBall*>& GetPlayerBalls() { return m_balls; }
};

