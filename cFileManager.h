#pragma once
#include "cSingleton.hpp"

class cFileManager : public cSingleton<cFileManager>
{
private:
	FILE* m_writeInfo = nullptr;
	FILE* m_readInfo = nullptr;
public:
	cFileManager() {}
	virtual ~cFileManager() {
		if (m_writeInfo != nullptr) fclose(m_writeInfo);
		if (m_readInfo != nullptr) fclose(m_readInfo);
	}

	void WriteFile(const string fileName, const string text);
	bool MakeDir(const string dirPath);
	string ReadFile(const string path);
	
	void OptionLoad();
	void OptionSave();
};

#define FILEMANAGER cFileManager::GetInst()