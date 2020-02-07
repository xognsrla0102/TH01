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
	if (m_objs[tagNum] == nullptr) m_objs[tagNum] = obj;
	else DEBUG_LOG("�̹� ���� �̸��� �±װ� �־���...\n");
}

cObject* cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum] == nullptr)
		DEBUG_LOG("ã�� �±װ� ������...\n");
	return m_objs[tagNum];
}

