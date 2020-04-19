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
	m_endPoint.push_back(cPointInfo(FALSE, newPos, speed, delay));
}

void cPath::AddCurve(VEC2 nowPos, VEC2 curvePos, VEC2 endPos, FLOAT speed) {
	//2�� ������ ��� ���ؼ� �������� ������
	VEC2 p0(nowPos), p1(curvePos), p2(endPos), m0, m1, b;

	m0 = p0, m1 = p1;

	//��� 20���
	for (size_t i = 1; i <= 20; i++) {
		D3DXVec2Lerp(&m0, &p0, &p1, 0.05 * i);
		D3DXVec2Lerp(&m1, &p1, &p2, 0.05 * i);
		D3DXVec2Lerp(&b, &m0, &m1, 0.05 * i);

		m_endPoint.push_back(cPointInfo(TRUE, b, speed, 0));
	}
}

BOOL cPath::Update(VEC2 pos, FLOAT moveDist)
{
	//���������� ��ǥ ���������� �Ÿ�
	FLOAT d = DistPoint(pos, m_endPoint[m_nowPos].m_pos);

	//���� �Ÿ��� �̵��� �Ÿ����� ���� �� �Ǵ�
	//���� �Ÿ��� 5.f �̸��� ��
	if (d <= moveDist || d < 5.f) {
		//��ǥ ������ ���������� ��
		if (m_nowPos == m_endPoint.size() - 1) {

			if (m_isLoop == TRUE) {
				//m_nowPos++; �̹Ƿ� 0�� �Ǳ� ����
				m_nowPos = 0 - 1;
			}
			else {
				m_isDone = TRUE;
				return FALSE;
			}
		}
		//�����̰� �����ؼ� ������ ���·� ������ ��ŭ �����ϰų�
		else if (m_endPoint[m_nowPos].m_delay != 0) {
			if (timeGetTime() - m_stay < m_endPoint[m_nowPos].m_delay)
				return FALSE;
		}
		m_nowPos++;
		m_stay = timeGetTime();
		//��ǥ�������� �̵������ִ� ��ȣ�� ������ ��
		//�� ��ȣ�� TRUE�� ��ȯ�����ν� ����
		return TRUE;
	}
	else return FALSE;
}
