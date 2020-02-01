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
#define CAMERA_MOVE 1
#define goal_in 5000

struct playerScene
{
	s16 x;
	s16 y;
};
struct camera
{
	s16 x;
	s16 y;
};
typedef struct sozai
{
	char name[64];
	s16 x;
	s16 y;
	char showed;
	char broke;
	s16 genso[4];
	s16 HP;
};

s16 playerMoveOn(s16 *x,s16 *y,s16 cameraX,s16 cameraY);
void cameraScroll(s16 *cameraX,s16 *playerX);
u16 playerButton();
int VDP_BG( VDPPlan PLAN, int PAL, int ind, int type, int tile_x, int tile_y, Image image1, Image image2, Image image3, Image image4, Image image5 );

struct datas game(struct datas Data) {
	SPR_init();
    // disable interrupt when accessing VDP
	s16 num2;
    SYS_disableInts();
    struct playerScene PlayerData;
    PlayerData.x=0;
//  PlayerData.x=160;
    PlayerData.y=122;
    struct camera Camera;
    Camera.x=0;
//  Camera.x=160;
    Camera.y=122;
    u16 tests[SOZAI_SUU][9]=
    {
    	{ 400, 180,FALSE,FALSE,1,2,4,8,3} // @suppress("Symbol is not resolved")
    };
    char tests_name[SOZAI_SUU][64]=
    {
    		"てごろないわ"
    };
    u16 NPCs[7][2]=
    {
    		{1,100}
    };//アイテムID/報酬
    char NPCsItemName[7][64]=
    {
    		"ハンマー"
    };

