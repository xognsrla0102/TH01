#pragma once
class cImage
{
public:
	//cTextureŬ�������� ���������� ��ġ�� �� ������ �Ϳ� ����
	//�ӽù��� Ŭ���� ������ �ٲٱ⿣ �ð��� �ʹ� ���� �ɸ��Ƿ�
	//���ݺ��Ͷ� cImageŬ������ ���
	cTexture* m_img;

	VEC2 m_pos = VEC2(0, 0);
	vector<VEC2> m_endPos;

	FLOAT m_a = 255;
	FLOAT m_r = 255;
	FLOAT m_g = 255;
	FLOAT m_b = 255;

	FLOAT m_rot = 0.f;

	D3DXCOLOR m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b);

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b); }
};

