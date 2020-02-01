#include <genesis.h>

#define SPRITE_SIZE 6

// sprites structure (pointer of Sprite)
Sprite* sprites[SPRITE_SIZE];

enum game_mode {
    LOGO,
    TITLE,
    GAME,
	GAME2,
	GAME3,
	WORK,
};

int logo();
int title();
int game();
int game2();
int game3();
int work();
void text( int num, int x, int y );
void fadeIn();
