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

struct datas
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
	s16 explore_mode; //0 or 1 s‚«‚©‹A‚è
	s16 date;
	s16 addMoney;
};


struct datas logo(struct datas Data);
struct datas title(struct datas Data);
struct datas init(struct datas Data);
struct datas day(struct datas Data);
struct datas afterDay(struct datas Data);
struct datas game(struct datas Data);
struct datas game2(struct datas Data);
struct datas game3(struct datas Data);
struct datas work(struct datas Data);
void text( int num, int x, int y );
void fadeIn();
