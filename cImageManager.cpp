#include "DXUT.h"
#include "cSingleTexture.h"
#include "cMultiTexture.h"
#include "cImageManager.h"

cImageManager::cImageManager()
{
	D3DXCreateSprite(g_device, &m_sprite);
}

cImageManager::~cImageManager()
{
	SAFE_RELEASE(m_sprite);

	for (auto iter : m_imgs)
		SAFE_DELETE(iter.second);
	m_imgs.clear();
}

void cImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

void cImageManager::AddImage(string name, string path, int cnt)
{
	auto find = m_imgs.find(name);
	if (find != m_imgs.end()) {
		DEBUG_LOG("이미 같은 이름의 이미지가 있네유..\n");
		return;
	}
	cTexture* text;
	if (cnt == 0) text = new cSingleTexture;
	else text = new cMultiTexture();
	text->AddImage(path, cnt);
	m_imgs.insert(map<string, cTexture*>::value_type(name, text));
}

cTexture* cImageManager::FindImage(string name, int cnt)
{
	auto find = m_imgs.find(name);
	if (find == m_imgs.end()) {
		DEBUG_LOG("찾는 이미지가 없어유..\n");
		return nullptr;
	}
	return find->second->FindImage(cnt);
}

void cImageManager::Render(cTexture* text, VEC2 pos, float size, float rot, D3DCOLOR color, bool center)
{
}

void cImageManager::CenterRender(cTexture* text, VEC2 pos, VEC2 center, float size, float rot, D3DCOLOR color)
{
}

