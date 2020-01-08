#include "DXUT.h"
#include "cInput.h"

cInput::cInput(HWND hWnd) : m_hWnd(hWnd)
{
	CreateDevice(m_hWnd);
}

cInput::~cInput()
{
	ReleaseInput();
}

HRESULT cInput::CreateDevice(HWND hWnd)
{
	HRESULT hr;

	if(FAILED(hr = DirectInput8Create(
		GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&m_Input, NULL)))
		return hr;

	//Ű���� ��ü ����
	if (FAILED(hr = m_Input->CreateDevice(
		GUID_SysKeyboard, &m_device, NULL)))
		return hr;

	//����ϰ��� �ϴ� ��ü�� ���� ���� (dinput.h�� ���ǵǾ� ����)
	if(FAILED(hr = m_device->SetDataFormat(&c_dfDIKeyboard)))
		return hr;

	//���� ���α׷��� �ý��۰� ��ȣ�ۿ� ����
	if(FAILED(hr = m_device->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE |
		DISCL_NOWINKEY
	)))
		return hr;

	//Ű���� ����� ȹ��
	m_device->Acquire();

	return S_OK;
}

VOID cInput::ReleaseInput()
{
	if (m_device) m_device->Unacquire();
	
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_Input);
}

VOID cInput::OnActivate(WPARAM wParam)
{
	//â����� �� �ٸ� â �����ٰ� �ٽ� �� â ���� ���
	//Ű���� ������� �ٽ� Ȯ���ؾ���

	//���� �޼����� ���°� â Ȱ��ȭ �����̸� Ű���� ����̽��� ������ ���
	if (WA_INACTIVE != wParam && m_device)
		m_device->Acquire();

	//WM_ACTIVATE �� Ȱ��ȭ ��Ȱ��ȭ �� �� ���� �߰�
	//WA_INACTIVE�� wParam�� ���� �� ��Ȱ��ȭ
	//WA_ACTIVE �� ������ Ȱ��ȭ��� ��

}

HRESULT cInput::GetData()
{
	HRESULT hr;

	if (m_device == nullptr)
		return S_OK;
	
	ZeroMemory(m_Keys, sizeof(m_Keys));

	//m_Keys �迭�� ���� �������� ����
	hr = m_device->GetDeviceState(sizeof(m_Keys), m_Keys);

	//����̽��� ���� ������� Ȯ������ ���� ���
	if (FAILED(hr)) {
		do {
			//������� Ȯ���� �� ���� �ݺ�
			hr = m_device->Acquire();
		} while (hr == DIERR_INPUTLOST);
		return S_OK;
	}

	DEBUG_LOG("%d\n", m_Keys[DIK_A]);
	return S_OK;
}

BOOL cInput::KeyDown(BYTE key)
{
	if (m_Keys[key] & 0x80) {
		m_Keys[key] = true;
		return true;
	}
	m_Keys[key] = false;
	return false;
}
