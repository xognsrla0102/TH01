#pragma once

#include <iostream>
#include <string>
#include <direct.h>
#include <dinput.h>
#include <time.h>
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

#define INGAMEX 745
#define INGAMEY 620

enum TAGS {
	PLAYER,
	BALLS,
	ITEMS,
	ENEMYS,
	BULLETS,
	TAG_END
};

enum BOOK_COLOR {
	BOOK_RED,
	BOOK_GREEN,
	BOOK_PINK
};

enum FAIRY_COLOR {
	FAIRY_RED,
	FAIRY_ORANGE,
	FAIRY_GREEN,
	FAIRY_BLUE,
	FAIRY_PURPLE
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

enum PLAYER_STATUS {
	pIDLE,
	pLEFT,
	pRIGHT
};

extern INT  playerLife;
extern INT  playerBomb;
extern BOOL isMidi;
extern BOOL onBGM;
extern BOOL onSND;
extern BOOL isWindowed;
extern BOOL isExtra;
extern BOOL isMarisa;
extern BOOL isB;
extern BOOL extraMode;

template <typename T>
void Lerp(T& start, T end, float t) {
	//70은 델타타임 조정값
	start = start + t * (end - start) * D_TIME * 70;
}

FLOAT DistPoint(VEC2 a, VEC2 b);

#ifdef _DEBUG
	void DEBUG_LOG(LPCSTR fmt, ...);
#else
	void DEBUG_LOG(LPCSTR fmt, ...);
#endif

#include "SDKsound.h"
#include "collision.h"
#include "cTexture.h"
#include "cMultiTexture.h"
#include "cImage.h"
#include "cAnimation.h"
#include "cEffect.h"
#include "cPath.h"
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "cSoundManager.h"
#include "cEffectManager.h"
#include "cFileManager.h"
#include "cCameraManager.h"
#include "cFontManager.h"
//STL의 clear 함수는 요소 갯수를 지워주지 포인터가 가르키는 곳까지 해제해주진 않으므로
//포인터 시퀀스라면 모든 원소에 접근해서 SAFE_DELETE 해줘야함.
//포인터 시퀀스가 아니라면 굳이 일일이 SAFE_DELETE 해줄 필요없음