#include "DXUT.h"
#include "cFileManager.h"

FILE* cFileManager::FileOpen()
{
	pFile = fopen("./gameInfo/info.txt", "wt+");
	return nullptr;
}
