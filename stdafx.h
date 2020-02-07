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

enum TAGS {
	PLAYER,
	ENEMY,
	EFFECT,
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

enum MODE_BUTTON {
	mLUNATIC,
	mEXTRA
};

enum MODE_BUTPOS {
	mSTART_POS,
	mLEFT_POS,
	mENTER_POS
};

extern int  playerLife;
extern int  playerBomb;
extern bool isMidi;
extern bool onBGM;
extern bool onSND;
extern bool isWindowed;
extern bool isExtra;
extern bool character[2][2];

template <typename T>
void Lerp(T& start, T end, float t) {
	start = start + t * (end - start);
}

#ifdef _DEBUG
	void DEBUG_LOG(LPCSTR fmt, ...);
#endif

#include "SDKsound.h"
#include "cTexture.h"
#include "cAnimation.h"
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "cSoundManager.h"
#include "cFileManager.h"
#include "cCameraManager.h"
//STL의 clear 함수는 요소 갯수를 지워주지 포인터가 가르키는 곳까지 해제해주진 않으므로
//포인터 시퀀스라면 모든 원소에 접근해서 SAFE_DELETE 해줘야함.
//포인터 시퀀스가 아니라면 굳이 일일이 SAFE_DELETE 해줄 필요없음