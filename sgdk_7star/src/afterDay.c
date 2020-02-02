#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"
#include "game.h"
const int WHAIT2 = 180;

struct datas afterDay(struct datas Data) {

    // disable interrupt when accessing VDP
    SYS_disableInts();

    Data.gm = AFTERDAY;

    u16 pad1;

    int count = 0;

    if(Data.explore_mode==1){
    	u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    	    text(Data.date,15,10);
    	    char str1[] = "“ú–ÚI—¹";
    	    draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 20, 10, 0); // @suppress("Symbol is not resolved")
    	    pattern +=  strlen(str1) * 2;
    	    text(Data.money,20,20);
    	    char str2[] = "¡“ú‚Ì‰Ò‚¬";
    	    draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 20, 0); // @suppress("Symbol is not resolved")
    	    pattern +=  strlen(str2) * 2;

    	    // fade in
    	    fadeIn();

    	    // VDP process done, we can re enable interrupts
    	    SYS_enableInts();

    	    while(1)
    	    {
    	    	count++;

    	    	        pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
    	    	        if (pad1 & BUTTON_START // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
    	    	         || count > WHAIT2
    	    	        ) {
    	    	            Data.gm = GAME;
	    	            break;
    	    	        }
    	        VDP_waitVSync();
    	    }
    }
    return Data;
}

