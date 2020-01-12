#pragma once
#include "cSingleton.hpp"

using namespace TAGS;

class cObject;
class cObjectManager : public cSingleton<cObjectManager>
{
private:
	vector<cObject*> m_objs[TAG_END];
public:
	cObjectManager();
	virtual ~cObjectManager();

	void AddOBJ(cObject* obj, int tagNum);

	void Update();
	void Render();
};

#define OBJECT cObjectManager::GetInst()
#define OBJADD(i, j) OBJECT->AddOBJ(i, j);
