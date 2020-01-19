#include "DXUT.h"
#include "cLoadScene.h"
#include "cMain.h"

cMain::cMain()
{
	isMidi = false;

	SCENE->AddScene("loadScene", new cLoadScene);
	SCENE->ChangeScene("loadScene");
}

cMain::~cMain()
{
	cSoundManager::ReleaseInst();
	cInputManager::ReleaseInst();
	cSceneManager::ReleaseInst();
	cObjectManager::ReleaseInst();
	cImageManager::ReleaseInst();
}

void cMain::Update()
{
	INPUT->Update();
	SCENE->Update();
}

void cMain::Render()
{
	IMAGE->Begin(); 
	SCENE->Render();
	IMAGE->End();
}

void cMain::LostDevice()
{
	IMAGE->LostDevice();
}

void cMain::ResetDevice()
{
	IMAGE->ResetDevice();
}
