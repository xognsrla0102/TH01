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
	INPUT->ReleaseInst();
	SCENE->ReleaseInst();
	OBJECT->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
	CAMERA->ReleaseInst();
	FILEMANAGER->ReleaseInst();
}

void cMain::Update()
{
	CAMERA->Update();
	INPUT->Update();
	SCENE->Update();
}

void cMain::Render()
{
	IMAGE->Begin();

	CAMERA->SetTransform();
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
