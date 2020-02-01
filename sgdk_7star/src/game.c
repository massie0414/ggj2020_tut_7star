#include <genesis.h>

#include "resource.h"
#include "resource_game.h"

#include "main.h"

#define TOP_HEIGHT 1120-240
#define BOTTOM_HEIGHT 2240-480
#define CAMERA_SCROLL 10
#define SCROLL_DIFF 32
#define SOZAI_SUU 1
#define HUMMER_RANGE 48

struct playerScene
{
	fix32 x;
	fix32 y;
};
struct camera
{
	fix32 x;
	fix32 y;
};
typedef struct sozai
{
	char name[64];
	fix32 x;
	fix32 y;
	char showed;
	char broke;
	fix32 genso[4];
};


fix32 playerMoveOn(fix32 *x,fix32 *y);
void cameraScroll(fix32 *cameraX,fix32 *playerX);
u16 playerButton();
int game() {

    // disable interrupt when accessing VDP
	fix32 num2;
    SYS_disableInts();
    struct playerScene PlayerData;
    PlayerData.x=100;
    PlayerData.y=100;
    struct camera Camera;
    Camera.x=3200/2;
    Camera.y=2240/2;
    u16 tests[SOZAI_SUU][9]=
    {
    	{2000,1800,FALSE,FALSE,5,5,5,5,1} // @suppress("Symbol is not resolved")
    };
    u16 ind;
    char tests_name[SOZAI_SUU][64]=
    {
    		"‚Ä‚²‚ë‚È‚¢‚í"
    };

    struct sozai Sozais[SOZAI_SUU];
    for(fix32 i;i<SOZAI_SUU;i++)
    {
//    	strcpy(Sozais[i].name,tests_name[i]);
    	for(fix32 h;h<64;h++)
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

    SPR_init();
    memcpy(&palette[0], Player.palette->data, 16 * 2);
    memcpy(&palette[32], soradesu_image.palette->data, 16 * 2);
    memcpy(&palette[48], rock01.palette->data, 16 * 2);
    VDP_drawImageEx(PLAN_B, &soradesu_image, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
    ind += soradesu_image.tileset->numTile;
    VDP_drawImageEx(PLAN_A, &bga_image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
    ind += bga_image.tileset->numTile;



    sprites[0] = SPR_addSprite(&Player, 0,0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    VDP_drawImageEx(PLAN_A, &bga_image, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
    ind += bga_image.tileset->numTile;
    VDP_drawImageEx(PLAN_B, &bgb_image, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
   ind += bgb_image.tileset->numTile;

    SPR_setAnim(sprites[0], 0);
    SYS_enableInts();
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);



	int walk_count = 0;
	int scroll_x = 0;
    while(TRUE)
   {
    	fix32 walkMode=playerMoveOn(&PlayerData.x,&PlayerData.y);
    	if(walkMode==1) {
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
    	else {
    		SPR_setAnim(sprites[0], 0);
    		walk_count = 0;
    	}
    //	cameraScroll(&Camera.x,&PlayerData.x);
    	Camera.x += 500;
    	PlayerData.x -= 5;

    	VDP_setHorizontalScroll(PLAN_A, fix32ToInt(-Camera.x));
		VDP_setHorizontalScroll(PLAN_B, fix32ToInt(-Camera.x) >> 3);

		SPR_setPosition(sprites[0],PlayerData.x/10,PlayerData.y/10);
		for(fix32 i=0;i<SOZAI_SUU;i++)
			{
				if(Sozais[i].broke==1) continue;
				else if(Sozais[i].showed==1)
				{
					SPR_setPosition(sprites[i+3],(Sozais[i].x-Camera.x/100)/10,Sozais[i].y/10);
					u16 num=playerButton();
					if(num &BUTTON_A)
					{
						num2=0;
						if(PlayerData.x+48>Sozais[i].x&&PlayerData.x+48<Sozais[i].x+48&&PlayerData.y>Sozais[i].y&&PlayerData.y<Sozais[i].y+48) num2=1;
						if(PlayerData.x+72>Sozais[i].x&&PlayerData.x+72<Sozais[i].x+48&&PlayerData.y>Sozais[i].y&&PlayerData.y<Sozais[i].y+48) num2=1;
						if(PlayerData.x+96>Sozais[i].x&&PlayerData.x+96<Sozais[i].x+48&&PlayerData.y>Sozais[i].y&&PlayerData.y<Sozais[i].y+48) num2=1;
						if(PlayerData.x+48>Sozais[i].x&&PlayerData.x+48<Sozais[i].x+48&&PlayerData.y+24>Sozais[i].y&&PlayerData.y+24<Sozais[i].y+48) num2=1;
						if(PlayerData.x+96>Sozais[i].x&&PlayerData.x+96<Sozais[i].x+48&&PlayerData.y+24>Sozais[i].y&&PlayerData.y+24<Sozais[i].y+48) num2=1;
						if(PlayerData.x+48>Sozais[i].x&&PlayerData.x+48<Sozais[i].x+48&&PlayerData.y+48>Sozais[i].y&&PlayerData.y+48<Sozais[i].y+48) num2=1;
						if(PlayerData.x+72>Sozais[i].x&&PlayerData.x+72<Sozais[i].x+48&&PlayerData.y+48>Sozais[i].y&&PlayerData.y+48<Sozais[i].y+48) num2=1;
						if(PlayerData.x+96>Sozais[i].x&&PlayerData.x+96<Sozais[i].x+48&&PlayerData.y+48>Sozais[i].y&&PlayerData.y+48<Sozais[i].y+48) num2=1;
//						text(fix32ToInt(num2),10,10);
						if(num2==1) {SPR_releaseSprite(sprites[i+3]); Sozais[i].broke==1;}}

				}
				else if(Sozais[i].x<=Camera.x+1600)
					{
						Sozais[i].showed =1;
						sprites[i+3] = SPR_addSprite(
											&rock01,
											(Sozais[i].x-Camera.x)/10,
											Sozais[i].y/10,
											TILE_ATTR(PAL1, TRUE, FALSE, FALSE)
									);

					}
			}
        SPR_update();
        VDP_waitVSync();
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
fix32 playerMoveOn(fix32 *x,fix32 *y)
{
	fix32 mode=0;
	u16 value = JOY_readJoypad(JOY_1);
	if(value&BUTTON_LEFT){*x-=20;mode=1;}
	if(value&BUTTON_RIGHT){ *x+=20;mode=1;}
	if(value&BUTTON_UP){*y-=10;mode=1;}
	if(value&BUTTON_DOWN){*y+=10;mode=1;}
	//‚Í‚¶‚Á‚±ˆ—
	if(*y>BOTTOM_HEIGHT) *y=BOTTOM_HEIGHT;
	if(*y<TOP_HEIGHT) *y=TOP_HEIGHT;
	if(*x<0){*x=0; mode=1;}
	if(*x/10>320-48) *x=(320-48)*10;
	return mode;
}
u16 playerButton()
{
	fix32 num=0;
	return JOY_readJoypad(JOY_1);

	return num;
}
//void cameraScroll(fix32 *cameraX,fix32 *playerX)
//{
//	*cameraX=cameraX+5;
//	*playerX-=5;
//
//}
