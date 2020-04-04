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
	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));

	if (m_followPlayer == TRUE && player->m_isHit != TRUE) {
		VEC2 dir;
		D3DXVec2Normalize(&dir, &(player->GetPos() - m_pos));
		m_pos += dir * 800.f * D_TIME;
	}
	else if (player->m_isBomb == TRUE ||
		(player->m_power == 128 && player->GetPos().y < 50 + INGAMEY / 3.f)
		) m_followPlayer = TRUE;
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
	if (m_pos.x - m_img->m_info.Width / 2 > 50 + INGAMEX + 500 ||
		m_pos.x + m_img->m_info.Width / 2 < 50 - 500 ||
		m_pos.y - m_img->m_info.Height / 2 > 50 + INGAMEY + 500 ||
		m_pos.y + m_img->m_info.Height / 2 < 50 - 500
		) m_isLive = FALSE;
}

void cItem::Collision()
{
	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));

	if (player->m_isHit == TRUE ||
		(m_isEndPos == FALSE && m_followPlayer == FALSE)
		) return;

	VEC2 playerPos = player->GetPos();

	RECT itemRect = {
		m_pos.x - m_img->m_info.Width / 2,
		m_pos.y - m_img->m_info.Height / 2,
		m_pos.x + m_img->m_info.Width / 2,
		m_pos.y + m_img->m_info.Height / 2
	};

	RECT playerRect = {
		playerPos.x - player->GetImg()->m_info.Width / 2,
		playerPos.y - player->GetImg()->m_info.Height / 2,
		playerPos.x + player->GetImg()->m_info.Width / 2,
		playerPos.y + player->GetImg()->m_info.Height / 2
	};

	if (AABB(itemRect, playerRect)) {
		SOUND->Copy("getitemSND");
		if(m_key != "item_tan")
			SOUND->Copy("getitemSND");

		if(m_key == "item_smallPower"){
			if (player->m_power == 128);
			else if (player->m_power < 128) player->m_power++;
			else player->m_power = 128;

			if (player->m_power == 128) {
				player->m_score += 51200;
				FONT->AddFont("51200", m_pos, 1000, TRUE, D3DCOLOR_ARGB(255, 255, 255, 0));
			}
			else {
				player->m_score += 10;
				FONT->AddFont("10", m_pos, 1000, TRUE);
			}
		}
		else if (m_key == "item_bigPower") {
			if (player->m_power == 128);
			else if (player->m_power < 128) player->m_power += 8;
			else player->m_power = 128;

			if (player->m_power == 128) {
				player->m_score += 51200;
				FONT->AddFont("51200", m_pos, 1000, TRUE, D3DCOLOR_ARGB(255, 255, 255, 0));
			}
			else {
				player->m_score += 10;
				FONT->AddFont("10", m_pos, 1000, TRUE);
			}
		}
		else if (m_key == "item_fullPower") {
			if (player->m_power == 128) {
				player->m_score += 1000;
				FONT->AddFont("1000", m_pos, 1000, TRUE);
			}
			else player->m_power = 128;
		}
		else if (m_key == "item_tan")
			player->m_score += player->m_graze / 3.f * 10 + 500;
		else if (m_key == "item_extend") {
			if (player->m_life < 8) player->m_life++;
			else player->m_bomb++;
		}
		else if (m_key == "item_boom") {
			if(player->m_bomb < 8) player->m_bomb++;
		}
		else if (m_key == "item_jum") {
			player->m_jum++;
			//50 + INGAMEY 에서 50 + INGAMEY / 3사이의 거리를 100으로 잡았을 때
			//현재 플레이어의 y는 50 + INGAMEY에서 얼마만큼 차이가 나고 그 차이는 50 + INGAMEY와 50 + INGAMEY / 3 사이의 거리에
			//비해 얼마나 차지하는지

			if (player->GetPos().y > 50 + INGAMEY / 3.f) {
				FLOAT percent = (50 + INGAMEY) - (50 + INGAMEY / 3.f);
				FLOAT playerDist = (50 + INGAMEY) - player->GetPos().y;
				player->m_score += 100000 * playerDist / percent;

				CHAR temp[256];
				sprintf(temp, "%d", (INT)(100000 * playerDist / percent));
				FONT->AddFont(temp, m_pos, 1000, TRUE);
			}
			else {
				player->m_score += 200000;
				FONT->AddFont("200000", m_pos, 1000, TRUE, D3DCOLOR_ARGB(255, 255, 255, 0));
			}
		}
		m_isLive = FALSE;
	}
}

