#pragma once
#include "cObject.h"

class cItem;
class cItemAdmin : public cObject
{
public:
	vector<cItem*> m_items;
public:
	cItemAdmin() {}
	virtual ~cItemAdmin();

	virtual void Update() override;
	virtual void Render() override;
	void Release();
};

