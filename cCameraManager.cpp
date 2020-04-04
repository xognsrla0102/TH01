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

void cCameraManager::ResetCamera()
{
	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0.f, WINSIZEX, WINSIZEY, 0.f, 0.f, 1.f);
	g_device->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCameraManager::Update()
{
	DEBUG_LOG("%d %d\n", m_isShake, m_isPause);

	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	if (m_isShake == TRUE && m_isPause == FALSE)
		Shake();

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, 0.f);

	m_matView = matS * matT;
}

void cCameraManager::SetTransform()
{
	//�� ��� ����
	g_device->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCameraManager::ResetSetting()
{
	if (m_velocity < 0) m_velocity = -m_velocity;
	m_accel = 1;
	m_pos = VEC2(0, 0);
}

void cCameraManager::Shake()
{
	if (timeGetTime() - start > m_delay) {
		m_pos.x = rand() % m_accel - rand() % m_accel;
		m_pos.y = rand() % m_accel - rand() % m_accel;
		m_accel += m_velocity;
		start = timeGetTime();
	}
	
	if (m_accel > 40) {
		m_accel = 40;
		m_velocity = -m_velocity;
	}
	else if (m_accel < 1) {
		ResetSetting();
		m_isShake = FALSE;
	}
}
