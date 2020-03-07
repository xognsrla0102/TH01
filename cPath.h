#pragma once

class cPointInfo {
public:
	VEC2 m_pos;
	FLOAT m_speed;
	FLOAT m_delay;
public:
	cPointInfo(VEC2 newPos, FLOAT speed)
		: m_pos(newPos), m_speed(speed), m_delay(0) {}
	cPointInfo(VEC2 newPos, FLOAT speed, time_t delay)
		: m_pos(newPos), m_speed(speed), m_delay(delay) {}
};

class cPath
{
public:
	vector<cPointInfo> m_endPoint;

	INT m_nowPos = 0;

	BOOL m_isDone = FALSE;

	time_t m_stay;
public:
	cPath(VEC2 startPos);
	~cPath();

	void AddPoint(VEC2 newPos, FLOAT speed, FLOAT delay);
	void AddCurve(VEC2 curvePos, VEC2 endPos);
	BOOL Update(VEC2 pos);
};

