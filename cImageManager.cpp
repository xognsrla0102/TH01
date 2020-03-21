#include "DXUT.h"
#include "cMultiTexture.h"
#include "cImageManager.h"

cImageManager::cImageManager()
{
	D3DXCreateSprite(g_device, &m_sprite);

	D3DXCreateFont(
		g_device,
		20,
		0,
		FW_NORMAL,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Arial",
		&m_font
	);
}

cImageManager::~cImageManager()
{
	SAFE_RELEASE(m_sprite);
	m_font->Release();

	for (auto iter : m_imgs)
		SAFE_DELETE(iter.second);
	m_imgs.clear();
}

void cImageManager::Begin(bool isUI)
{
	if (isUI) {
		//OBJECTSPACE�� �������� ���� ��� �̹����� ������ ��ǥ �������� �׷�����.
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else {
		//OBJECTSPACE�� �����ϸ� ī�޶� �����̴��� �̹����� ������ ��ǥ ������ �ƴ�
		//���� ��ǥ �������� �׷�����.
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	}
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::ReBegin(bool isUI)
{
	End();
	Begin(isUI);
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
		DEBUG_LOG("�̹� ���� �̸��� �̹����� �ֳ���..\n");
		return;
	}
	else if(cnt < 0) {
		DEBUG_LOG("%d�� cnt�� ���� �� ������...\n", cnt);
		return;
	}

	cMultiTexture* text = new cMultiTexture;
	text->AddImage(path, cnt);
	m_imgs[name] = text;
}

cTexture* cImageManager::FindImage(string name, int cnt)
{
	auto find = m_imgs.find(name);
	if (find == m_imgs.end()) {
		DEBUG_LOG("ã�� �̹����� ������..\n");
		return nullptr;
	}
	return find->second->FindImage(cnt);
}

void cImageManager::Render(cTexture* text, VEC2 pos, float size, float rot, bool center, D3DCOLOR color)
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
	else DEBUG_LOG("�ؽ��İ� �����\n");
}

void cImageManager::Render(cTexture* text, VEC2 pos, VEC2 size, float rot, bool center, D3DCOLOR color)
{
	if (text) {
		D3DXMATRIXA16 mat, s, r, t;
		D3DXMatrixScaling(&s, size.x, size.y, 1.f);
		D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

		mat = s * r * t;
		m_sprite->SetTransform(&mat);
		if (center)
			m_sprite->Draw(text->m_text, nullptr, &VEC3(text->m_info.Width / 2, text->m_info.Height / 2, 0.f), nullptr, color);
		else
			m_sprite->Draw(text->m_text, nullptr, nullptr, nullptr, color);
	}
	else DEBUG_LOG("�ؽ��İ� �����\n");
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
	else DEBUG_LOG("�ؽ��İ� �����\n");
}

void cImageManager::DrawNum(string text, VEC2 pos, FLOAT size)
{
	cTexture* nowImg;
	for (size_t i = 0; i < text.size(); i++) {
		char key[256];
		sprintf(key, "num_%c", text[i]);
		nowImg = FindImage(key);
		Render(nowImg, VEC2(pos.x + (i * 23), pos.y), size);
	}
}

void cImageManager::DrawFrame(string text, VEC2 pos)
{
	cTexture* nowImg;
	for (size_t i = 0; i < 5; i++) {
		if (text[i] == '.')
			nowImg = FindImage("num_dot");
		else {
			char key[256];
			sprintf(key, "num_%c", text[i]);
			nowImg = FindImage(key);
		}
		Render(nowImg, VEC2(pos.x + (i * 20), pos.y), 1.f);
	}
}

void cImageManager::DrawFont(string text, VEC2 pos, D3DCOLOR color)
{
	RECT rt = { pos.x, pos.y, 0, 0 };

	m_font->DrawTextA(
		nullptr,
		text.c_str(),
		-1,
		&rt,
		DT_NOCLIP,
		color
	);
}

