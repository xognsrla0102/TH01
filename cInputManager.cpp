#include "DXUT.h"
#include "cInput.h"
#include "cInputManager.h"

cInputManager::cInputManager()
{
	keyboard = new cInput(DXUTGetHWND());
}

cInputManager::~cInputManager()
{
	SAFE_DELETE(keyboard);
}

void cInputManager::Update()
{
	keyboard->GetData();
}

BOOL cInputManager::KeyDown(BYTE key)
{
	return keyboard->KeyDown(key);
}
