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
	FONT->ReleaseInst();
	FILEMANAGER->ReleaseInst();
}

void cMain::Update()
{
	CAMERA->Update();
	INPUT->Update();
	SCENE->Update();
	FONT->Update();
}

void cMain::Render()
{
	//sprite�� Begin �ϱ� ���� ī�޶� �� ����� ���������
	//Begin�� �� �� (D3DXSPRITE_OBJECTSPACE ������ �� ��)
	//�� ����� �����ؼ� ī�޶� �������� �̹����� ���� ��ǥ�� ������(������ ��ǥ�� �ƴ�)
	CAMERA->SetTransform();

	IMAGE->Begin(FALSE);

	SCENE->Render();
	FONT->Render();

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
