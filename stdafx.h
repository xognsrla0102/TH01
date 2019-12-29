#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

using VEC2 = D3DXVECTOR2;
using VEC3 = D3DXVECTOR3;
using VEC4 = D3DXVECTOR4;

#define D_TIME DXUTGetElapsedTime();
#define g_device DXUTGetD3D9Device()

#define WINSIZEX 1280
#define WINSIZEY 720

#ifdef _DEBUG
	void DEBUG_LOG(LPCSTR fmt, ...);
#endif

#include "cImageManager.h"
#include "cSceneManager.h"
//STL�� clear �Լ��� ���� ������� �����Ͱ� ����Ű�� ������ ���������� �����Ƿ�
//��� ���ҿ� �����ؼ� SAFE_DELETE �������. ������ �������� �ƴ϶�� ���� ������ SAFE_DELETE ���� �ʿ����