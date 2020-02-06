#pragma once
#include "cSingleton.hpp"

class cObject;
class cObjectManager : public cSingleton<cObjectManager>
{
private:
	cObject* m_objs[TAG_END] = { 0 };
public:
	cObjectManager();
	virtual ~cObjectManager();

	void AddOBJ(cObject* obj, int tagNum);
	cObject* FindOBJ(int tagNum);
};

#define OBJECT cObjectManager::GetInst()
#define OBJADD(i, j) OBJECT->AddOBJ(i, j)
#define OBJFIND(i) OBJECT->FindOBJ(i)
