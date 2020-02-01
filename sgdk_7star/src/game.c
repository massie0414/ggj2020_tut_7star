#include <genesis.h>

#include "resource.h"
#include "resource_game.h"

#include "main.h"

#define TOP_HEIGHT 1120-240
#define BOTTOM_HEIGHT 2240-480
#define CAMERA_SCROLL 10
#define SCROLL_DIFF 32
#define SOZAI_SUU 1

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
void chkSozais(struct sozai Sozai,fix32 cameraX);
int game() {

    // disable interrupt when accessing VDP


    SYS_disableInts();
    struct playerScene PlayerData;
    PlayerData.x=100;
    PlayerData.y=100;
    struct camera Camera;
    Camera.x=320/2;
    Camera.y=224/2;
    u16 tests[SOZAI_SUU][8]=
    {
    	{6400,2000,FALSE,FALSE,5,5,5,5} // @suppress("Symbol is not resolved")
    };
    u16 ind;
    char tests_name[SOZAI_SUU][64]=
    {
    		"‚è‚ñ‚²"
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
    memcpy(&palette[16], SozaiProto.palette->data, 16 * 2);

    VDP_drawImageEx(PLAN_B, &bgb_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æ
   ind += bgb_image.tileset->numTile;
   VDP_drawImageEx(PLAN_A, &bga_image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);//”wŒi‚Ì•`‰æA
   ind += bga_image.tileset->numTile;


    sprites[0] = SPR_addSprite(&Player, 0,0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    SPR_setAnim(sprites[0], 0);
    SYS_enableInts();
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);

	for(fix32 i=1;i<SOZAI_SUU;i++)
	{
		chkSozais(Sozais[i],Camera.x);
		if(Sozais[i].showed==1 && sprites[i+3]== NULL){
			sprites[i+3] = SPR_addSprite(
					&SozaiProto,
					Sozais[i].x-Camera.x,
					Sozais[i].y,
					TILE_ATTR(PAL1, TRUE, FALSE, FALSE)
			);
		}
	}

	int scroll_x = 0;
    while(TRUE)
   {
    	fix32 walkMode=playerMoveOn(&PlayerData.x,&PlayerData.y);
    	if(walkMode==1) SPR_setAnim(sprites[0], 1);
    	else SPR_setAnim(sprites[0], 0);
    //	cameraScroll(&Camera.x,&PlayerData.x);
    	Camera.x += 500;
    	PlayerData.x -= 5;

    	VDP_setHorizontalScroll(PLAN_A, fix32ToInt(-Camera.x));
		VDP_setHorizontalScroll(PLAN_B, fix32ToInt(-Camera.x) >> 3);

		text( Camera.x, 0, 26 );

    	SPR_setPosition(sprites[0],PlayerData.x/10,PlayerData.y/10);

        SPR_update();
        VDP_waitVSync();
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
//void cameraScroll(fix32 *cameraX,fix32 *playerX)
//{
//	*cameraX=cameraX+5;
//	*playerX-=5;
//
//}
void
chkSozais(struct sozai Sozai,fix32 cameraX)
{
	if(Sozai.showed==1 || Sozai.broke==1) return Sozai;
	if(Sozai.x<=cameraX+1600)
	{
		Sozai.showed =1;
	}
}
