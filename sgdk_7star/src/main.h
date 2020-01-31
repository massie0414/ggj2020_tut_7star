#include <genesis.h>

#define TEST_SIZE 1

// sprites structure (pointer of Sprite)
Sprite* sprites[TEST_SIZE];

enum game_mode {
    LOGO,
    TITLE,
    GAME,
	GAME2,
	GAME3,
};

int logo();
int title();
int game();
int game2();
int game3();
void text( int num, int x, int y );
void fadeIn();
