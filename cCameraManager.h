#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	//���� �������� ���ƺ���
	//Ȯ�� ��ҳ�
	//ȭ�� ���� ȿ�� ���� �ۿ� �� ��

	D3DXMATRIX m_matView;
	//���� ��� ó��
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