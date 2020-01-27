#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	//직교 투영에선 많아봤자
	//확대 축소나
	//화면 흔드는 효과 정도 밖에 안 씀

	D3DXMATRIX m_matView;
	//투영 행렬 처리
	D3DXMATRIX m_matProj;

	VEC2 m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);

	float m_size = 1.f;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void Update();
	void SetTransform();

	void Shake();
};

#define CAMERA cCameraManager::GetInst()