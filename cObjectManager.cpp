#include "DXUT.h"
#include "cObject.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
}

cObjectManager::~cObjectManager()
{
	for (auto iter : m_objs)
		SAFE_DELETE(iter);
}

void cObjectManager::AddOBJ(cObject* obj, int tagNum)
{
	if (m_objs[tagNum] == nullptr)
		DEBUG_LOG("찾는 태그가 없어유...\n");
	m_objs[tagNum] = obj;
}

cObject* cObjectManager::FindOBJ(int tagNum)
{
	return m_objs[tagNum];
}

