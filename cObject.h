#pragma once

class cObject abstract
{
protected:
	cTexture*		m_img	= nullptr;
	cMultiTexture*	m_imgs  = nullptr;

	cAnimation* m_ani	= nullptr;

	VEC2		m_pos	= VEC2(0.f, 0.f);
	VEC2		m_size	= VEC2(1.f, 1.f);

	FLOAT		m_rot	= 0.f;
	FLOAT		m_speed = 0.f;

	BOOL		m_isLive= TRUE;
public:
	cObject() {}
	virtual ~cObject() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	cTexture* GetImg() { return m_img; }
	VEC2 GetPos() { return m_pos; }
	VEC2 GetSize() { return m_size; }
	FLOAT GetRot() { return m_rot; }
	BOOL GetLive() { return m_isLive; }

	VEC2& GetRefPos() { return m_pos; }
	VEC2& GetRefSize() { return m_size; }
	BOOL& GetRefLive() { return m_isLive; }

	void SetImg(cTexture* img) { m_img = img; }
	void SetPos(VEC2 pos) { m_pos = pos; }
	void SetSize(VEC2 size) { m_size = size; }
	void SetRot(FLOAT rot) { m_rot = rot; }
	void SetLive(BOOL isLive) { m_isLive = isLive; }
};