    struct sozai Sozais[SOZAI_SUU];
    for(s16 i;i<SOZAI_SUU;i++)
    {
//    	strcpy(Sozais[i].name,tests_name[i]);
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
	   SOUND_PCM_CH1,
	   TRUE
   );

//  SPR_init();
    memcpy(&palette[0], Player.palette->data, 16 * 2);
    memcpy(&palette[16], rock01.palette->data, 16 * 2);
    memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
    memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);
    memcpy(&palette[64], NPC.palette->data, 16 * 2);

	sprites[0] = SPR_addSprite(&Player, 0, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	SPR_setPosition(sprites[0], 0 ,0);
	SPR_setAnim(sprites[0], 0);

    // 背景B
    int vdp_b_count = 0;
    int vdp_b_x = 0;
    u16 ind_b = TILE_USERINDEX;
    ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64;
    ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64;
    ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64;
    ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64;
    ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64;
    ind_b = TILE_USERINDEX;
    ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64;

    // 背景A
    int vdp_a_count = 0;
    int vdp_a_x = 0;
    u16 ind_a = 800;
    ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64;
    ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64;
    ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64;
    ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64;
    ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64;
    ind_a = 800;
    ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64;

    SYS_enableInts();
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);



	int walk_count = 0;
	int fightMode=0;
	int fightModeTimer;

	int bg_b_count = 0;
	int bg_a_count = 0;

    int vdp_b_clean_x = 0;
    int vdp_a_clean_x = 0;

    u16 ind_c = 450;
    u16 ind_d = 1200;

    //依頼人関係
    s16 Irainin_showed=0;

    while(TRUE)
   {

    	text(PlayerData.y,0,0);
    	bg_b_count += CAMERA_MOVE;

    	if ( bg_b_count >= 64 * 8 ) {
    		if ( Camera.x < 500 ) {
    			ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );
    		}
       		else if ( Camera.x < 2500 ) {
       			VDP_setPalette(2, soradoukutu_1_image.palette->data);
       			ind_c = VDP_BG( PLAN_B, PAL2, ind_c, ++vdp_b_count, vdp_b_x, 0, soradoukutu_1_image, soradoukutu_2_image, soradoukutu_3_image, soradoukutu_4_image, soradoukutu_5_image );
       		}
       		else {
       			VDP_setPalette(2, doukutu_1_image.palette->data);
       			ind_b = VDP_BG( PLAN_B, PAL2, ind_b, ++vdp_b_count, vdp_b_x, 0, doukutu_1_image, doukutu_2_image, doukutu_3_image, doukutu_4_image, doukutu_5_image );
       		}
    		vdp_b_count %= 5;
    		if ( vdp_b_count == 0 ) {
    			ind_b = TILE_USERINDEX;
    			ind_c = 450;
    		}

    		vdp_b_x += 8;
    		vdp_b_x %= 64;
    	    bg_b_count -= 64 * 8;
    	}

    	bg_a_count += CAMERA_MOVE;
    	if ( bg_a_count >= 64 ) {
    		if ( Camera.x < 2800 ) {
    			ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );
    		}
       		else if ( Camera.x < 3000 ) {
       			VDP_setPalette(3, zimenntodoukutu_1_image.palette->data);
       			ind_d = VDP_BG( PLAN_A, PAL3, ind_d, ++vdp_a_count, vdp_a_x, 0, zimenntodoukutu_1_image, zimenntodoukutu_2_image, zimenntodoukutu_3_image, zimenntodoukutu_4_image, zimenntodoukutu_5_image );
      		}
    		else {
       			VDP_setPalette(3, doukutuzimen_1_image.palette->data);
    			ind_a = VDP_BG( PLAN_A, PAL3, ind_a, ++vdp_a_count, vdp_a_x, 0, doukutuzimen_1_image, doukutuzimen_2_image, doukutuzimen_3_image, doukutuzimen_4_image, doukutuzimen_5_image );
    		}
    		vdp_a_count %= 5;
    		if ( vdp_a_count == 0 ) {
    			ind_a = 800;
    			ind_d = 1200;
    		}
    		vdp_a_x += 8;
    		vdp_a_x %= 64;
    	    bg_a_count -= 64;
    	}

    	text( PlayerData.x, 0, 0 );
    	text( Camera.x, 0, 1 );

    	u16 num=playerButton();
    	if(num & BUTTON_A==1)
    	{

			SND_startPlay_4PCM_ENV(
				Punch_wav,
				sizeof(Punch_wav),
				SOUND_PCM_CH2,
				FALSE
			);
    		fightMode=1;
			fightModeTimer=30;
			SPR_setAnim(sprites[0],2);
    	}
    	s16 walkMode=playerMoveOn(&PlayerData.x,&PlayerData.y,Camera.x,Camera.y);
    	if(walkMode==1 && fightMode!=1) {
    		SPR_setAnim(sprites[0], 1);

    		if ( walk_count == 0 ) {
				// 効果音を鳴らしてみる
				SND_startPlay_4PCM_ENV(
						SE_Footstep_8,
						sizeof(SE_Footstep_8),
						SOUND_PCM_CH3,
						FALSE
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

		SPR_setPosition(sprites[0],160+PlayerData.x-Camera.x,PlayerData.y);
		for(s16 i=0;i<SOZAI_SUU;i++)
			{
				if(Sozais[i].broke==1) continue;
				if(Sozais[i].showed==1)
				{
					SPR_setPosition(sprites[i+3],(Sozais[i].x-Camera.x),Sozais[i].y);
					u16 num=playerButton();
					if(playerButton()&BUTTON_A)
					{

						SND_startPlay_4PCM_ENV(
							Punch_wav,
							sizeof(Punch_wav),
							SOUND_PCM_CH2,
							FALSE
						);}

					if(num & BUTTON_A)
					{
						num2=0;

						if ( PlayerData.x+24 > Sozais[i].x
						  && PlayerData.x+24 < Sozais[i].x+48
						  && PlayerData.y+24 > Sozais[i].y
						  && PlayerData.y+24 < Sozais[i].y+48
						) {
							num2=1;
						}
						num2=1;
						if(num2==1) {
							Sozais[i].HP-=1;
							if(Sozais[i].HP<=0){
								SND_startPlay_4PCM_ENV(
										SE_Explosion_8,
										sizeof(SE_Explosion_8),
										SOUND_PCM_CH2,
										FALSE
								);
								Data.water=Sozais[i].genso[1];
								Data.stone=Sozais[i].genso[2];
								Data.metal=Sozais[i].genso[3];
								Data.wood=Sozais[i].genso[4];
								Sozais[i].broke=1;
								SPR_setPosition(sprites[i+3], 350 ,0);

								// 効果音を鳴らしてみる



							}
													}
//						if(Sozais[i].x<Camera.x){SPR_setAnim(sprites[i+3],-1); Sozais[i].broke=1;}
					}

				}
				else if(Sozais[i].x<=Camera.x+320 && Sozais[i].showed!=1)
					{
						Sozais[i].showed =1;
						sprites[i+3] = SPR_addSprite(
											&rock01,
											Sozais[i].x-Camera.x,
											Sozais[i].y,
											TILE_ATTR(PAL1, TRUE, FALSE, FALSE)
									);
					}
			}


        SPR_update();
        VDP_waitVSync();

        //依頼人はこのへん
        if(Camera.x+320>=660 && Irainin_showed!=1){sprites[6] = SPR_addSprite(&NPC,660-Camera.x,124,TILE_ATTR(PAL0, TRUE, FALSE, FALSE));Irainin_showed=1;}
        if(Irainin_showed==1) SPR_setPosition(sprites[6],660-Camera.x,124);


        //プレイヤーの依頼人関係処理
//        if(Data.explore_mode==1 && Camera.x+160>=500)

        // デバッグコマンド
        u16 pad1 =JOY_readJoypad(JOY_1);
        if (pad1 & BUTTON_START || Camera.x>goal_in){
            VDP_clearPlan(PLAN_A, TRUE);
            VDP_clearPlan(PLAN_B, TRUE);
            VDP_setHorizontalScroll(PLAN_B, 0);
            VDP_setVerticalScroll(PLAN_B, 0);
            VDP_setHorizontalScroll(PLAN_A, 0);
            VDP_setVerticalScroll(PLAN_A, 0);
            //SPR_end();
			Data.gm=WORK;
			break;
        }

   }

    return Data;
}
s16 playerMoveOn(s16 *x,s16 *y,s16 cameraX,s16 cameraY)
{
	s16 mode=0;
	u16 value = JOY_readJoypad(JOY_1);
	if(value&BUTTON_LEFT){*x-=2;mode=1;}
	if(value&BUTTON_RIGHT){ *x+=2;mode=1;}
	if(value&BUTTON_UP){*y-=1;mode=1;}
	if(value&BUTTON_DOWN){*y+=1;mode=1;}
	//はじっこ処理
	if(*y>BOTTOM_HEIGHT) *y=BOTTOM_HEIGHT;
	if(*y<TOP_HEIGHT) *y=TOP_HEIGHT;
	if(*x<0){*x=0; mode=1;}
	if(*x<cameraX-160){*x=cameraX-160; mode=1;}
	if(*x>cameraX+160-48) *x=cameraX+160-48;
	return mode;
}
u16 playerButton()
{
	s16 num=0;
	return JOY_readJoypad(JOY_1);

}
//void cameraScroll(fix32 *cameraX,fix32 *playerX)
//{
//	*cameraX=cameraX+5;
//	*playerX-=5;
//
//}

//背景の描画
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
) {
	Image image;

	switch ( type ) {
	case 1:
		image = image1;
		break;
	case 2:
		image = image2;
		break;
	case 3:
		image = image3;
		break;
	case 4:
		image = image4;
		break;
	case 5:
		image = image5;
		break;
	}

	VDP_drawImageEx(
			PLAN,
			&image,
			TILE_ATTR_FULL(PAL, FALSE, FALSE, FALSE, ind),
		//	TILE_ATTR_FULL(PAL, FALSE, FALSE, FALSE, 1),
			tile_x,
			tile_y,
			FALSE,
			TRUE
	);
	ind += image.tileset->numTile;

//	if ( ind > 400 && ind < 500 ) {
//		ind = TILE_USERINDEX;
//	}

	// スプライト領域を避ける
	if ( ind > 880 && ind < 980 ) {
		ind = 980;
	}
//	if ( ind > 1350 ) {
//		ind = 500;
//	}

//	text( ind, 0, 2 );

	return ind;
}


