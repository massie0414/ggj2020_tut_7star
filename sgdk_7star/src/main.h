#include <genesis.h>

#define SPRITE_NUM 64
#define CAMERA_MOVE 1

#define TOP_HEIGHT 124
#define BOTTOM_HEIGHT 224-48
#define CAMERA_SCROLL
#define SCROLL_DIFF 32
#define SOZAI_SUU 1
#define HUMMER_RANGE 48

Sprite* sprites[SPRITE_NUM];

enum game_mode {
    LOGO,
    TITLE,
	INIT,
	DAY,
    GAME,
	WORK,
	AFTERDAY,
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
//s16 playerMoveOn(
//		u16 pad1,
//		s16 *x,
//		s16 *y,
//		s16 cameraX,
//		s16 cameraY
//);


struct camera
{
	s16 x;
	s16 y;
};

