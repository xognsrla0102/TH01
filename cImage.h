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

	float m_a = 255;
	float m_r = 255;
	float m_g = 255;
	float m_b = 255;

	D3DXCOLOR m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b);

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b); }
};

