#include "DXUT.h"
#include "cPath.h"

cPath::cPath(VEC2 startPos)
{
	AddPoint(startPos, 1, 0);
}

cPath::~cPath()
{
	m_endPoint.clear();
}

void cPath::AddPoint(VEC2 newPos, FLOAT speed, FLOAT delay)
{
	//스피드가 0일 경우 delay만큼 현재 위치 유지
	//딜레이가 0일 경우 스피드만큼 현재 위치 Lerp
	m_endPoint.push_back(cPointInfo(newPos, speed, delay));
}

void cPath::AddCurve(VEC2 curvePos, VEC2 endPos) {
	return;
}

BOOL cPath::Update(VEC2 pos)
{
	//현재지점과 목표 지점까지의 거리
	FLOAT d = DistPoint(pos, m_endPoint[m_nowPos].m_pos);
	
	//최종지점에 도착했을 경우
	if (m_isDone == TRUE) return FALSE;
	//목표 지점이 최종지점이고 최종지점에 도달했을 때
	else if (m_nowPos == m_endPoint.size() - 1 && d < 1.f) {
		m_isDone = TRUE;
		return FALSE;
	}
	//현재 지점과 목표지점의 거리차이가 1.f 미만일 때
	else if (d < 1.f) {
		//딜레이가 존재해서 정지한 상태로 딜레이 만큼 유지하거나
		if (m_endPoint[m_nowPos].m_delay != 0)
			if (timeGetTime() - m_stay < m_endPoint[m_nowPos].m_delay)
				return FALSE;
		//Lerp한 후의 거리차이가 0.01f 미만이 된거라면 다음 포인트로 옮겨주는게 맞음
		m_nowPos++;
		m_stay = timeGetTime();
		//목표지점으로 이동시켜주는 신호를 보내야 함
		//그 신호를 TRUE를 반환함으로써 구분
		return TRUE;
	}
	else return FALSE;
}
