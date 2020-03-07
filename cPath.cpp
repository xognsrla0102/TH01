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
	//���ǵ尡 0�� ��� delay��ŭ ���� ��ġ ����
	//�����̰� 0�� ��� ���ǵ常ŭ ���� ��ġ Lerp
	m_endPoint.push_back(cPointInfo(newPos, speed, delay));
}

void cPath::AddCurve(VEC2 curvePos, VEC2 endPos) {
	return;
}

BOOL cPath::Update(VEC2 pos)
{
	//���������� ��ǥ ���������� �Ÿ�
	FLOAT d = DistPoint(pos, m_endPoint[m_nowPos].m_pos);
	
	//���������� �������� ���
	if (m_isDone == TRUE) return FALSE;
	//��ǥ ������ ���������̰� ���������� �������� ��
	else if (m_nowPos == m_endPoint.size() - 1 && d < 1.f) {
		m_isDone = TRUE;
		return FALSE;
	}
	//���� ������ ��ǥ������ �Ÿ����̰� 1.f �̸��� ��
	else if (d < 1.f) {
		//�����̰� �����ؼ� ������ ���·� ������ ��ŭ �����ϰų�
		if (m_endPoint[m_nowPos].m_delay != 0)
			if (timeGetTime() - m_stay < m_endPoint[m_nowPos].m_delay)
				return FALSE;
		//Lerp�� ���� �Ÿ����̰� 0.01f �̸��� �ȰŶ�� ���� ����Ʈ�� �Ű��ִ°� ����
		m_nowPos++;
		m_stay = timeGetTime();
		//��ǥ�������� �̵������ִ� ��ȣ�� ������ ��
		//�� ��ȣ�� TRUE�� ��ȯ�����ν� ����
		return TRUE;
	}
	else return FALSE;
}
