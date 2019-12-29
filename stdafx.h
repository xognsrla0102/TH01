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

//STL의 clear 함수는 비워주기만 하지 포인터가 가르키는 곳까지 없애주진 않으므로
//모든 원소에 접근해서 SAFE_DELETE 해줘야함. 포인터 시퀀스가 아니라면 굳이 일일이 SAFE_DELETE 해줄 필요없음