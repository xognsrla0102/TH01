#include "DXUT.h"
#include "cLoadScene.h"
#include "cMain.h"

cMain::cMain()
{
	srand(time(NULL));
	SCENE->AddScene("loadScene", new cLoadScene);
	SCENE->ChangeScene("loadScene");
}

cMain::~cMain()
{
	INPUT->ReleaseInst();
	SCENE->ReleaseInst();
	EFFECT->ReleaseInst();
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
	//sprite를 Begin 하기 전에 카메라 뷰 행렬을 적용해줘야
	//Begin을 할 때 (D3DXSPRITE_OBJECTSPACE 설정을 할 때)
	//뷰 행렬을 무시해서 카메라를 움직여도 이미지는 월드 좌표에 고정됨(윈도우 좌표가 아님)
	CAMERA->SetTransform();

	IMAGE->Begin(FALSE);

	SCENE->Render();

	IMAGE->End();
}

void cMain::LostDevice()
{
	IMAGE->LostDevice();
}

void cMain::ResetDevice()
{
	CAMERA->ResetCamera();
	IMAGE->ResetDevice();
}
