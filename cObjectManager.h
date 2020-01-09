#pragma once
#include "cSingleton.hpp"
using TAGS::TAG_END;

class cObject;
class cObjectManager : public cSingleton<cObjectManager>
{
private:
	vector<cObject*> m_objs[TAG_END];
public:
	void AddOBJ(cObject* obj);
	vector<cObject*>& FindOBJ(int tagNum);
};

#define OBJECT cObjectManager::GetInst()
