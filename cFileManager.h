#pragma once
#include "cSingleton.hpp"

class cFileManager : public cSingleton<cFileManager>
{
private:
	FILE* pFile;
public:
	cFileManager() {}
	virtual ~cFileManager() {
		if(pFile)
			fclose(pFile);
	}

	FILE* FileOpen();
	FILE* GetFile() { return pFile; }
};

#define FILEMANAGER cFileManager::GetInst()