#include "DXUT.h"
#include "cObject.h"
#include "cObjectManager.h"

void cObjectManager::AddOBJ(cObject* obj)
{
	
}

vector<cObject*>& cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum].size()) return m_objs[tagNum];
	else DEBUG_LOG("�ش� ��ü������ �������� �ʽ��ϴ�.\n");
}
