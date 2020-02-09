#include <genesis.h>

#include "resource.h"
#include "resource_game.h"

#include "main.h"

#define TOP_HEIGHT 124
#define BOTTOM_HEIGHT 224-48
#define CAMERA_SCROLL
#define SCROLL_DIFF 32
#define SOZAI_SUU 1
#define HUMMER_RANGE 48

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
	char showed;
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

s16 playerMoveOn(
		s16 *x,
		s16 *y,
		s16 cameraX,
		s16 cameraY
);

//void cameraScroll(
//		s16 *cameraX,
//		s16 *playerX
//);

int VDP_BG(
		VDPPlan PLAN,
		int PAL,
		int ind,
		int type,
		int tile_x,
		int tile_y,
		Image image1,
		Image image2,
		Image image3,
		Image image4,
		Image image5
);

datas game(datas Data) {

    SYS_disableInts();

    s16 num2;
    struct playerScene PlayerData;
    PlayerData.x=0;
    PlayerData.y=122;
    struct camera Camera;
    Camera.x=0;
    Camera.y=122;
    u16 tests[SOZAI_SUU][9]=
    {
    	{ 400, 180,FALSE,FALSE,1,2,4,8,3} // @suppress("Symbol is not resolved")
    };
    char tests_name[SOZAI_SUU][64]=
    {
    		"てごろないわ"
    };
    u16 NPCs[7][5]=
    {
    		{1,1,100, 400, 124}
    };//アイテムID/個数/報酬/X/Y
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
	   SOUND_PCM_CH1, // @suppress("Symbol is not resolved")
	   TRUE // @suppress("Symbol is not resolved")
   );

