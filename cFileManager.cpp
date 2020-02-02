#include "DXUT.h"
#include "cFileManager.h"

void cFileManager::WriteFile(const string fileName, const string text)
{
	char path[256];

	sprintf(path, "./gameInfo/%s.txt", fileName.c_str());

	m_writeInfo = fopen(path, "wt+");

	fputs(text.c_str(), m_writeInfo);

	fclose(m_writeInfo);
}

bool cFileManager::MakeDir(const string dirPath)
{
	if (_mkdir(dirPath.c_str()) == 0) return true;
	return false;
}

string cFileManager::ReadFile(const string path)
{
	char str[256];

	m_readInfo = fopen(path.c_str(), "rt+");

	fgets(str, sizeof(str), m_readInfo);

	fclose(m_readInfo);

	return string(str);
}

void cFileManager::OptionLoad()
{
	playerLife = stoi(FILEMANAGER->ReadFile("./gameInfo/LifeInfo.txt"));
	playerBomb = stoi(FILEMANAGER->ReadFile("./gameInfo/BombInfo.txt"));
	onBGM = stoi(FILEMANAGER->ReadFile("./gameInfo/BGMInfo.txt"));
	isMidi = stoi(FILEMANAGER->ReadFile("./gameInfo/MidiInfo.txt"));
	onSND = stoi(FILEMANAGER->ReadFile("./gameInfo/SoundInfo.txt"));
	isWindowed = stoi(FILEMANAGER->ReadFile("./gameInfo/WinModeInfo.txt"));
	isExtra = stoi(FILEMANAGER->ReadFile("./gameInfo/ExtraInfo.txt"));
}

void cFileManager::OptionSave()
{
	FILEMANAGER->WriteFile("LifeInfo", to_string(playerLife));
	FILEMANAGER->WriteFile("BombInfo", to_string(playerBomb));
	FILEMANAGER->WriteFile("BGMInfo", to_string(onBGM));
	FILEMANAGER->WriteFile("MidiInfo", to_string(isMidi));
	FILEMANAGER->WriteFile("SoundInfo", to_string(onSND));
	FILEMANAGER->WriteFile("WinModeInfo", to_string(isWindowed));
	FILEMANAGER->WriteFile("ExtraInfo", to_string(isExtra));
}
