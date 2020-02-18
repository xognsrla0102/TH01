#pragma once
class cPath
{
private:
	vector<VEC2> m_endPos;
public:
	cPath() {}
	~cPath();

	void AddPos(VEC2 pos);
	void ErasePos(INT idx);
	void ResetPath();
};

