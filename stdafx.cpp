#include "DXUT.h"

FLOAT DistPoint(VEC2 a, VEC2 b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

#ifdef _DEBUG
void DEBUG_LOG(LPCSTR fmt, ...) {
	char buf[256];
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

bool isMarisa = false;

bool isB = false;