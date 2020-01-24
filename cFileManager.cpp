#include "DXUT.h"
#include "cFileManager.h"

void cFileManager::WriteFile(const string& fileName, const string& text)
{
	_mkdir("./gameInfo");

	char path[256] = "./gameInfo/%s.txt";
	sprintf(path, path, fileName.c_str());

	m_writeInfo = fopen(path, "wt+");

	fputs(text.c_str(), m_writeInfo);

	fclose(m_writeInfo);
}

string cFileManager::ReadFile(const string& path)
{
	char str[256];

	m_readInfo = fopen(path.c_str(), "rt+");

	fgets(str, sizeof(str), m_readInfo);

	fclose(m_readInfo);

	return string(str);
}
