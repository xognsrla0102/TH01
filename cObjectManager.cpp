#include "DXUT.h"
#include "cObject.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
}

cObjectManager::~cObjectManager()
{
	for (auto objIdx : m_objs) {
		for (auto iter : objIdx)
			SAFE_DELETE(iter);
	}
	m_objs->clear();
}

void cObjectManager::AddOBJ(cObject* obj, int tagNum)
{
	obj->SetTag(tagNum);
	m_objs->push_back(obj);
}

void cObjectManager::Update()
{
	for (int i = 0; i < TAG_END; i++) {
		auto& refObjs = m_objs[i];
		for (auto j = refObjs.begin(); j != refObjs.end();) {
			//dead status
			if (!(*j)->GetLive()) {
				SAFE_DELETE(*(j));
				j = refObjs.erase(j);
			}
			else {
				(*j)->Update();
				j++;
			}
		}
	}
}

void cObjectManager::Render()
{
}
