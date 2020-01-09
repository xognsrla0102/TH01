#include "DXUT.h"
#include "cObject.h"
#include "cObjectManager.h"

void cObjectManager::AddOBJ(cObject* obj)
{
	
}

vector<cObject*>& cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum].size()) return m_objs[tagNum];
	else DEBUG_LOG("해당 객체집합이 존재하지 않습니다.\n");
}
