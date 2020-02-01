#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"
#include "game.h"

/**
 * 文字で描画してみる
 */
int work() {
	int y=10;

	u16 pad1,pad0;
    // disable interrupt when accessing VDP
    SYS_disableInts();

    enum game_mode gm;
    gm = WORK;
    enum game_item iw,im;
    iw=WATER;
    im=METAL;


    u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    char str1[] = "道具";
    draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 5, 5, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 2;
    char str2[] = "ハンマー";
    draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 5, 10, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 4;
    char str3[] = "バケツ";
    draw_sjis_text(PLAN_A, str3, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 5, 15, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;
    char str4[] = "爆弾";
    draw_sjis_text(PLAN_A, str4, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 5, 20, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;
    char str5[] = "ノコギリ";
    draw_sjis_text(PLAN_A, str5, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 5, 25, 0);
    pattern +=  strlen(str2) * 2;
    char str6[] = "アイテム";
    draw_sjis_text(PLAN_A, str6, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 20, 5, 0);
    pattern +=  strlen(str2) * 2;
    // fade in
    fadeIn();

    // VDP process done, we can re enable interrupts
    SYS_enableInts();


    while(1)
    {
		pad1 = JOY_readJoypad(JOY_1);
		if (pad0 != pad1) {
					pad0 = pad1;
		if (pad1 & BUTTON_UP) { // @suppress("Symbol is not resolved")
		                y-=5;
		            }
		            if (pad1 & BUTTON_DOWN) { // @suppress("Symbol is not resolved")
		                y+=5;
		            }
		            if ( y < 10 ) {
                        y = 10;
		                        }
		                        else if ( y > 25 ) {
		                            y = 25;
		                        }
		            if (pad1 & BUTTON_START){
		            	if(y==10 && iw==9){
		            		iw -=3;
		            		text(iw, 0, 26);
		            	}
		            	else if(y==15){

		            	}
		            	else if(y==20){

		            	}
		            	else if(y==25){

		            	}
		            }
		}
	    VDP_drawText(" ", 2, 10);  // クリア
	    VDP_drawText(" ", 2, 15);  // クリア
	    VDP_drawText(" ", 2, 20);  // クリア
	    VDP_drawText(" ", 2, 25);  // クリア
	    VDP_drawText(">", 2, y);
        VDP_waitVSync();
    }

    return gm;
}
