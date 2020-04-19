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
#else 
void DEBUG_LOG(LPCSTR fmt, ...) {}
#endif

INT playerLife = 3;
INT playerBomb = 3;

BOOL onBGM = TRUE;
BOOL isMidi = FALSE;
BOOL onSND = TRUE;

BOOL isWindowed = TRUE;

BOOL isExtra = FALSE;

BOOL isMarisa = FALSE;
BOOL isB = FALSE;

BOOL extraMode = FALSE;