#include "DXUT.h"
#include "cLoadScene.h"
#include "cMain.h"

cMain::cMain()
{
	SCENE->AddScene("loadScene", new cLoadScene);
	SCENE->ChangeScene("loadScene");
}

cMain::~cMain()
{
	cInputManager::ReleaseInst();
	cSceneManager::ReleaseInst();
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
