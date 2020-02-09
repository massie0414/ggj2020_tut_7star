#include <genesis.h>

#include "resource.h"
#include "main.h"

s16 goal_in=5000;

struct playerScene
{
	s16 x;
	s16 y;
};

struct sozai
{
	char name[64];
	s16 x;
	s16 y;
	char showed;	// 表示
	char broke;
	s16 genso[4];
	s16 HP;
};

struct irainin
{
	s16 amount;
	s16 item_id;
	char name[64];
	s16 reward;
	s16 x;
	s16 y;
};


datas game(datas Data) {

	SYS_disableInts();

	struct playerScene PlayerData;
	PlayerData.x=0;
	PlayerData.y=122;
	struct camera Camera;
	Camera.x=0;
	Camera.y=122;
	u16 tests[SOZAI_SUU][9]=
	{
			//  x,   y,showed,broke,genso1,genso2,genso3,genso4,HP
			{ 400, 180, FALSE,FALSE,     1,     2,     4,     8, 60 } // @suppress("Symbol is not resolved")
	};
	char tests_name[SOZAI_SUU][64]=
	{
			"てごろないわ"
	};
	u16 NPCs[7][5]=
	{
			//アイテムID/個数/報酬/X/Y
			{1,1,100, 400, 124}
	};
	char NPCsItemName[7][64]=
	{
			"ハンマー"
	};

	struct sozai Sozais[SOZAI_SUU];
	for(s16 i;i<SOZAI_SUU;i++)
	{
		for(s16 h;h<64;h++)
		{
			Sozais[i].name[h]=tests_name[i][h];
		}
		Sozais[i].x = tests[i][0];
		Sozais[i].y = tests[i][1];
		Sozais[i].showed=tests[i][2];
		Sozais[i].broke=tests[i][3];
		Sozais[i].genso[0]=tests[i][4];
		Sozais[i].genso[1]=tests[i][5];
		Sozais[i].genso[2]=tests[i][6];
		Sozais[i].genso[3]=tests[i][7];
		Sozais[i].HP=tests[i][8];
	}

	Data.gm = GAME;

	u16 palette[128];

	// BGM再生
	SND_startPlay_4PCM_ENV(
		BGM_Sub_8,
		sizeof(BGM_Sub_8),
		SOUND_PCM_CH1,	// @suppress("Symbol is not resolved")
		TRUE 			// @suppress("Symbol is not resolved")
	);

	memcpy(&palette[0], NPC.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	// プレイヤー
	sprites[0] = SPR_addSprite(&Player, 0, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
	SPR_setPosition(sprites[0], 0 ,0);

	// 岩
	Sozais[0].showed =1;
	sprites[3] = SPR_addSprite(
			&rock01,
			Sozais[0].x-Camera.x,
			Sozais[0].y,
			TILE_ATTR(PAL1, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
	);

	// 背景B
	int vdp_b_count = 0;
	int vdp_b_x = 0;
	int ind_b[5];
	u16 ind = TILE_USERINDEX; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

	// 背景A
	int vdp_a_count = 0;
	int vdp_a_x = 0;
	int ind_a[5];
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")

	// 追加背景B
	VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++;	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

	// 追加背景A
	VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")

	SYS_enableInts();

	fadeIn( palette );

	int walk_count = 0;
	int fightMode = 0;
	int fightModeTimer = 0;

	int bg_b_count = 0;
	int bg_a_count = 0;

	//依頼人関係
	s16 Irainin_showed=0;
	struct irainin Irainins[1];
	for (s16 i = 0; i < 1; i++ ) {
		for ( s16 h = 0; h < 64; h++ ) {
			Irainins[i].name[h] = NPCsItemName[i][h];
		}
		Irainins[i].item_id = NPCs[i][0];
		Irainins[i].amount = NPCs[i][1];
		Irainins[i].reward = NPCs[i][2];
		Irainins[i].x = NPCs[i][3];
		Irainins[i].y = NPCs[i][4];
	}
	s16 completedSwitch = 0;

	// コイン
	sprites[7]=SPR_addSprite(
			&jump_coin,
			350,
			0,
			TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
	);
	s16 coin_time=0;

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

		u16 pad1 = JOY_readJoypad(JOY_1);	// @suppress("Symbol is not resolved")

		if( ( pad1 & BUTTON_A ) && fightMode == 0 ) {	// @suppress("Symbol is not resolved")
			// 効果音（攻撃）
			SND_startPlay_4PCM_ENV(
				Punch_wav,
				sizeof(Punch_wav),
				SOUND_PCM_CH2,	// @suppress("Symbol is not resolved")
				FALSE 			// @suppress("Symbol is not resolved")
			);

			fightMode=1;
			fightModeTimer=30;
			if ( Data.hammer > 0 ) {
				SPR_setAnim(sprites[0],3);
			}
			else {
				SPR_setAnim(sprites[0],2);
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
			SPR_setAnim(sprites[0], 1);

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
			SPR_setAnim(sprites[0], 0);
			walk_count = 0;
		}
		else if ( fightMode == 1 ) {
			// 攻撃
			fightModeTimer--;
			SPR_setAnim(sprites[0],2);
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
			sprites[0],PlayerData.x - Camera.x,
			PlayerData.y
		);

		// 素材
		for ( s16 i = 0; i < SOZAI_SUU; i++ ) {
			if ( Sozais[i].broke == 1 ) {
				// 壊れていたら処理しない
				continue;
			}

			if ( Sozais[i].showed == 1 ) {
				// 素材を移動する
				SPR_setPosition(
					sprites[i+3],
					(Sozais[i].x-Camera.x),
					Sozais[i].y
				);

				if ( fightMode == 1 ) { // @suppress("Symbol is not resolved")
					// 攻撃中

					// 当たり判定 TODO 距離で判定した方が良い気がする
					if ( PlayerData.x+24 > Sozais[i].x
					  && PlayerData.x+24 < Sozais[i].x+48
					  && PlayerData.y+48 > Sozais[i].y
					  && PlayerData.y+48 < Sozais[i].y+48
					) {
						// 当たった
						Sozais[i].HP -= 1;

						if ( Sozais[i].HP <= 0 ) {
							// 壊れた

							// 効果音（破壊）
							SND_startPlay_4PCM_ENV(
									SE_Explosion_8,
									sizeof(SE_Explosion_8),
									SOUND_PCM_CH4, 	// @suppress("Symbol is not resolved")
									FALSE 			// @suppress("Symbol is not resolved")
							);

							Data.water=Sozais[i].genso[0];
							Data.stone=Sozais[i].genso[1];
							Data.metal=Sozais[i].genso[2];
							Data.wood=Sozais[i].genso[3];

							// スプライトの消滅
							SPR_releaseSprite(sprites[i+3]);
							Sozais[i].broke=1;
						}
					}
				}

				// 画面外
				if ( Sozais[i].x < Camera.x && Sozais[i].broke == 0 ) {
					// スプライトの消滅
					SPR_releaseSprite(sprites[i+3]);
					Sozais[i].broke=1;
				}
			}
		}

		// 依頼人
		if ( Data.explore_mode == 1 ) {
			// 帰りの処理 TODO 行きも依頼人はいる

			//依頼人
			if ( Camera.x >= 0 && Irainin_showed != 1 ) {
				sprites[6] = SPR_addSprite(
						&NPC,
						Irainins[Data.date-1].x,
						Irainins[Data.date-1].y,
						TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
				);
				Irainin_showed = 1;
			}
			if ( Irainin_showed == 1 ) {
				SPR_setPosition(
					sprites[6],
					Irainins[Data.date-1].x - Camera.x,	// カメラ移動を意識するため、毎フレーム処理
					Irainins[Data.date-1].y
				);
			}

			// 画面外にいったらリリース
			if ( Irainins[Data.date-1].x - Camera.x + PLAYER_WIDTH < 0){
				SPR_releaseSprite(sprites[6]);
			}

			//プレイヤーの依頼人関係処理
			if ( PlayerData.x > Irainins[Data.date-1].x-48
			  && PlayerData.x < Irainins[Data.date-1].x+48
			  && PlayerData.y > Irainins[Data.date-1].y-48
			  && PlayerData.y < Irainins[Data.date-1].y+48
			  && completedSwitch == 0
			) {
				// 依頼人と接触
				Data.hammer = 1;
				s16 ans = 0;
				switch ( Irainins[Data.date-1].item_id )
				{
					case 0:
						// 椅子
						ans = ( Data.chair >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 1:
						// 机
						ans = ( Data.desk >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 2:
						// 彫刻
						ans = ( Data.sculpture >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 3:
						// 水槽
						ans = ( Data.tank >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 4:
						// 指輪
						ans = ( Data.ring >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 5:
						// 石の家
						ans = ( Data.sHouse >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 6:
						// 木の豪邸
						ans = ( Data.wMansion >= Irainins[Data.date-1].amount? 1:0 );
						break;
				}

				ans = 1;	// TODO デバッグ

				if ( ans == 1 ) {
					// 依頼人の欲しいものを持っていた
					Data.hammer -= Irainins[Data.date-1].amount;
					Data.money += Irainins[Data.date-1].reward;
					Data.addMoney += Irainins[Data.date-1].reward;

					// 喜んでいるアニメーション
					SPR_setAnim(sprites[6],1);

					// 効果音（コイン）
					SND_startPlay_4PCM_ENV(
							SE_Explosion_8,
							sizeof(SE_Explosion_8),
							SOUND_PCM_CH4,	// @suppress("Symbol is not resolved")
							FALSE 			// @suppress("Symbol is not resolved")
					);

					// コイン
					SPR_setPosition(sprites[7],PlayerData.x,PlayerData.y);
					SPR_setAnim(sprites[7],0);
					coin_time = 30;
				}
				completedSwitch = 1;
			}

			if ( coin_time > 1 ) {
				coin_time--;
			}

			if ( coin_time == 1 ) {
				coin_time--;
				SPR_setPosition(sprites[7],350,0);
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
	}

    // 後処理
	VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
	VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
	VDP_setHorizontalScroll(PLAN_B, 0);
	VDP_setVerticalScroll(PLAN_B, 0);
	VDP_setHorizontalScroll(PLAN_A, 0);
	VDP_setVerticalScroll(PLAN_A, 0);

	// スプライトの削除
	s16 i = 0;
	for (i = 0; i < SPRITE_NUM; i++) {
		SPR_releaseSprite(sprites[i]);
	}
	SPR_update();

	fadeOut();

    return Data;
}
