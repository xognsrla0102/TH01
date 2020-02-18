#pragma once
#include "cObject.h"

class cBullet;
class cBulletAdmin : public cObject
{
private:
	vector<cBullet*> m_playerBullet;
	vector<cBullet*> m_ballBullet;
public:
	cBulletAdmin() {}
	virtual ~cBulletAdmin();

	virtual void Update() override;
	virtual void Render() override;
	void Release();

	vector<cBullet*>& GetPlayerBullet() { return m_playerBullet; }
	vector<cBullet*>& GetBallBullet() { return m_ballBullet; }
};

