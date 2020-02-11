#include <genesis.h>

#define WIDTH 320
#define HEIGHT 224

#define PLAYER_WIDTH 48
#define PLAYER_HEIGHT 48

#define SPRITE_NUM 64
#define CAMERA_MOVE 1

#define TOP_HEIGHT 124
#define BOTTOM_HEIGHT 224-48
#define CAMERA_SCROLL
#define SCROLL_DIFF 32
#define SOZAI_SUU 1
#define HUMMER_RANGE 48

#define PLAYER_WAIT 0
#define PLAYER_WALK 1
#define PLAYER_PUNCH 2
#define PLAYER_HAMMER 3
#define PLAYER_BUCKET 4
#define PLAYER_BOMB 5
#define PLAYER_SAW 6

#define ITEM_ID_KI01 1
#define ITEM_ID_KI02 2
#define ITEM_ID_KI03 3
#define ITEM_ID_KI04 4
#define ITEM_ID_KINNZANN01 5
#define ITEM_ID_koori01 6
#define ITEM_ID_koori02 7
#define ITEM_ID_koori03 8
#define ITEM_ID_KOUMYAKU01 9
#define ITEM_ID_KOUMYAKU02 10
#define ITEM_ID_MIZU01 11
#define ITEM_ID_MIZU02 12
#define ITEM_ID_ROCK01 13
#define ITEM_ID_ROCK02 14
#define ITEM_ID_ROCK03 15
#define ITEM_ID_TETUKUZU01 16

Sprite* sprites[SPRITE_NUM];

// 0:player
// 1:NPC
// 2:ä‚1
// 3:
// 4:
// 5:
// 6:

enum game_mode {
    LOGO,
    TITLE,
	INIT,
	DAY,
    GAME,
	WORK,
	AFTERDAY,
	HOW_TO_PLAY,
};

typedef struct
{
	s16 water;
	s16 stone;
	s16 metal;
	s16 wood;
	s16 attack;
	s16 hammer;
	s16 bucket;
	s16 bomb;
	s16 bflag;
	s16 saw;
	s16 chair;
	s16 desk;
	s16 chest;
	s16 brick;
	s16 ring;
	s16 sculpture;
	s16 wHouse;
	s16 sHouse;
	s16 wMansion;
	s16 sMansion;
	s16 tank;

	enum game_mode gm;
	s16 money;
	s16 explore_mode; //0 or 1 çsÇ´Ç©ãAÇË
	s16 date;
	s16 addMoney;
} datas;

datas logo(datas Data);
datas title(datas Data);
datas init(datas Data);
datas day(datas Data);
datas afterDay(datas Data);
datas game(datas Data);
datas work(datas Data);
datas howToPlay(datas Data);
void text( int num, int x, int y );
void fadeIn( u16 palette[] );
void fadeOut();
int VDP_BG( VDPPlan PLAN,
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

struct camera
{
	s16 x;
	s16 y;
};
