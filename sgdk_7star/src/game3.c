#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"

/**
 * 文字で描画してみる
 */
datas game3(datas Data) {

    // disable interrupt when accessing VDP
    SYS_disableInts();

    //enum game_mode gm;
    Data.gm = GAME3;

    u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    char str1[] = "テスト１";
    draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 4, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 2;

    char str2[] = "テスト２";
    draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 7, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;

    char str3[] = "テスト３";
    draw_sjis_text(PLAN_A, str3, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 10, 0); // @suppress("Symbol is not resolved")


    // fade in
    fadeIn();

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

//    s16 a_x = 0;
//    s16 a_y = 0;
    s16 b_x = 0;
    s16 b_y = 0;
    while(1)
    {
	//	a_x++;
	//	a_y++;
		b_x++;
		b_y++;
	//	VDP_setHorizontalScroll(PLAN_A, a_x);
	//	VDP_setVerticalScroll(PLAN_A, a_y);

		VDP_setHorizontalScroll(PLAN_B, b_x);
		VDP_setVerticalScroll(PLAN_B, b_y);

        VDP_waitVSync();
    }

    return Data;
}