//  SPR_init();
    memcpy(&palette[0], Player.palette->data, 16 * 2);
    memcpy(&palette[16], rock01.palette->data, 16 * 2);
    memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
    memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	sprites[0] = SPR_addSprite(&Player, 0, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
	SPR_setPosition(sprites[0], 0 ,0);

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

//  VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE); // @suppress("Symbol is not resolved")
    fadeIn( palette );

	int walk_count = 0;
	int fightMode=0;
	int fightModeTimer;

	int bg_b_count = 0;
	int bg_a_count = 0;

//    int vdp_b_clean_x = 0;
//    int vdp_a_clean_x = 0;

//    u16 ind_c = 450;
//    u16 ind_d = 1200;

    //依頼人関係
    s16 Irainin_showed=0;
    struct irainin Irainins[1];
    for(s16 i=0;i<1;i++)
    {
    	for(s16 h=0;h<64;h++)
    	{
    		Irainins[i].name[h]=NPCsItemName[i][h];
    	}

    	Irainins[i].item_id = NPCs[i][0];
    	Irainins[i].amount = NPCs[i][1];
    	Irainins[i].reward = NPCs[i][2];
    	Irainins[i].x = NPCs[i][3];
    	Irainins[i].y = NPCs[i][4];
    }
    s16 completedSwitch=0;

    sprites[7]=SPR_addSprite(&jump_coin,350,0,TILE_ATTR(PAL0, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
	s16 coin_time=0;

    while(TRUE) // @suppress("Symbol is not resolved")
   {

    //	text(Sozais[0].x,0,0);
    //	text(PlayerData.x,0,1);
    	bg_b_count += CAMERA_MOVE;

    	if ( bg_b_count >= 64 * 8 ) {
    		VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); // @suppress("Symbol is not resolved")
    		vdp_b_count++;
    		vdp_b_count %= 5;
    		vdp_b_x += 8;
    		vdp_b_x %= 64;
    	    bg_b_count -= 64 * 8;
    	}

    	bg_a_count += CAMERA_MOVE;
    	if ( bg_a_count >= 64 ) {
    		VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image ); // @suppress("Symbol is not resolved")
    		vdp_a_count++;
    		vdp_a_count %= 5;
    		vdp_a_x += 8;
    		vdp_a_x %= 64;
    	    bg_a_count -= 64;
    	}

    	u16 pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
    	if( pad1 & BUTTON_A ) // @suppress("Symbol is not resolved")
    	{

			SND_startPlay_4PCM_ENV(
				Punch_wav,
				sizeof(Punch_wav),
				SOUND_PCM_CH2, // @suppress("Symbol is not resolved")
				FALSE // @suppress("Symbol is not resolved")
			);
    		fightMode=1;
			fightModeTimer=30;
			if(Data.hammer>0)SPR_setAnim(sprites[0],3);
			else SPR_setAnim(sprites[0],2);

    	}
    	s16 walkMode=playerMoveOn(&PlayerData.x,&PlayerData.y,Camera.x,Camera.y);
    	if(walkMode==1 && fightMode!=1) {
    		SPR_setAnim(sprites[0], 1);

    		if ( walk_count == 0 ) {
				// 効果音を鳴らしてみる
				SND_startPlay_4PCM_ENV(
						SE_Footstep_8,
						sizeof(SE_Footstep_8),
						SOUND_PCM_CH3, // @suppress("Symbol is not resolved")
						FALSE // @suppress("Symbol is not resolved")
				);
    		}
    	    walk_count++;
    	    if ( walk_count > 30 ) {
    	    	walk_count = 0;
    	    }
    	}
    	else if(fightMode!=1 && walkMode!=1) {
    		SPR_setAnim(sprites[0], 0);
    		walk_count = 0;
    	}
    	if(fightMode==1){
    		fightModeTimer--;
    		SPR_setAnim(sprites[0],2);
    		if(fightModeTimer<=0) fightMode=0;
    	}

    	Camera.x += CAMERA_MOVE;

    	VDP_setHorizontalScroll(PLAN_A, -Camera.x);
		VDP_setHorizontalScroll(PLAN_B,-Camera.x >> 3);

		SPR_setPosition(sprites[0],PlayerData.x-Camera.x,PlayerData.y);
		for(s16 i=0;i<SOZAI_SUU;i++)
			{
				if(Sozais[i].broke==1) continue;
				if(Sozais[i].showed==1)
				{
					SPR_setPosition(sprites[i+3],(Sozais[i].x-Camera.x),Sozais[i].y);
				//	u16 num=playerButton();
					if(pad1 & BUTTON_A) // @suppress("Symbol is not resolved")
					{

						SND_startPlay_4PCM_ENV(
							Punch_wav,
							sizeof(Punch_wav),
							SOUND_PCM_CH2, // @suppress("Symbol is not resolved")
							FALSE // @suppress("Symbol is not resolved")
						);}

					if(pad1 & BUTTON_A) // @suppress("Symbol is not resolved")
					{
						num2=0;

						if ( PlayerData.x+24 > Sozais[i].x
						  && PlayerData.x+24 < Sozais[i].x+48
						  && PlayerData.y+48 > Sozais[i].y
						  && PlayerData.y+48 < Sozais[i].y+48
						){num2=1;}

						if(num2==1) {
							Sozais[i].HP-=1;
								SND_startPlay_4PCM_ENV(
										SE_Explosion_8,
										sizeof(SE_Explosion_8),
										SOUND_PCM_CH2, // @suppress("Symbol is not resolved")
										FALSE // @suppress("Symbol is not resolved")
								);
								Data.water=Sozais[i].genso[0];
								Data.stone=Sozais[i].genso[1];
								Data.metal=Sozais[i].genso[2];
								Data.wood=Sozais[i].genso[3];
								Sozais[i].broke=1;
								SPR_setPosition(sprites[i+3], 350 ,0);

							}
						if(Sozais[i].x<Camera.x){SPR_releaseSprite(sprites[i+3]); Sozais[i].broke=1;}
					}

				}
			}

		// 依頼人
		   if ( Data.explore_mode == 1 ) {
		    	// 帰りの処理

				//依頼人
				if(Camera.x>=0 && Irainin_showed!=1){
					sprites[6] = SPR_addSprite(
							&NPC,
							Irainins[Data.date-1].x,
							Irainins[Data.date-1].y,
							TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
					);
					Irainin_showed=1;
				}
				if(Irainin_showed==1) {
					SPR_setPosition(
						sprites[6],
						Irainins[Data.date-1].x-Camera.x,	// カメラ移動を意識するため、毎フレーム処理
						Irainins[Data.date-1].y
					);
				}
//				if(Camera.x>=260){
//					SPR_releaseSprite(sprites[6]);
//				}

//				text(Data.date, 0, 5);
//				text(Irainins[Data.date-1].item_id, 0, 6);
//				text(Irainins[Data.date-1].amount, 0, 7);
//				text(Data.desk, 0, 8);

				//プレイヤーの依頼人関係処理
				if ( PlayerData.x > Irainins[Data.date-1].x-48
				  && PlayerData.x < Irainins[Data.date-1].x+48
				  && PlayerData.y > Irainins[Data.date-1].y-48
				  && PlayerData.y < Irainins[Data.date-1].y+48
				  && completedSwitch == 0
				) {
					Data.hammer=1;
					s16 ans=0;
//					switch(Irainins[Data.date-1].item_id)
//					{
//						case 0:
//							ans=(Data.chair>=Irainins[Data.date-1].amount? 1:0);
//							break;
//						case 1:
//							ans=(Data.desk>=Irainins[Data.date-1].amount? 1:0);
//							break;
//						case 2:
//							ans=(Data.sculpture>=Irainins[Data.date-1].amount? 1:0);
//							break;
//						case 3:
//							ans=(Data.tank>=Irainins[Data.date-1].amount? 1:0);
//							break;
//						case 4:
//							ans=(Data.ring>=Irainins[Data.date-1].amount? 1:0);
//							break;
//						case 5:
//							ans=(Data.sHouse>=Irainins[Data.date-1].amount? 1:0);
//							break;
//						case 6:
//							ans=(Data.wMansion>=Irainins[Data.date-1].amount? 1:0);
//							break;
//					}

					ans = 1;
					if(ans==1)
					{
						Data.hammer-=Irainins[Data.date-1].amount;
						Data.money+=Irainins[Data.date-1].reward;
						Data.addMoney+=Irainins[Data.date-1].reward;
						SPR_setAnim(sprites[6],1);
						SND_startPlay_4PCM_ENV(
								SE_Explosion_8,
								sizeof(SE_Explosion_8),
								SOUND_PCM_CH2, // @suppress("Symbol is not resolved")
								FALSE // @suppress("Symbol is not resolved")
						);
						SPR_setPosition(sprites[7],PlayerData.x,PlayerData.y);
						SPR_setAnim(sprites[7],0);
						coin_time=30;
					}
					completedSwitch=1;
				}

				if(coin_time>1) {
					coin_time--;
				}

				if(coin_time==1) {
					coin_time--;
					SPR_setPosition(sprites[7],350,0);
				}
		    }



        SPR_update();
        VDP_waitVSync();

        // デバッグコマンド
//      u16 pad1 =JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
        if ((pad1 & BUTTON_START || Camera.x>goal_in) &&Data.explore_mode==1){ // @suppress("Suggested parenthesis around expression") // @suppress("Symbol is not resolved")
                   VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
                   VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
                   VDP_setHorizontalScroll(PLAN_B, 0);
                   VDP_setVerticalScroll(PLAN_B, 0);
                   VDP_setHorizontalScroll(PLAN_A, 0);
                   VDP_setVerticalScroll(PLAN_A, 0);
                   s16 i = 0;
                   for (i = 0; i < 7; i++) {
                   	SPR_releaseSprite(sprites[i]);
                   }
                   //SPR_end();

       			Data.gm=AFTERDAY;
       			break;
               }
        if ((pad1 & BUTTON_START || Camera.x>goal_in) &&Data.explore_mode==0 ){ // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
            VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
            VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
            VDP_setHorizontalScroll(PLAN_B, 0);
            VDP_setVerticalScroll(PLAN_B, 0);
            VDP_setHorizontalScroll(PLAN_A, 0);
            VDP_setVerticalScroll(PLAN_A, 0);
            SPR_releaseSprite(sprites[0]);
            //SPR_end();
            s16 i = 0;
            for (i = 0; i < 7; i++) {
            	SPR_releaseSprite(sprites[i]);
            }

			Data.gm=WORK;
			break;
        }

   }

    return Data;
}
s16 playerMoveOn(s16 *x,s16 *y,s16 cameraX,s16 cameraY)
{
	s16 mode=0;
	u16 value = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
	if(value&BUTTON_LEFT){*x-=2;mode=1;} // @suppress("Symbol is not resolved")
	if(value&BUTTON_RIGHT){ *x+=2;mode=1;} // @suppress("Symbol is not resolved")
	if(value&BUTTON_UP){*y-=1;mode=1;} // @suppress("Symbol is not resolved")
	if(value&BUTTON_DOWN){*y+=1;mode=1;} // @suppress("Symbol is not resolved")
	//はじっこ処理
	if(*y>BOTTOM_HEIGHT) *y=BOTTOM_HEIGHT;
	if(*y<TOP_HEIGHT) *y=TOP_HEIGHT;
	if(*x<0){*x=0; mode=1;}
	if(*x<cameraX){*x=cameraX; mode=1;}
	if(*x>cameraX+320-48) *x=cameraX+320-48;
	return mode;
}
//u16 playerButton()
//{
//	return JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
//}

//void cameraScroll(fix32 *cameraX,fix32 *playerX)
//{
//	*cameraX=cameraX+5;
//	*playerX-=5;
//
//}


