#pragma once
#include "cObject.h"

class cBullet;
class cBulletAdmin : public cObject
{
private:
	vector<cBullet*> m_playerBullet;
public:
	cBulletAdmin() {}
	~cBulletAdmin();

	virtual void Update() override;
	virtual void Render() override;

	vector<cBullet*>& GetPlayerBullet() { return m_playerBullet; }
};

