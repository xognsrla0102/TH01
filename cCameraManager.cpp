#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
	//LookAt 함수로 카메라의 기본 위치와 바라보는 방향을 정할 필요가 없음
	//2D니까.. 그냥 기본상태(정면)보면 됨.
	//항등항렬로 설정해두고 확대축소, 이동처리만 해서 뷰행렬에 전달하면 됨

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	//직교 투영

	//z Near Plane = 0.f
	//z Far Plane = 1.f

	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0.f, WINSIZEX, WINSIZEY, 0.f, 0.f, 1.f);

	//투영행렬 적용
	g_device->SetTransform(D3DTS_PROJECTION, &m_matProj);

	//투시 투영
	//Perspective Projection

	//등각 투영
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
	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	if (m_isShake) Shake();

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, 0.f);

	m_matView = matS * matT;
}

void cCameraManager::SetTransform()
{
	//뷰 행렬 설정
	g_device->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCameraManager::Shake()
{
	if (m_isShake == FALSE) return;

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
		m_accel = 1;
		m_velocity = -m_velocity;
		m_pos = VEC2(0, 0);
		m_isShake = FALSE;
	}
}
