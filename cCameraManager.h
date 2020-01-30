#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	D3DXMATRIX m_matView;
	//투영 행렬 처리
	D3DXMATRIX m_matProj;

	VEC2 m_pos = VEC2(0, 0);

	float m_size = 1.f;

public:
	bool m_isShake = false;

public:
	cCameraManager();
	virtual ~cCameraManager();

	void Update();
	void SetTransform();

	void Shake();
};

#define CAMERA cCameraManager::GetInst()