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

	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0.f, WINSIZEX, WINSIZEY, 0.f, 0.f, 1.f);

	//������� ����
	g_device->SetTransform(D3DTS_PROJECTION, &m_matProj);

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

	if (m_isShake) Shake();

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, 0.f);

	m_matView = matS * matT;
}

void cCameraManager::SetTransform()
{
	//�� ��� ����
	g_device->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCameraManager::Shake()
{
	static time_t start2 = timeGetTime();

	static int accel = 1.f;
	static int dir = 1.f;

	if (timeGetTime() - start2 > 30) {
		m_pos.x = rand() % accel - rand() % accel;
		m_pos.y = rand() % accel - rand() % accel;
		accel += dir;
		start2 = timeGetTime();
	}
	
	if (accel > 30) {
		accel = 30;
		dir = -dir;
	}

	else if (accel < 1) {
		accel = 1;
		dir = -dir;
		m_isShake = false;
	}
}
