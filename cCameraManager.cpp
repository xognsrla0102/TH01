#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
	//LookAt �Լ��� ī�޶��� �⺻ ��ġ�� �ٶ󺸴� ������ ���� �ʿ䰡 ����
	//2D�ϱ�.. �׳� �⺻����(����)���� ��.
	//�׵��׷ķ� �����صΰ� Ȯ�����, �̵�ó���� �ؼ� ����Ŀ� �����ϸ� ��

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	//���� ����

	//z Near Plane = 0.f
	//z Far Plane = 1.f
	D3DXMatrixOrthoLH(&m_matProj, WINSIZEX, -WINSIZEY, 0.f, 1.f);

	//���� ����
	//Perspective Projection

	//� ����
	//Isometric Projection
}

cCameraManager::~cCameraManager()
{
}

void cCameraManager::Update()
{
	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_size, m_size, 0.f);

	D3DXMatrixTranslation(&matT, -m_pos.x, -m_pos.y, 0.f);

	//����Ŀ��� ī�޶��� �̵������ ����
	m_matView = matS * matT;
}

void cCameraManager::SetTransform()
{
	//�� ��� ����
	g_device->SetTransform(D3DTS_VIEW, &m_matView);
	//���� ��� ����
	g_device->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCameraManager::Shake()
{
}
