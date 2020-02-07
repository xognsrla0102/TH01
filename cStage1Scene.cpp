#include "DXUT.h"
#include "cStage1Scene.h"

cStage1Scene::cStage1Scene()
{
}

cStage1Scene::~cStage1Scene()
{
}

void cStage1Scene::Init()
{
	OBJFIND(PLAYER)->SetPos(VEC2(WINSIZEX / 2, 650));
}

void cStage1Scene::Update()
{
	OBJFIND(PLAYER)->Update();
}

void cStage1Scene::Render()
{
	OBJFIND(PLAYER)->Render();
}

void cStage1Scene::Release()
{
}
