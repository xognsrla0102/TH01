#pragma once
class cObject abstract
{
protected:
	VEC2 m_pos;
	VEC2 m_size;
	FLOAT m_rot = 0.f;
	BOOL m_isLive = TRUE;
	int m_tag;
public:
	cObject() {}
	virtual ~cObject() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	int GetTag() { return m_tag; }
	VEC2 GetPos() { return m_pos; }
	VEC2 GetSize() { return m_size; }
	FLOAT GetRot() { return m_rot; }
	BOOL GetLive() { return m_isLive; }

	void SetTag(int tagNum) { m_tag = tagNum; }
	void SetPos(VEC2 pos) { m_pos = pos; }
	void SetSize(VEC2 size) { m_size = size; }
	void SetRot(FLOAT rot) { m_rot = rot; }
	void SetLive(BOOL isLive) { m_isLive = isLive; }
};

