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
	memcpy(oldKey, nowKey, sizeof(nowKey));
	memset(nowKey, false, sizeof(nowKey));

	keyboard->GetData();

	for (int i = 0; i < 256; i++)
		if (keyboard->KeyDown(i))
			nowKey[i] = true;
}

BOOL cInputManager::KeyDown(BYTE key)
{
	return (!oldKey[key] && nowKey[key]);
}

BOOL cInputManager::KeyUp(BYTE key)
{
	return (oldKey[key] && !nowKey[key]);
}

BOOL cInputManager::KeyPress(BYTE key)
{
	return (oldKey[key] && nowKey[key]);
}
