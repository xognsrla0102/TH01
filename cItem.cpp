#include "DXUT.h"
#include "cPlayer.h"
#include "cItem.h"

cItem::cItem(string key, VEC2 pos, VEC2 endPos)
{
	m_key = key;
	m_img = IMAGE->FindImage(key);
	m_pos = pos;
	m_endPos = endPos;
}

void cItem::Update()
{
	if (m_followPlayer == TRUE) {
		VEC2 dir;
		D3DXVec2Normalize(&dir, &(((cPlayer*)OBJFIND(PLAYER))->GetPos() - m_pos));
		m_pos += dir * 800.f * D_TIME;
	}
	else if (((cPlayer*)OBJFIND(PLAYER))->m_isBomb == TRUE)
		m_followPlayer = TRUE;
	else {
		if (m_isEndPos == FALSE) {
			if (DistPoint(m_pos, m_endPos) < 5.f) m_isEndPos = TRUE;
			else Lerp(m_pos, m_endPos, 0.03);
		}
		else {
			//0.5초만에 원래 속도 도달
			if (m_accel < 1.f) m_accel += D_TIME * 2;
			else m_accel = 1.f;
			m_pos.y += 200.f * D_TIME * m_accel;
		}
	}
}

void cItem::Render()
{
	IMAGE->Render(m_img, m_pos, 1.f, 0.f, TRUE);
}

void cItem::OutMapChk()
{
	if (m_pos.x - m_img->m_info.Width / 2 > 50 + INGAMEX + 300 ||
		m_pos.x + m_img->m_info.Width / 2 < 50 - 300 ||
		m_pos.y - m_img->m_info.Height / 2 > 50 + INGAMEY + 300 ||
		m_pos.y + m_img->m_info.Height / 2 < 50 - 300
		) m_isLive = FALSE;
}

void cItem::Collision()
{
	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));

	if (player->m_isHit == TRUE) return;
	VEC2 playerPos = player->GetPos();

	RECT itemRect = {
		m_pos.x - m_img->m_info.Width / 2,
		m_pos.y - m_img->m_info.Height / 2,
		m_pos.x + m_img->m_info.Width / 2,
		m_pos.y + m_img->m_info.Height / 2
	};

	RECT playerRect = {
		playerPos.x - 5,
		playerPos.y - 5,
		playerPos.x + 5,
		playerPos.y + 5
	};

	if (AABB(itemRect, playerRect)) {
		SOUND->Copy("getitemSND");
		SOUND->Copy("getitemSND");

		if(m_key == "item_smallPower"){
			if (player->m_power == 128);
			else if (player->m_power < 128) player->m_power++;
			else player->m_power = 128;
			player->m_score += 10;
			if (player->m_power == 128) player->m_score += 51200;
		}
		else if (m_key == "item_bigPower") {
			if (player->m_power == 128);
			else if (player->m_power < 128) player->m_power += 8;
			else player->m_power = 128;

			player->m_score += 10 * 8;
			if (player->m_power == 128) player->m_score += 51200;
		}
		else if (m_key == "item_bonus") {

		}
		else if (m_key == "item_extend") {
			player->m_life++;
		}
		else if (m_key == "item_boom") {
			player->m_bomb++;
		}
		else if (m_key == "item_jum") {
			player->m_jum++;
		}
		m_isLive = FALSE;
	}
}

