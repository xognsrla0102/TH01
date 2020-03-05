#pragma once

class cPath
{
public:
	vector<VEC2> m_endPos;
	INT m_nowPos = 0;
	BOOL isDone = FALSE;
public:
	cPath(VEC2 startPos);
	~cPath();

	void AddPoint(VEC2 newPos);
	void Update();
};

