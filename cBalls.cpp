#include "DXUT.h"
#include "cBall.h"
#include "cBalls.h"

cBalls::cBalls()
{
}

cBalls::~cBalls()
{
	Release();
}

void cBalls::Update()
{
	for (auto iter : m_balls)
		iter->Update();
}

void cBalls::Render()
{
	for (auto iter : m_balls)
		iter->Render();
}

void cBalls::Release()
{
	for (auto iter : m_balls)
		SAFE_DELETE(iter);
	m_balls.clear();
}
