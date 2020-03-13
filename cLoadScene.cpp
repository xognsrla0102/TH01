#include "DXUT.h"

#include "cPlayer.h"
#include "cBalls.h"
#include "cBulletAdmin.h"
#include "cEnemyAdmin.h"
#include "cItemAdmin.h"

#include "cTitleScene.h"
#include "cStartScene.h"
#include "cHowtoScene.h"
#include "cMusicScene.h"
#include "cOptionScene.h"
#include "cStage1Scene.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->InsertImage("loadBG", "resource/scene/loadscene/bg.png");
	m_BG = IMAGE->FindImage("loadBG");
}

cLoadScene::~cLoadScene()
{
	for (auto iter : m_sounds)
		SAFE_DELETE(iter);
	m_sounds.clear();

	for (auto iter : m_imgs)
		SAFE_DELETE(iter);
	m_imgs.clear();
}

void cLoadScene::Init()
{
	//파일 로딩

	//정보가 없을 경우 기존엔 파일이 없으니 디렉토리 만드는 것이 성공함
	if (FILEMANAGER->MakeDir("./gameInfo"))
		FILEMANAGER->OptionSave();
	//있으면 가져오기
	else {
		//윈도우 모드는 겜 실행후에 변수를 받으므로 직접 전환 시켜줘야함
		FILEMANAGER->OptionLoad();
		//디폴트 윈도우 모드가 창모드(isWindowed = true)이므로
		//정보를 받았을 때 전체화면일 경우에만 전환시켜주고
		//창모드일 때는 따로 처리시켜줄 필요가 없음
		if (isWindowed != true) {
			DXUTPause(true, true);
			DXUTToggleFullScreen();
			DXUTPause(false, false);
		}
	}

	//소리 로딩

	//배경음악
	for (size_t i = 1; i <= 4; i++) {
		char key[256];
		WCHAR path[256];

		//midi사운드 추가
		sprintf(key, "th_%02d_midi", i);
		wsprintf(path, L"./resource/music/midi/th06_%02d.wav", i);

		Load(key, path);

		//wav사운드 추가
		sprintf(key, "th_%02d_wav", i);
		wsprintf(path, L"./resource/music/wav/th06_%02d.wav", i);

		Load(key, path);
	}

	//효과음 추가
	Load("bombSND", L"./resource/sound/bomb.wav");
	Load("reimouAbombSND", L"./resource/sound/reimouA_bomb.wav");
	Load("reimouBbombSND", L"./resource/sound/reimouB_bomb.wav");
	Load("marisaAbombSND", L"./resource/sound/marisaA_bomb.wav");
	Load("marisaBbombSND", L"./resource/sound/marisaB_bomb.wav");

	Load("bossdeadSND", L"./resource/sound/bossdead.wav");
	Load("bossspellSND", L"./resource/sound/bossspell.wav");

	Load("cancelSND", L"./resource/sound/cancel.wav");
	Load("chargeshotSND", L"./resource/sound/chargeshot.wav");

	Load("deadSND", L"./resource/sound/dead.wav");

	Load("enemydeadSND", L"./resource/sound/enemydead.wav");
	Load("extendSND", L"./resource/sound/extend.wav");

	Load("getitemSND", L"./resource/sound/getitem.wav");
	Load("grazeSND", L"./resource/sound/graze.wav");

	Load("hitSND", L"./resource/sound/hit.wav");

	Load("kira0SND", L"./resource/sound/kira00.wav");
	Load("kira1SND", L"./resource/sound/kira01.wav");
	Load("kira2SND", L"./resource/sound/kira02.wav");

	Load("lazer0SND", L"./resource/sound/lazer0.wav");
	Load("lazer1SND", L"./resource/sound/lazer1.wav");

	Load("powerSND", L"./resource/sound/power.wav");
	Load("powerupSND", L"./resource/sound/powerup.wav");

	Load("selectSND", L"./resource/sound/select.wav");
	Load("shotSND", L"./resource/sound/shot.wav");

	Load("timeSND", L"./resource/sound/time.wav");

	Load("weakshotSND", L"./resource/sound/weakshot.wav");
	Load("normalshotSND", L"./resource/sound/normalshot.wav");

	Load("keymoveSND", L"./resource/sound/keymove.wav");

	//이펙트 로딩
	Load("enemy_dead_EFFECT", "./resource/effect/death.png");
	Load("createBullet_EFFECT", "./resource/effect/createBullet.png");
	Load("powerUp_EFFECT", "./resource/effect/powerUp.png");

	//이미지 로딩

	//인게임 이미지 로딩
	Load("item_fullPower", "./resource/item/fullPower.png");
	Load("item_bigPower", "./resource/item/bigPower.png");
	Load("item_smallPower", "./resource/item/smallPower.png");
	Load("item_bonus", "./resource/item/bonus.png");
	Load("item_extend", "./resource/item/extend.png");
	Load("item_boom", "./resource/item/boom.png");
	Load("item_jum", "./resource/item/jum.png");

	//4장의 이미지가 한쌍이 되서 로딩(애니메이션)
	Load("player_reimou_idle", "./resource/scene/ingameScene/player/reimou/idle%d.png", 4);
	Load("player_reimou_left", "./resource/scene/ingameScene/player/reimou/left%d.png", 7);
	Load("player_reimou_right", "./resource/scene/ingameScene/player/reimou/right%d.png", 7);

	Load("player_reimou_mainShot", "./resource/scene/ingameScene/player/reimou/mainShot.png");
	Load("player_reimou_subShot0", "./resource/scene/ingameScene/player/reimou/homingShot.png");
	Load("player_reimou_subShot1", "./resource/scene/ingameScene/player/reimou/needleShot.png");
	Load("player_reimou_ball", "./resource/scene/ingameScene/player/reimou/ball.png");

	//레이무 스펠 A 나중에 만들어야징
	Load("player_reimou_spellB0", "./resource/scene/ingameScene/player/reimou/spellB0.png");
	Load("player_reimou_spellB1", "./resource/scene/ingameScene/player/reimou/spellB1.png");

	Load("player_marisa_idle", "./resource/scene/ingameScene/player/marisa/idle%d.png", 4);
	Load("player_marisa_left", "./resource/scene/ingameScene/player/marisa/left%d.png", 8);
	Load("player_marisa_right", "./resource/scene/ingameScene/player/marisa/right%d.png", 8);
	
	Load("player_marisa_mainShot", "./resource/scene/ingameScene/player/marisa/mainShot.png");
	Load("player_marisa_subShot0", "./resource/scene/ingameScene/player/marisa/missileShot.png");
	Load("player_marisa_subShot1", "./resource/scene/ingameScene/player/marisa/razerShot.png");
	Load("player_marisa_ball", "./resource/scene/ingameScene/player/marisa/ball.png");
	Load("player_marisa_spellA", "./resource/scene/ingameScene/player/marisa/spellA.png");
	Load("player_marisa_spellB", "./resource/scene/ingameScene/player/marisa/spellB.png");

	Load("spell_reimou_face", "./resource/spell/reimouFace.png");
	Load("spell_reimouA_name", "./resource/spell/reimouA.png");
	Load("spell_reimouB_name", "./resource/spell/reimouB.png");

	Load("spell_marisa_face", "./resource/spell/marisaFace.png");
	Load("spell_marisaA_name", "./resource/spell/marisaA.png");
	Load("spell_marisaB_name", "./resource/spell/marisaB.png");

	Load("spell_black", "./resource/spell/spellBlack.png");

	Load("ingame_ui", "./resource/scene/ingameScene/ui/gameUI.png");
	Load("ingame_life", "./resource/scene/ingameScene/ui/lifeStar.png");
	Load("ingame_bomb", "./resource/scene/ingameScene/ui/bombStar.png");

	Load("ingame_bg", "./resource/scene/ingameScene/stage1/bg.png");
	Load("ingame_black", "./resource/scene/ingameScene/stage1/black.png");

	Load("ingame_name", "./resource/scene/ingameScene/ui/name.png");
	Load("ingame_music", "./resource/scene/ingameScene/ui/music.png");
	Load("ingame_title", "./resource/scene/ingameScene/ui/title.png");
	Load("ingame_circle", "./resource/scene/ingameScene/ui/circle.png");

	//적 이미지
	Load("enemy_one", "./resource/enemy/one/one.png");

	Load("enemy_fairy_red", "./resource/enemy/fairy/red/%d.png", 8);
	Load("enemy_fairy_orange", "./resource/enemy/fairy/orange/%d.png", 8);
	Load("enemy_fairy_blue", "./resource/enemy/fairy/blue/%d.png", 8);
	Load("enemy_fairy_green", "./resource/enemy/fairy/green/%d.png", 4);
	Load("enemy_fairy_purple", "./resource/enemy/fairy/purple/%d.png", 4);

	Load("enemy_book_red", "./resource/enemy/book/red.png");
	Load("enemy_book_green", "./resource/enemy/book/green.png");
	Load("enemy_book_pink", "./resource/enemy/book/pink.png");

	Load("enemy_magiczone", "./resource/enemy/book/magic.png");

	//보스 이미지
	Load("enemy_devil", "./resource/enemy/boss/devil.png");

	Load("enemy_patchouli_idle", "./resource/enemy/boss/patchouli/idle.png");
	Load("enemy_patchouli_spell", "./resource/enemy/boss/patchouli/spell.png");
	Load("enemy_patchouli_move", "./resource/enemy/boss/patchouli/%d.png", 3);

	//적 총알 이미지
	Load("bullet_blueOne", "./resource/enemy/bullet/blueOne.png");

	Load("bullet_blueMeal", "./resource/enemy/bullet/blueMeal.png");

	for (size_t i = 0; i < 5; i++) {
		char key[256], path[256];
		sprintf(key, "ingame_%d", i);
		sprintf(path, "./resource/scene/ingameScene/ui/%d.png", i);
		Load(key, path);
	}

	//숫자 이미지 로딩
	for (size_t i = 0; i < 10; i++) {
		char key[256], path[256];
		sprintf(key, "num_%d", i);
		sprintf(path, "./resource/number/%d.png", i);

		Load(key, path);
	}
	Load("num_dot", "./resource/number/dot.png");

	//타이틀 씬 이미지
	Load("whiteBG", "./resource/scene/titleScene/whitebg.png");
	Load("titleBG", "./resource/scene/titleScene/bg.png");

	//동방홍마향 The embodiment of devil. 글자
	for (size_t i = 0; i < 6; i++) {
		char key[256], path[256];
		sprintf(key, "title_text_%d", i);
		sprintf(path, "./resource/scene/titleScene/text/%d.png", i);
		Load(key, path);
	}

	//스타트 씬 이미지
	Load("startBG", "./resource/scene/startScene/bg.png");
	Load("startSELECT_MODE", "./resource/scene/startScene/selectMode.png");
	Load("startSELECT_CHARACTER", "./resource/scene/startScene/selectCharacter.png");
	Load("startSELECT_WEAPON", "./resource/scene/startScene/selectWeapon.png");

	//하우투 씬 이미지
	for (size_t i = 0; i < 12; i++) {
		char key[256], path[256];
		sprintf(key, "howto_%d", i);
		sprintf(path, "./resource/scene/howtoScene/%d.png", i);
		Load(key, path);
	}

	//음악 룸 씬 이미지
	Load("musicBG", "./resource/scene/musicScene/bg.png");
	for (size_t i = 1; i <= 4; i++) {
		char key[256], path[256];
		sprintf(key, "music_th%d", i);
		sprintf(path, "./resource/scene/musicScene/%d.png", i);
		Load(key, path);
	}

	//옵션 씬 이미지
	Load("optionBG", "./resource/scene/optionScene/bg.png");

	//타이틀 씬 버튼
	Load("startBT", "./resource/button/start.png");
	Load("howtoBT", "./resource/button/howto.png");
	Load("replayBT", "./resource/button/replay.png");
	Load("scoreBT", "./resource/button/score.png");
	Load("musicBT", "./resource/button/musicroom.png");
	Load("optionBT", "./resource/button/option.png");
	Load("quitBT", "./resource/button/quit.png");

	//스타트 씬 버튼
	Load("lunaticBT", "./resource/scene/startScene/lunatic.png");
	Load("extraBT", "./resource/scene/startScene/extra.png");
	Load("reimouBT", "./resource/scene/startScene/reimou.png");
	Load("reimou1BT", "./resource/scene/startScene/reimou1.png");
	Load("reimou2BT", "./resource/scene/startScene/reimou2.png");
	Load("marisaBT", "./resource/scene/startScene/marisa.png");
	Load("marisa1BT", "./resource/scene/startScene/marisa1.png");
	Load("marisa2BT", "./resource/scene/startScene/marisa2.png");

	//음악 룸 씬 버튼
	Load("th01BT", "./resource/button/th01.png");
	Load("th02BT", "./resource/button/th02.png");
	Load("th03BT", "./resource/button/th03.png");
	Load("th04BT", "./resource/button/th04.png");

	//옵션 씬 버튼
	Load("0BT", "./resource/button/0.png");
	Load("1BT", "./resource/button/1.png");
	Load("2BT", "./resource/button/2.png");
	Load("3BT", "./resource/button/3.png");
	Load("4BT", "./resource/button/4.png");
	Load("5BT", "./resource/button/5.png");

	Load("lifeBT", "./resource/button/player.png");
	Load("bombBT", "./resource/button/bomb.png");
	Load("bgmBT", "./resource/button/bgm.png");
	Load("wavBT", "./resource/button/wav.png");
	Load("midiBT", "./resource/button/midi.png");
	Load("soundBT", "./resource/button/sound.png");
	Load("modeBT", "./resource/button/mode.png");
	Load("windowBT", "./resource/button/window.png");
	Load("fullBT", "./resource/button/full.png");
	Load("restoreBT", "./resource/button/restore.png");
	Load("onBT", "./resource/button/on.png");
	Load("offBT", "./resource/button/off.png");
}

