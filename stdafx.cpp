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

bool isMidi = true;
bool onBGM = true;
bool onSND = true;
bool isWindowed = true;