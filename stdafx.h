#pragma once

#include <iostream>
#include <dinput.h>
#include <vector>
#include <map>
using namespace std;

using VEC2 = D3DXVECTOR2;
using VEC3 = D3DXVECTOR3;
using VEC4 = D3DXVECTOR4;

#define D_TIME DXUTGetElapsedTime()
#define g_device DXUTGetD3D9Device()

#define WINSIZEX 1280
#define WINSIZEY 720

struct NEMO {
	double left, top, height, width, rot;
};

#ifdef _DEBUG
	void DEBUG_LOG(LPCSTR fmt, ...);
#endif

#include "cImageManager.h"
#include "cSceneManager.h"
#include "cInputManager.h"
//STL의 clear 함수는 값만 비워주지 포인터가 가르키는 곳까지 해제해주진 않으므로
//모든 원소에 접근해서 SAFE_DELETE 해줘야함. 포인터 시퀀스가 아니라면 굳이 일일이 SAFE_DELETE 해줄 필요없음