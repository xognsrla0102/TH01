#pragma once

#include <iostream>
#include <string>
#include <direct.h>
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

enum TAGS{
	BG,
	UI,
	PLAYER,
	ENEMY,
	BULLET,
	TAG_END
};

enum INTRO_POS {
	START_POS,
	MID_POS,
	LEFT_POS,
	FADE_OUT_POS
};

enum TITLE_BUTTON {
	tSTART,
	tHOWTO,
	tREPLAY,
	tSCORE,
	tMUSIC,
	tOPTION,
	tEXIT
};

enum OPTION_BUTTON {
	oLIFE,
	oBOMB,
	oBGM,
	oSOUND,
	oWINDOWED,
	oRESTORE,
	oQUIT,
	oBUTTON_END
};

extern int playerLife;
extern int playerBomb;
extern bool isMidi;
extern bool onBGM;
extern bool onSND;
extern bool isWindowed;

template <typename T>
void Lerp(T& start, T end, float t) {
	start = start + t * (end - start);
}

#ifdef _DEBUG
	void DEBUG_LOG(LPCSTR fmt, ...);
#endif

#include "SDKsound.h"
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "cSoundManager.h"
#include "cFileManager.h"
//STL�� clear �Լ��� ��� ������ �������� �����Ͱ� ����Ű�� ������ ���������� �����Ƿ�
//��� ���ҿ� �����ؼ� SAFE_DELETE �������. ������ �������� �ƴ϶�� ���� ������ SAFE_DELETE ���� �ʿ����