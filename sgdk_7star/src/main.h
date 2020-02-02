#include <genesis.h>

#define SPRITE_SIZE 8

// sprites structure (pointer of Sprite)
Sprite* sprites[SPRITE_SIZE];

enum game_mode {
    LOGO,
    TITLE,
	INIT,
	DAY,
    GAME,
	GAME2,
	GAME3,
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
datas game2(datas Data);
datas game3(datas Data);
datas work(datas Data);
void text( int num, int x, int y );
void fadeIn();
