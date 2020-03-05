#pragma once
#include "cObject.h"

class cEnemy;
class cEnemyAdmin : public cObject
{
private:
	vector<cEnemy*> m_ones;
	vector<cEnemy*> m_fairys;
public:
	cEnemyAdmin();
	~cEnemyAdmin();

	virtual void Update() override;
	virtual void Render() override;
	void Release();

	vector<cEnemy*>& GetOne() { return m_ones; }
	vector<cEnemy*>& GetFairy() { return m_fairys; }
};

