#pragma once
#include "cSingleton.hpp"

class cInput;
class cInputManager : public cSingleton<cInputManager>
{
private:
	cInput* keyboard = nullptr;
public:
	cInputManager();
	virtual ~cInputManager();

	void Update();
	BOOL KeyDown(BYTE key);
};

#define INPUT cInputManager::GetInst()