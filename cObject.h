#pragma once
class cObject abstract
{
protected:
	cTexture*	m_img	= nullptr;
	VEC2		m_pos	= VEC2(0, 0);
	VEC2		m_size	= VEC2(1, 1);
	FLOAT		m_rot	= 0.f;
	FLOAT		m_speed = 0.f;
	BOOL		m_isLive= TRUE;
	INT			m_tag	= -1;
public:
	cObject() {}
	virtual ~cObject() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	INT GetTag() { return m_tag; }
	VEC2 GetPos() { return m_pos; }
	VEC2 GetSize() { return m_size; }
	FLOAT GetRot() { return m_rot; }
	BOOL GetLive() { return m_isLive; }

	void SetTag(INT tagNum) { m_tag = tagNum; }
	void SetPos(VEC2 pos) { m_pos = pos; }
	void SetSize(VEC2 size) { m_size = size; }
	void SetRot(FLOAT rot) { m_rot = rot; }
	void SetLive(BOOL isLive) { m_isLive = isLive; }
};