void cLoadScene::Update()
{
	//소리
	if (m_nowLoad[0] < m_sounds.size()) {
		int& idx = m_nowLoad[0];
		SOUND->AddSound(m_sounds[idx]->m_idx1, m_sounds[idx]->m_idx2);
		idx++;
	}

	//이미지
	if (m_nowLoad[1] < m_imgs.size()) {
		int& idx = m_nowLoad[1];
		IMAGE->InsertImage(m_imgs[idx]->m_idx1, m_imgs[idx]->m_idx2, m_imgs[idx]->m_cnt);
		idx++;
	}

	if (m_nowLoad[0] == m_sounds.size() &&
		m_nowLoad[1] == m_imgs.size()
		) {
		//OBJ생성
		OBJECT->AddOBJ(new cPlayer, PLAYER);
		((cPlayer*)OBJFIND(PLAYER))->Init();
		OBJECT->AddOBJ(new cBalls, BALLS);
		OBJECT->AddOBJ(new cBulletAdmin, BULLETS);
		OBJECT->AddOBJ(new cEnemyAdmin, ENEMYS);
		OBJECT->AddOBJ(new cItemAdmin, ITEMS);

		//씬 추가 (같이 로딩할 수 없는 문제 때문)
		SCENE->AddScene("titleScene", new cTitleScene);
		SCENE->AddScene("startScene", new cStartScene);
		SCENE->AddScene("howtoScene", new cHowtoScene);
		SCENE->AddScene("musicScene", new cMusicScene);
		SCENE->AddScene("optionScene", new cOptionScene);
		SCENE->AddScene("stage1Scene", new cStage1Scene);

		SCENE->ChangeScene("titleScene");
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_BG, VEC2(0, 0), 1.f);
}

void cLoadScene::Release()
{
}