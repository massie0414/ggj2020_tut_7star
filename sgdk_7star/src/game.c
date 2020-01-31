#include <genesis.h>
#include "resource.h"
#include "main.h"

int game() {

    // disable interrupt when accessing VDP
    SYS_disableInts();

    enum game_mode gm;
    gm = GAME;

    u16 palette[64];

    int i = 0;
    for ( i = 0; i < TEST_SIZE; i++ ) {
    	SPR_setAnim(sprites[i], i % 8);
    }
//  SPR_update();

    // load background
    u16 ind = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    VDP_drawImageEx(
    		PLAN_B,
			&bgb,
			TILE_ATTR_FULL(
					PAL1, // @suppress("Symbol is not resolved")
					FALSE, // @suppress("Symbol is not resolved")
					FALSE, // @suppress("Symbol is not resolved")
					FALSE, // @suppress("Symbol is not resolved")
					ind
					),
			0,
			0,
			FALSE, // @suppress("Symbol is not resolved")
			TRUE // @suppress("Symbol is not resolved")
	);
    ind += bgb.tileset->numTile;
    VDP_drawImageEx(
    		PLAN_A,
			&bga,
			TILE_ATTR_FULL(
					PAL2, // @suppress("Symbol is not resolved")
					FALSE, // @suppress("Symbol is not resolved")
					FALSE, // @suppress("Symbol is not resolved")
					FALSE, // @suppress("Symbol is not resolved")
					ind),
			0,
			0,
			FALSE, // @suppress("Symbol is not resolved")
			TRUE // @suppress("Symbol is not resolved")
	);
    ind += bga.tileset->numTile;

    memcpy(&palette[ 0], sonic_sprite.palette->data, 16 * 2);
    memcpy(&palette[16], bgb.palette->data, 16 * 2);
    memcpy(&palette[32], bga.palette->data, 16 * 2);
    memcpy(&palette[48], sonic_sprite.palette->data, 16 * 2);

    // fade in
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

    // 使用可能なVDPスプライトの数を返します。
    u16 availableSprites = VDP_getAvailableSprites();

    // 現在割り当てられているVDPスプライトの最高のインデックスを計算して返します。
    s16 refreshHighestAllocatedSpriteIndex = VDP_refreshHighestAllocatedSpriteIndex();

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

//  int count = 0;

    s16 x = 10;
    s16 y = 10;

    i = 0;
    s16 a_x = 0;
    s16 b_x = 0;
    s16 a_y = 0;
    s16 b_y = 0;
    while(1)
    {
        text(availableSprites, 0, 26);
        text(refreshHighestAllocatedSpriteIndex, 0, 27);

    //    a_x++;
    //    a_y++;
    //    b_x+=2;
    //    b_y+=2;
        VDP_setHorizontalScroll(PLAN_A, a_x);
        VDP_setHorizontalScroll(PLAN_B, b_x);
        VDP_setVerticalScroll(PLAN_A, a_y);
        VDP_setVerticalScroll(PLAN_B, b_y);


    	/*
    	count++;
    	if ( count > 100 ) {
    		gm = TITLE;

    		for ( i = 0; i < TEST_SIZE; i++ ) {
    			SPR_setAnim(sprites[i], -1);
    		}
    	    SPR_update();

    	    VDP_fadeOut(0, (1 * 16) - 1, 20, FALSE);

    		break;
    	}
    	*/

    //	for ( i = 0; i < TEST_SIZE; i++ ) {
    		x = ( i % 5 ) * 8 * 6;
    		y = ( i / 5 ) * 8 * 6;
			SPR_setPosition(
				sprites[i],
				x,
				y
			);
    //	}

		i++;
		i = i % TEST_SIZE;

        SPR_update();
        VDP_waitVSync();
    }

    return gm;
}
