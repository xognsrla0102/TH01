#include "DXUT.h"
#include "cTexture.h"
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

void cImageManager::InsertImage(string name, string path, int cnt)
{
	auto find = m_imgs.find(name);
	if (find != m_imgs.end()) {
		DEBUG_LOG("이미 같은 이름의 이미지가 있네유..\n");
		return;
	}
	cTexture* text;
	if (cnt == 1) text = new cSingleTexture;
	else if (cnt > 1) text = new cMultiTexture;
	else {
		DEBUG_LOG("%d는 cnt에 넣을 수 없어유...\n", cnt);
		return;
	}

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
	if (text) {
		D3DXMATRIXA16 mat, s, r, t;
		D3DXMatrixScaling(&s, size, size, size);
		D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

		mat = s * r * t;
		m_sprite->SetTransform(&mat);
		if (center)
			m_sprite->Draw(text->m_text, nullptr, &VEC3(text->m_info.Width / 2, text->m_info.Height / 2, 0.f), nullptr, color);
		else
			m_sprite->Draw(text->m_text, nullptr, nullptr, nullptr, color);
	}
	else DEBUG_LOG("텍스쳐가 비었소\n");
}

void cImageManager::CenterRender(cTexture* text, VEC2 pos, VEC2 center, float size, float rot, D3DCOLOR color)
{
	if (text) {
		D3DXMATRIXA16 mat, s, r, t;
		D3DXMatrixScaling(&s, size, size, size);
		D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

		mat = s * r * t;

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(text->m_text, nullptr, &VEC3(center.x, center.y, 0.f), nullptr, color);
	}
	else DEBUG_LOG("텍스쳐가 비었소\n");
}

