#pragma once
#include "cSingleton.hpp"

class cObject;
class cObjectManager : public cSingleton<cObjectManager>
{
private:
	vector<cObject*> m_objs[5];
public:
};

#define OBJECT cObjectManager::GetInst()
