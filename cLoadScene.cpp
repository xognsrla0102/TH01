#include "DXUT.h"
#include "cTexture.h"
#include "cPlayer.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->InsertImage("loadBG", "resource/scene/loadscene/bg.png");
	IMAGE->InsertImage("player", "resource/scene/loadscene/obj1.png");
	IMAGE->InsertImage("obj2", "resource/scene/loadscene/obj2.png");
	IMAGE->InsertImage("isColl", "resource/scene/loadscene/obj3.png");

	m_BG = IMAGE->FindImage("loadBG");
	m_player = new cPlayer;
	obj2 = IMAGE->FindImage("obj2");
	rtCol2 = {
		1000 - obj2->m_info.Width / 2.0,
		WINSIZEY / 2 - obj2->m_info.Height / 2.0,
		(double)obj2->m_info.Height,
		(double)obj2->m_info.Width,
		0.0
	};
}

cLoadScene::~cLoadScene()
{
	for (auto iter : m_datas)
		SAFE_DELETE(iter.second);
	m_datas.clear();
}

void cLoadScene::Init()
{
}

void cLoadScene::Update()
{
	d = getDistance(m_player->rtCol, rtCol2);
	m_player->Update();

	DEBUG_LOG("x : %.f\ny : %.f\nheight : %.f\nwidth : %.f\nrot : %.f\n\n", m_player->rtCol.left, m_player->rtCol.top, m_player->rtCol.height, m_player->rtCol.width, m_player->rtCol.rot);

	if (OBB(m_player->rtCol, rtCol2)) {
		m_player->isColl = true;
	}
	else {
		m_player->isColl = false;
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0));
	IMAGE->Render(obj2, VEC2(1000, WINSIZEY / 2), 1.f, 0.f, D3DCOLOR_ARGB(255,255,255,255), true);
	m_player->Render();
}

void cLoadScene::Release()
{
	SAFE_DELETE(m_player);
}

VEC2 cLoadScene::getDistance(NEMO a, NEMO b)
{
	VEC2 ret;
	ret.x = (a.left + a.width / 2) - (b.left + b.width / 2);
	ret.y = (a.top + a.height / 2) - (b.top + b.height / 2);
	return ret;
}

VEC2 cLoadScene::getHeight(NEMO a)
{
	VEC2 ret;
	ret.x = cos(D3DXToRadian(a.rot - 90)) * a.height / 2.f;
	ret.y = sin(D3DXToRadian(a.rot - 90)) * a.height / 2.f;
	return ret;
}

VEC2 cLoadScene::getWidth(NEMO a)
{
	VEC2 ret;
	ret.x = cos(D3DXToRadian(a.rot)) * a.width / 2.f;
	ret.y = sin(D3DXToRadian(a.rot)) * a.width / 2.f;
	return ret;
}

bool cLoadScene::OBB(NEMO a, NEMO b)
{
	//obb 공식
	//d.u < ah.u + aw.u + bh.u + bw.u
	VEC2 unit;
	VEC2 axis[4] = {
		getHeight(a),
		getHeight(b),
		getWidth(a),
		getWidth(b)
	};

	//투영할 축 갯수
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		//투영 축 단위벡터 변환
		D3DXVec2Normalize(&unit, &axis[i]);
		for (int j = 0; j < 4; j++)
			sum += abs(D3DXVec2Dot(&axis[j], &unit));
		//안 충돌
		if (abs(D3DXVec2Dot(&d, &unit)) > sum)
			return false;
	}
	return true;
	//충돌
}
