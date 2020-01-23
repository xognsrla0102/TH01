#include "DXUT.h"
#include "cButton.h"

cButton::cButton(const string& key, VEC2 size) : m_key(key)
{
	m_size = size;
	m_img = IMAGE->FindImage(key);
	oldSize = m_size.x;
}

void cButton::Update()
{
	if (m_isOn) {
		Lerp(m_alpha, 255, 0.25);
		Lerp(m_size, VEC2(oldSize + 0.5f, oldSize + 0.5f), 0.25);
	}
	else {
		Lerp(m_alpha, 150, 0.25);
		Lerp(m_size, VEC2(oldSize, oldSize), 0.25);
	}
}

void cButton::Render()
{
	IMAGE->Render(m_img, m_pos, m_size.x, m_rot, true, D3DCOLOR_ARGB(m_alpha, m_alpha, m_alpha, m_alpha));
}
