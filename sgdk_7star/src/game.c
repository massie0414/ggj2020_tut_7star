#include <genesis.h>

#include "resource.h"
#include "resource_game.h"

#include "main.h"

#define TOP_HEIGHT 122-24
#define BOTTOM_HEIGHT 224-48
#define CAMERA_SCROLL
#define SCROLL_DIFF 32
#define SOZAI_SUU 1
#define HUMMER_RANGE 48

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
};


s16 playerMoveOn(s16 *x,s16 *y,s16 cameraX,s16 cameraY);
void cameraScroll(s16 *cameraX,s16 *playerX);
u16 playerButton();
int game() {

    // disable interrupt when accessing VDP
	s16 num2;
    SYS_disableInts();
    struct playerScene PlayerData;
    PlayerData.x=160;
    PlayerData.y=122;
    struct camera Camera;
    Camera.x=160;
    Camera.y=122;
    u16 tests[SOZAI_SUU][9]=
    {
    	{ 400, 180,FALSE,FALSE,5,5,5,5,1} // @suppress("Symbol is not resolved")
    };
    u16 ind;
    char tests_name[SOZAI_SUU][64]=
    {
    		"‚Ä‚²‚ë‚È‚¢‚í"
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
    }
    enum game_mode gm;
    gm = GAME;
//  Sprite* sprites[6];
//  Sprite* sozaiSprites[3];
    u16 palette[64];
    SND_startPlay_4PCM_ENV(
       		BGM_Sub_8,
               sizeof(BGM_Sub_8),
               SOUND_PCM_CH1,
               FALSE
       );

    SPR_init();
    memcpy(&palette[0], Player.palette->data, 16 * 2);
    memcpy(&palette[16], rock01.palette->data, 16 * 2);
    memcpy(&palette[32], soradesu_image.palette->data, 16 * 2);
    memcpy(&palette[48], zimensample_image.palette->data, 16 * 2);

    VDP_drawImageEx(PLAN_B, &soradesu_image, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
    ind += soradesu_image.tileset->numTile;
    VDP_drawImageEx(PLAN_B, &soradesu_1_image, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 40, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
    ind += soradesu_1_image.tileset->numTile;
    VDP_drawImageEx(PLAN_B, &soradesu_1_image, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 48, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
    ind += soradesu_1_image.tileset->numTile;
    VDP_drawImageEx(PLAN_B, &soradesu_1_image, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 56, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
    ind += soradesu_1_image.tileset->numTile;
    VDP_drawImageEx(PLAN_A, &zimensample_image, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
    ind += zimensample_image.tileset->numTile;
    VDP_drawImageEx(PLAN_A, &zimensample_1_image, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 40, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
    ind += zimensample_1_image.tileset->numTile;
    VDP_drawImageEx(PLAN_A, &zimensample_1_image, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 48, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
    ind += zimensample_1_image.tileset->numTile;
    VDP_drawImageEx(PLAN_A, &zimensample_1_image, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 56, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
    ind += zimensample_1_image.tileset->numTile;

    sprites[0] = SPR_addSprite(&Player, 0,0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

    SPR_setAnim(sprites[0], 0);
    SYS_enableInts();
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);



	int walk_count = 0;
	int fightMode=0;
	int fightModeTimer;
	int scroll_x = 0;
    while(TRUE)
   {
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
				// Œø‰Ê‰¹‚ð–Â‚ç‚µ‚Ä‚Ý‚é
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
    //	cameraScroll(&Camera.x,&PlayerData.x);
    	Camera.x +=1 ;
    //	PlayerData.x -= 5;

    	VDP_setHorizontalScroll(PLAN_A, -Camera.x);
		VDP_setHorizontalScroll(PLAN_B,-Camera.x >> 3);

		SPR_setPosition(sprites[0],160+PlayerData.x-Camera.x,PlayerData.y);
		for(s16 i=0;i<SOZAI_SUU;i++)
			{
				if(Sozais[i].broke==1) continue;
				else if(Sozais[i].showed==1)
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
//						if(PlayerData.x+48>Sozais[i].x&&PlayerData.x+48<Sozais[i].x+48&&PlayerData.y>Sozais[i].y&&PlayerData.y<Sozais[i].y+48){num2=1;}
//						if(PlayerData.x+72>Sozais[i].x&&PlayerData.x+72<Sozais[i].x+48&&PlayerData.y>Sozais[i].y&&PlayerData.y<Sozais[i].y+48) num2=1;
//						if(PlayerData.x+96>Sozais[i].x&&PlayerData.x+96<Sozais[i].x+48&&PlayerData.y>Sozais[i].y&&PlayerData.y<Sozais[i].y+48) num2=1;
//						if(PlayerData.x+48>Sozais[i].x&&PlayerData.x+48<Sozais[i].x+48&&PlayerData.y+24>Sozais[i].y&&PlayerData.y+24<Sozais[i].y+48) num2=1;
//						if(PlayerData.x+96>Sozais[i].x&&PlayerData.x+96<Sozais[i].x+48&&PlayerData.y+24>Sozais[i].y&&PlayerData.y+24<Sozais[i].y+48) num2=1;
//						if(PlayerData.x+48>Sozais[i].x&&PlayerData.x+48<Sozais[i].x+48&&PlayerData.y+48>Sozais[i].y&&PlayerData.y+48<Sozais[i].y+48) num2=1;
//						if(PlayerData.x+72>Sozais[i].x&&PlayerData.x+72<Sozais[i].x+48&&PlayerData.y+48>Sozais[i].y&&PlayerData.y+48<Sozais[i].y+48) num2=1;
//						if(PlayerData.x+96>Sozais[i].x&&PlayerData.x+96<Sozais[i].x+48&&PlayerData.y+48>Sozais[i].y&&PlayerData.y+48<Sozais[i].y+48) num2=1;

						if ( PlayerData.x+24 > Sozais[i].x
						  && PlayerData.x+24 < Sozais[i].x+48
						  && PlayerData.y+24 > Sozais[i].y
						  && PlayerData.y+24 < Sozais[i].y+48
						) {
							num2=1;
						}

						if(num2==1) {
							SPR_releaseSprite(sprites[i+3]);
							Sozais[i].broke==1;

			                // Œø‰Ê‰¹‚ð–Â‚ç‚µ‚Ä‚Ý‚é
			                SND_startPlay_4PCM_ENV(
			                		SE_Explosion_8,
			                        sizeof(SE_Explosion_8),
			                        SOUND_PCM_CH2,
			                        FALSE
			                );
						}
						if(Sozais[i].x<Camera.x){SPR_setAnim(sprites[i+3],-1); Sozais[i].broke=1;}
					}

				}
				else if(Sozais[i].x<=Camera.x+160 && Sozais[i].showed!=1)
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

        // ƒfƒoƒbƒOƒRƒ}ƒ“ƒh
        u16 pad1 =JOY_readJoypad(JOY_1);
        if (pad1 & BUTTON_START){
            VDP_clearPlan(PLAN_A, TRUE);
            VDP_clearPlan(PLAN_B, TRUE);
            VDP_setHorizontalScroll(PLAN_B, 0);
            VDP_setVerticalScroll(PLAN_B, 0);
            VDP_setHorizontalScroll(PLAN_A, 0);
            VDP_setVerticalScroll(PLAN_A, 0);
			gm=WORK;
			break;
        }

   }

    return gm;
}
s16 playerMoveOn(s16 *x,s16 *y,s16 cameraX,s16 cameraY)
{
	s16 mode=0;
	u16 value = JOY_readJoypad(JOY_1);
	if(value&BUTTON_LEFT){*x-=2;mode=1;}
	if(value&BUTTON_RIGHT){ *x+=2;mode=1;}
	if(value&BUTTON_UP){*y-=1;mode=1;}
	if(value&BUTTON_DOWN){*y+=1;mode=1;}
	//‚Í‚¶‚Á‚±ˆ—
	if(*y>BOTTOM_HEIGHT) *y=BOTTOM_HEIGHT;
	if(*y<TOP_HEIGHT) *y=TOP_HEIGHT;
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
