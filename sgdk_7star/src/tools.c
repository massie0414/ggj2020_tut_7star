#include <genesis.h>
#include "resource.h"
#include "main.h"

void text( int num, int x, int y ) {
    char texts[10][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    VDP_drawText(texts[ num /     1 % 10 ], x+4, y);
    VDP_drawText(texts[ num /    10 % 10 ], x+3, y);
    VDP_drawText(texts[ num /   100 % 10 ], x+2, y);
    VDP_drawText(texts[ num /  1000 % 10 ], x+1, y);
    VDP_drawText(texts[ num / 10000 % 10 ], x+0, y);
}

void fadeIn() {

    u16 palette[64];

    memcpy(&palette[ 0], test2.palette->data, 16 * 2);
    memcpy(&palette[16], bgb.palette->data, 16 * 2);
    memcpy(&palette[32], bga.palette->data, 16 * 2);
    memcpy(&palette[48], sonic_sprite.palette->data, 16 * 2);

    u16 fromcol = 0;
    u16 tocol = (4 * 16) - 1;
    u16 numframe = 20;
    u8 async = FALSE; // @suppress("Symbol is not resolved")
    VDP_fadeIn(
		fromcol,
		tocol,
		palette,
		numframe,
		async
	);
}
