#include "DXUT.h"


#ifdef _DEBUG
void DEBUG_LOG(LPCSTR fmt, ...) {
	char buf[200];
	va_list list;
	va_start(list, fmt);
	vsprintf(buf, fmt, list);
	va_end(list);
	OutputDebugStringA(buf);
}
#endif

int playerLife = 3;
int playerBomb = 3;

bool onBGM = true;
bool isMidi = false;

bool onSND = true;

bool isWindowed = true;

bool isExtra = false;

bool character[2][2] = { false };