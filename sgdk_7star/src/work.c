#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"
#include "game.h"

int work() {
	int y=10;
	int x=0;
	u16 pad1,pad0;
    // disable interrupt when accessing VDP
    SYS_disableInts();
    enum game_mode gm;
    gm = WORK;
    enum game_item iw,im;
    iw=WATER;
    im=METAL;

    /*enum game_item iwod,isto,imet,iwat;
    iwod=WOOD;
    isto=STONE;
    imet=METAL;
    iwat=WATER;*/

    u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    char str1[] = "★道具";
    draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 0, 5, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 2;
    char str2[] = "ハンマー";
    draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 10, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 4;
    char str3[] = "バケツ";
    draw_sjis_text(PLAN_A, str3, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 15, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;
    char str4[] = "爆弾";
    draw_sjis_text(PLAN_A, str4, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 20, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;
    char str5[] = "ノコギリ";
    draw_sjis_text(PLAN_A, str5, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 25, 0);
    pattern +=  strlen(str2) * 2;

    char str6[] = "★アイテム";
    draw_sjis_text(PLAN_A, str6, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 5, 0);
    pattern +=  strlen(str2) * 4;
    char str7[] = "椅子";
    draw_sjis_text(PLAN_A, str7, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 10, 0);
    pattern +=  strlen(str2) * 2;
    char str8[] = "机";
    draw_sjis_text(PLAN_A, str8, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 15, 0);
    pattern +=  strlen(str2) * 2;
    char str9[] = "タンス";
    draw_sjis_text(PLAN_A, str9, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 20, 0);
    pattern +=  strlen(str2) * 2;
    char str10[] = "レンガ";
    draw_sjis_text(PLAN_A, str10, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 25, 0);
    pattern +=  strlen(str2) * 2;

    char str11[] = "指輪";
    draw_sjis_text(PLAN_A, str11, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 10, 0);
    pattern +=  strlen(str2) * 2;
    char str12[] = "彫刻";
    draw_sjis_text(PLAN_A, str12, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 15, 0);
    pattern +=  strlen(str2) * 2;
    char str13[] = "木の家";
    draw_sjis_text(PLAN_A, str13, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 20, 0);
    pattern +=  strlen(str2) * 2;
    char str14[] = "石の家";
    draw_sjis_text(PLAN_A, str14, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 25, 0);
    pattern +=  strlen(str2) * 2;

    char str15[] = "木の豪邸";
    draw_sjis_text(PLAN_A, str15, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 10, 0);
    pattern +=  strlen(str2) * 2;
    char str16[] = "石の豪邸";
    draw_sjis_text(PLAN_A, str16, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 15, 0);
    pattern +=  strlen(str2) * 2;
    char str17[] = "水槽";
    draw_sjis_text(PLAN_A, str17, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 20, 0);
    pattern +=  strlen(str2) * 2;
    char str18[] = "★出口→";
    draw_sjis_text(PLAN_A, str18, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 25, 0);
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
		if (pad1 & BUTTON_UP) {
			VDP_drawText(" ", x, y);  // クリア
            y-=5;
        }
		if (pad1 & BUTTON_DOWN) {
			VDP_drawText(" ", x, y);  // クリア
            y+=5;
        }
			if(pad1 & BUTTON_RIGHT){
				VDP_drawText(" ", x, y);  // クリア
				x+=10;
			}
			if(pad1 & BUTTON_LEFT){
				VDP_drawText(" ", x, y);  // クリア
				x-=10;
			}
            if ( y < 10 ) {
                y = 10;
                        }
                        else if ( y > 25 ) {
                            y = 25;
                        }
           if ( x < 0 ) {
            	x = 0;
						}
						else if( x > 30 ) {
							x = 30;
						}
           if (pad1 & BUTTON_START){
            if(x==0 && y==10){
           	}
           	else if(x==0 && y==15 ){

           	}
           	else if(x==0 && y==20 ){

           	}
           	else if(x==0 && y==25 ){

           	}
				if(x==10 && y==10 ){

				}
				else if(x==10 && y==15 ){

				}
				else if(x==10 && y==20 ){

				}
				else if(x==10 && y==25 ){

				}
					if(x==20 && y==10 ){

					}
					else if(x==20 && y==15 ){

					}
					else if(x==20 && y==20 ){

					}
					else if(x==20 && y==25 ){
					}
						if(x==30 && y==10 ){

						}
						else if(x==30 && y==15 ){

						}
						else if(x==30 && y==20 ){

						}
						else if(x==30 && y==25 ){
							VDP_clearPlan(PLAN_A, TRUE);
							VDP_clearPlan(PLAN_B, TRUE);
							gm=GAME;
							break;
						}
		      }
		}
	    VDP_drawText(">", x, y);
        VDP_waitVSync();
    }
    return gm;
}
