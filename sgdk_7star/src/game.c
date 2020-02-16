#include <genesis.h>

#include "resource.h"
#include "main.h"

struct playerScene
{
	s16 x;
	s16 y;
};

struct sozai
{
	s16 item_id;
	s16 x;
	s16 y;
	char showed;	// 表示
	s16 water;
	s16 stone;
	s16 metal;
	s16 wood;
	s16 HP;
	s16 width;
};

struct irainin
{
	s16 amount;
	s16 item_id;
	s16 reward;
	s16 x;
	s16 y;
};

datas game(datas Data) {

	SYS_disableInts();

	// Window領域の定義
	VDP_setWindowHPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setWindowVPos(FALSE, 5); // @suppress("Symbol is not resolved")
	VDP_setTextPlan(PLAN_WINDOW);
	VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

	// プレイヤーの初期化
	struct playerScene PlayerData;
	PlayerData.x=0;
	PlayerData.y=122;

	// カメラの初期化
	struct camera Camera;
	Camera.x=0;
	Camera.y=122;

	Data.gm = GAME;

	// BGM再生
	SND_startPlay_4PCM_ENV(
		BGM_Sub_8,
		sizeof(BGM_Sub_8),
		SOUND_PCM_CH1,	// @suppress("Symbol is not resolved")
		TRUE 			// @suppress("Symbol is not resolved")
	);

	u16 palette[64];
	memcpy(&palette[0], NPC.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	s16 SOZAI_SUU = 3;

	// 行きか帰りか
	if ( Data.explore_mode == 1 ) {
		// 帰り
		memcpy(&palette[32], sorayuugata_image.palette->data, 16 * 2);
		memcpy(&palette[48], zimenyuugata_image.palette->data, 16 * 2);

		// 帰りは素材数を少なくする
		SOZAI_SUU = 1;
	}

	s16 goal_in = 5000;

	// 素材の初期化
	struct sozai Sozais[SOZAI_SUU];
	for(s16 i=0;i<SOZAI_SUU;i++)
	{
		Sozais[i].showed=0;
		Sozais[i].x=0;
	}

	// プレイヤー
	sprites[0] = SPR_addSprite(&Player, 0, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
	SPR_setPosition(sprites[0], 0 ,0);

	// 背景B
	s16 vdp_b_count = 0;
	s16 vdp_b_x = 0;
	s16 ind_b[5];
	u16 ind = TILE_USERINDEX; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

	// 背景A
	s16 vdp_a_count = 0;
	s16 vdp_a_x = 0;
	s16 ind_a[5];
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")

	// 追加背景B
	VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++;	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

	// 追加背景A
	VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")

    char str19[] = "水";
    draw_sjis_text(PLAN_WINDOW, str19, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind),  3, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str19) * 2;

    char str20[] = "木";
    draw_sjis_text(PLAN_WINDOW, str20, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 10, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str20) * 2;

    char str21[] = "鉄";
    draw_sjis_text(PLAN_WINDOW, str21, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 17, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str21) * 2;

    char str22[] = "石";
    draw_sjis_text(PLAN_WINDOW, str22, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 24, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str22) * 2;

    char str23[] = "お金";
    draw_sjis_text(PLAN_WINDOW, str23, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 31, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str23) * 2;

	SYS_enableInts();

	fadeIn( palette );

	s16 walk_count = 0;
	s16 fightMode = 0;
	s16 fightModeTimer = 0;

	s16 bg_b_count = 0;
	s16 bg_a_count = 0;

	//依頼人関係
//	u16 NPCs[5]=
//	{
//			//アイテムID,個数,報酬,    X,   Y
//			{        1,  1,100,  400, 124},
//			{        2,  1,100,  500, 124},
//			{        3,  1,100,  600, 124},
//			{        4,  1,100,  700, 124},
//			{        5,  1,100,  800, 124},
//			{        6,  1,100,  900, 124},
//			{        7,  1,100, 1000, 124},
//			{        8,  1,100, 1100, 124},
//			{        9,  1,100, 1200, 124},
//			{       10,  1,100, 1300, 124},
//			{       11,  1,100, 1400, 124},
//	};

	s16 Irainin_showed = 0;
	struct irainin Irainin;
	int irai_next_x = 400;	// 次の依頼人が表示される位置

	s16 completedSwitch = 0;

	s16 coin_time=0;

	int action = PLAYER_PUNCH;
	int next_x = 0;	// 次の素材
	int damage = 1;

	while ( TRUE ) { // @suppress("Symbol is not resolved")
		bg_b_count += CAMERA_MOVE;

		// 背景B
		if ( bg_b_count >= 64 * 8 ) {
			VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); // @suppress("Symbol is not resolved")
			vdp_b_count++;
			vdp_b_count %= 5;
			vdp_b_x += 8;
			vdp_b_x %= 64;
			bg_b_count -= 64 * 8;
		}

		// 背景A
		bg_a_count += CAMERA_MOVE;
		if ( bg_a_count >= 64 ) {
			VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image ); // @suppress("Symbol is not resolved")
			vdp_a_count++;
			vdp_a_count %= 5;
			vdp_a_x += 8;
			vdp_a_x %= 64;
			bg_a_count -= 64;
		}

		// 素材数＆お金
		text(Data.water, 5,2);
		text(Data.wood ,12,2);
		text(Data.metal,19,2);
		text(Data.stone,26,2);
		text(Data.money,35,2);

		u16 pad1 = JOY_readJoypad(JOY_1);	// @suppress("Symbol is not resolved")

		if( ( pad1 & BUTTON_A ) && fightMode == 0 ) {	// @suppress("Symbol is not resolved")
			// 効果音（攻撃）
			SND_startPlay_4PCM_ENV(
				SE_Punch_8,
				sizeof(SE_Punch_8),
				SOUND_PCM_CH2,	// @suppress("Symbol is not resolved")
				FALSE 			// @suppress("Symbol is not resolved")
			);

			fightMode=1;
			if ( Data.hammer > 0 ) {
				action = PLAYER_HAMMER;
				fightModeTimer=30;
				damage = 6;
			}
			else if ( Data.bucket > 0 ) {
				action = PLAYER_BUCKET;
				fightModeTimer=25;
				damage = 6;
			}
			else if ( Data.bomb > 0 ) {
				action = PLAYER_BOMB;
				fightModeTimer=30;
				damage = 6;
			}
			else if ( Data.saw > 0 ) {
				action = PLAYER_SAW;
				fightModeTimer=30;
				damage = 6;
			}
			else {
				action = PLAYER_PUNCH;
				fightModeTimer=30;
				damage = 1;
			}
		}

		// 移動
		s16 walkMode = 0;
		if ( pad1 & BUTTON_LEFT ){ // @suppress("Symbol is not resolved")
			PlayerData.x -= 2;
			walkMode = 1;
		}
		if ( pad1 & BUTTON_RIGHT ){ // @suppress("Symbol is not resolved")
			PlayerData.x += 2;
			walkMode = 1;
		}
		if ( pad1 & BUTTON_UP ){	// @suppress("Symbol is not resolved")
			PlayerData.y -= 1;
			walkMode = 1;
		}
		if ( pad1 & BUTTON_DOWN ){ // @suppress("Symbol is not resolved")
			PlayerData.y += 1;
			walkMode = 1;
		}

		//はじっこ処理
		if ( PlayerData.y > BOTTOM_HEIGHT ) {
			PlayerData.y = BOTTOM_HEIGHT;
		}
		if ( PlayerData.y < TOP_HEIGHT ) {
			PlayerData.y = TOP_HEIGHT;
		}
		if ( PlayerData.x < 0 ) {
			PlayerData.x = 0;
			walkMode = 1;
		}
		if ( PlayerData.x < Camera.x ) {
			PlayerData.x = Camera.x;
			walkMode = 1;
		}
		if ( PlayerData.x > Camera.x + WIDTH - PLAYER_WIDTH ) {
			PlayerData.x = Camera.x + WIDTH - PLAYER_WIDTH;
		}

		if ( walkMode == 1 && fightMode != 1 ) {
			// 歩いている
			SPR_setAnim(sprites[0], PLAYER_WALK);

			// 30フレームに１回、足音を鳴らす
			if ( walk_count == 0 ) {
				// 効果音を鳴らしてみる
				SND_startPlay_4PCM_ENV(
						SE_Footstep_8,
						sizeof(SE_Footstep_8),
						SOUND_PCM_CH3,	// @suppress("Symbol is not resolved")
						FALSE			// @suppress("Symbol is not resolved")
				);
			}
			walk_count++;
			if ( walk_count > 30 ) {
				walk_count = 0;
			}

		}
		else if ( fightMode != 1 && walkMode != 1 ) {
			// 止まっている
			SPR_setAnim(sprites[0], PLAYER_WAIT);
			walk_count = 0;
		}
		else if ( fightMode == 1 ) {
			// 攻撃
			fightModeTimer--;
			SPR_setAnim(sprites[0],action);
			if ( fightModeTimer <= 0 ) {
				fightMode = 0;
			}
		}

		// カメラの移動
		Camera.x += CAMERA_MOVE;
		VDP_setHorizontalScroll(PLAN_A, -Camera.x);
		VDP_setHorizontalScroll(PLAN_B,-Camera.x >> 3);

		// カメラの移動に合わせて、プレイヤーを移動する
		SPR_setPosition(
			sprites[0],
			PlayerData.x - Camera.x,
			PlayerData.y
		);

		// 素材
		for ( s16 i = 0; i < SOZAI_SUU; i++ ) {

			// 生成
			if ( Sozais[i].showed == 0 && next_x < WIDTH + Camera.x ) {

				Sozais[i].item_id = (s16)( random() % 16 ) + 1;
				Sozais[i].x = WIDTH + Camera.x + (s16)( random() % 128 );
				Sozais[i].y = 150 + (s16)( random() % 24 );

				switch ( Sozais[i].item_id ) {
				case ITEM_ID_KI01:
					// 木の苗
					sprites[i+1] = SPR_addSprite(&ki01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 16;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 1;
					Sozais[i].HP = 15;
					break;
				case ITEM_ID_KI02:
					// 木（小）
					sprites[i+1] = SPR_addSprite(&ki02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 24;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 5;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_KI03:
					// 木（中）
					sprites[i+1] = SPR_addSprite(&ki03,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 48;
					Sozais[i].water = 1;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 20;
					Sozais[i].HP = 150;
					break;
				case ITEM_ID_KI04:
					// 木（大）
					sprites[i+1] = SPR_addSprite(&ki04,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 64;
					Sozais[i].water = 5;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 50;
					Sozais[i].HP = 300;
					break;
				case ITEM_ID_KINNZANN01:
					// 金山
					sprites[i+1] = SPR_addSprite(&kinnzann01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 30;
					Sozais[i].metal = 15;
					Sozais[i].wood = 30;
					Sozais[i].HP = 100;
					break;
				case ITEM_ID_koori01:
					// 氷（小）
					sprites[i+1] = SPR_addSprite(&koori01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 1;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 10;
					break;
				case ITEM_ID_koori02:
					// 氷（中）
					sprites[i+1] = SPR_addSprite(&koori02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 5;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 30;
					break;
				case ITEM_ID_koori03:
					// 氷（大）
					sprites[i+1] = SPR_addSprite(&koori02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 20;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_KOUMYAKU01:
					// 鉱脈（小）
					sprites[i+1] = SPR_addSprite(&koumyaku01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 24;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 5;
					Sozais[i].wood = 0;
					Sozais[i].HP = 150;
					break;
				case ITEM_ID_KOUMYAKU02:
					// 鉱脈（中）
					sprites[i+1] = SPR_addSprite(&koumyaku02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 10;
					Sozais[i].wood = 0;
					Sozais[i].HP = 500;
					break;
				case ITEM_ID_MIZU01:
					// 池（小）
					sprites[i+1] = SPR_addSprite(&mizu01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 5;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 30;
					break;
				case ITEM_ID_MIZU02:
					// 池（大）
					sprites[i+1] = SPR_addSprite(&mizu02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 64;
					Sozais[i].water = 20;
					Sozais[i].stone = 1;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_ROCK01:
					// 岩（小）
					sprites[i+1] = SPR_addSprite(&rock01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 5;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_ROCK02:
					// 岩（中）
					sprites[i+1] = SPR_addSprite(&rock02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 20;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 150;
					break;
				case ITEM_ID_ROCK03:
					// 岩（大）
					sprites[i+1] = SPR_addSprite(&rock03,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 50;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 300;
					break;
				case ITEM_ID_TETUKUZU01:
					// 鉄くず
					sprites[i+1] = SPR_addSprite(&tetukuzu01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 16;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 1;
					Sozais[i].wood = 0;
					Sozais[i].HP = 30;
					break;
				}
				Sozais[i].showed = 1;

				next_x = Sozais[i].x + Sozais[i].width + 32;	// 32はバッファ
			}

			if ( Sozais[i].showed == 1 ) {
				// 素材を移動する
				SPR_setPosition(
					sprites[i+1],
					(Sozais[i].x-Camera.x) + Sozais[i].HP % 5,	// ダメージを受けた時の揺れ
					Sozais[i].y
				);

				if ( fightMode == 1 ) { // @suppress("Symbol is not resolved")
					// 攻撃中

					// 距離を求める TODO 重すぎる！！
//					int dx = abs( PlayerData.x - Sozais[i].x );
//					int dy = abs( PlayerData.y - Sozais[i].y );
//					int distance = sqrt( dx * dx + dy * dy );
//					text( distance, 30, 4 );

					// 当たり判定（攻撃が少し前なので、X軸をずらしています）
					if ( Sozais[i].x <= PlayerData.x+36 && PlayerData.x+36 <= Sozais[i].x + Sozais[i].width
					  && Sozais[i].y <= PlayerData.y+24 && PlayerData.y+24 <= Sozais[i].y + Sozais[i].width
					) {
						// 当たった
						Sozais[i].HP -= damage;

						if ( Sozais[i].HP <= 0 ) {
							// 壊れた

							// 効果音（破壊）
							SND_startPlay_4PCM_ENV(
									SE_Explosion_8,
									sizeof(SE_Explosion_8),
									SOUND_PCM_CH4, 	// @suppress("Symbol is not resolved")
									FALSE 			// @suppress("Symbol is not resolved")
							);

							Data.water += Sozais[i].water;
							Data.stone += Sozais[i].stone;
							Data.metal += Sozais[i].metal;
							Data.wood  += Sozais[i].wood;

							// スプライトの消滅
							SPR_releaseSprite(sprites[i+1]);
							Sozais[i].showed = 0;
						}
					}
				}

				// 画面外
				if ( Sozais[i].x + Sozais[i].width - Camera.x < 0 && Sozais[i].showed == 1 ) {
					// スプライトの消滅
					SPR_releaseSprite(sprites[i+1]);
					Sozais[i].showed = 0;
				}
			}
		}

		//依頼人
		if ( irai_next_x <= WIDTH + Camera.x
		  && Irainin_showed == 0
		) {
			// 生成
			Irainin_showed = 1;

			Irainin.item_id = (s16)( random() % 11 ) + 1;
			Irainin.x = WIDTH + Camera.x + (s16)( random() % 128 );
			Irainin.y = 124;

			Irainin.amount = 1;

			irai_next_x = Irainin.x + WIDTH;

			sprites[17] = SPR_addSprite(
					&NPC,
					Irainin.x - Camera.x,
					Irainin.y,
					TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
			);

			//依頼人のフキダシ
			switch ( Irainin.item_id ) {
			case ITEM_ID_CHAIR:
				// 椅子
				sprites[19] = SPR_addSprite( &fukidashi01, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 100;
				break;
			case ITEM_ID_DESK:
				// 机
				sprites[19] = SPR_addSprite( &fukidashi02, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 300;
				break;
			case ITEM_ID_CHEST:
				// タンス
				sprites[19] = SPR_addSprite( &fukidashi03, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 400;
				break;
			case ITEM_ID_BRICK:
				// れんが
				sprites[19] = SPR_addSprite( &fukidashi04, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 100;
				break;
			case ITEM_ID_RING:
				// 指輪
				sprites[19] = SPR_addSprite( &fukidashi05, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 100;
				break;
			case ITEM_ID_SCULPTURE:
				// 彫刻
				sprites[19] = SPR_addSprite( &fukidashi06, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 300;
				break;
			case ITEM_ID_W_HOUSE:
				// 木の家
				sprites[19] = SPR_addSprite( &fukidashi07, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 1000;
				break;
			case ITEM_ID_S_HOUSE:
				// 石の家
				sprites[19] = SPR_addSprite( &fukidashi08, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 1000;
				break;
			case ITEM_ID_W_MANSION:
				// 木の豪邸
				sprites[19] = SPR_addSprite( &fukidashi09, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 1500;
				break;
			case ITEM_ID_S_MANSION:
				// 石の豪邸
				sprites[19] = SPR_addSprite( &fukidashi10, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 1500;
				break;
			case ITEM_ID_TANK:
				// 水槽
				sprites[19] = SPR_addSprite( &fukidashi11, Irainin.x + 32 - Camera.x, Irainin.y - 32, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );	// @suppress("Symbol is not resolved")
				Irainin.reward = 500;
				break;
			}
		}

		if ( Irainin_showed == 1 ) {
			SPR_setPosition(
				sprites[17],
				Irainin.x - Camera.x,	// カメラ移動を意識するため、毎フレーム処理
				Irainin.y
			);

			SPR_setPosition(
				sprites[19],
				Irainin.x + 32 - Camera.x,	// カメラ移動を意識するため、毎フレーム処理
				Irainin.y - 32
			);
		}

		//プレイヤーの依頼人関係処理
		if ( Irainin.x - PLAYER_WIDTH  <= PlayerData.x && PlayerData.x <= Irainin.x + PLAYER_WIDTH
		  && Irainin.y - PLAYER_HEIGHT <= PlayerData.y && PlayerData.y <= Irainin.y + PLAYER_HEIGHT
		  && completedSwitch == 0
		) {
			// 依頼人と接触
			completedSwitch = 1;
			s16 ans = 0;
			switch ( Irainin.item_id )
			{
				case ITEM_ID_CHAIR:
					// 椅子
					if ( Data.chair >= Irainin.amount ) {
						ans = ITEM_ID_CHAIR;
						Data.chair -= Irainin.amount;
					}
					break;
				case ITEM_ID_DESK:
					// 机
					if ( Data.desk >= Irainin.amount ) {
						ans = ITEM_ID_DESK;
						Data.desk -= Irainin.amount;
					}
					break;
				case ITEM_ID_CHEST:
					// タンス
					if ( Data.chest >= Irainin.amount ) {
						ans = ITEM_ID_CHEST;
						Data.chest -= Irainin.amount;
					}
					break;
				case ITEM_ID_BRICK:
					// レンガ
					if ( Data.brick >= Irainin.amount ) {
						ans = ITEM_ID_BRICK;
						Data.brick -= Irainin.amount;
					}
					break;
				case ITEM_ID_RING:
					// 指輪
					if ( Data.ring >= Irainin.amount ) {
						ans = ITEM_ID_RING;
						Data.ring -= Irainin.amount;
					}
					break;
				case ITEM_ID_SCULPTURE:
					// 彫刻
					if ( Data.sculpture >= Irainin.amount ) {
						ans = ITEM_ID_SCULPTURE;
						Data.sculpture -= Irainin.amount;
					}
					break;
				case ITEM_ID_W_HOUSE:
					// 木の家
					if ( Data.wHouse >= Irainin.amount ) {
						ans = ITEM_ID_W_HOUSE;
						Data.wHouse -= Irainin.amount;
					}
					break;
				case ITEM_ID_S_HOUSE:
					// 石の家
					if ( Data.sHouse >= Irainin.amount ) {
						ans = ITEM_ID_S_HOUSE;
						Data.sHouse -= Irainin.amount;
					}
					break;
				case ITEM_ID_W_MANSION:
					// 木の豪邸
					if ( Data.wMansion >= Irainin.amount ) {
						ans = ITEM_ID_W_MANSION;
						Data.wMansion -= Irainin.amount;
					}
					break;
				case ITEM_ID_S_MANSION:
					// 石の豪邸
					if ( Data.sMansion >= Irainin.amount ) {
						ans = ITEM_ID_S_MANSION;
						Data.sMansion -= Irainin.amount;
					}
					break;
				case ITEM_ID_TANK:
					// 水槽
					if ( Data.tank >= Irainin.amount ) {
						ans = ITEM_ID_TANK;
						Data.tank -= Irainin.amount;
					}
					break;
			}

			if ( ans >= 1 ) {
				// 依頼人の欲しいものを持っていた
				Data.money += Irainin.reward;
				Data.addMoney += Irainin.reward;

				// 喜んでいるアニメーション
				SPR_setAnim(sprites[17],1);

				// 効果音（コイン）
				SND_startPlay_4PCM_ENV(
						SE_Button_8,
						sizeof(SE_Button_8),
						SOUND_PCM_CH4,	// @suppress("Symbol is not resolved")
						FALSE 			// @suppress("Symbol is not resolved")
				);

				// コイン
				sprites[18]=SPR_addSprite(
						&jump_coin,
						PlayerData.x + 20 - Camera.x,
						PlayerData.y - 32,
						TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
				);
			//	SPR_setAnim(sprites[18],0);
				coin_time = 120;
			}
		}

		// 画面外にいったらリリース
		if ( Irainin.x - Camera.x + PLAYER_WIDTH < 0){
			SPR_releaseSprite(sprites[17]);
			SPR_releaseSprite(sprites[19]);
			completedSwitch = 0;
			Irainin_showed = 0;
		}

		// コイン
		if ( coin_time >= 1 ) {
			SPR_setPosition(
					sprites[18],
					PlayerData.x + 20 - Camera.x,
					PlayerData.y - 32
			);
			coin_time--;
			if ( coin_time <= 0 ) {
				SPR_releaseSprite(sprites[18]);
			}
		}

		SPR_update();
		VDP_waitVSync();

		// デバッグコマンド
		if ( ( pad1 & BUTTON_START || Camera.x>goal_in ) // @suppress("Suggested parenthesis around expression") // @suppress("Symbol is not resolved")
			&& Data.explore_mode == 1
		){
			Data.gm=AFTERDAY;
			break;
		}
		if ( ( pad1 & BUTTON_START || Camera.x>goal_in ) && Data.explore_mode==0 ){ // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
			Data.gm=WORK;
			break;
		}

		if ( Data.money >= DEBT_NUM ){ // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
			// 借金返済
			Data.gm=WORK;
			break;
		}
	}

    return Data;
}
