#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include <stdarg.h>
using namespace std;

class D3DXVECTOR2;
class D3DXVECTOR3;
class D3DXVECTOR4;

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