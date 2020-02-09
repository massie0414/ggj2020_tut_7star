#include <genesis.h>
#include "resource.h"
#include "resource_game.h"
#include "main.h"
#include "draw_sjis.h"
#include "game.h"
const int WHAIT2 = 180;

datas afterDay(datas Data) {

    // disable interrupt when accessing VDP
    SYS_disableInts();

    Data.gm = AFTERDAY;

    u16 pad1;

    int count = 0;

	u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
	text(Data.date,15,10);
	char str1[] = "“ú–ÚI—¹";
	draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 20, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str1) * 2;
	text(Data.money,20,20);
	char str2[] = "¡“ú‚Ì‰Ò‚¬";
	draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 20, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str2) * 2;

	u16 palette[64];
	memcpy(&palette[0], Player.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	// fade in
	fadeIn( palette );

		// VDP process done, we can re enable interrupts
		SYS_enableInts();

    	    while(1)
    	    {
    	    	count++;

    	    	        pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
    	    	        if (pad1 & BUTTON_START || count > WHAIT2) {
    	    	            Data.gm = DAY;

    	    	            VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE); // @suppress("Symbol is not resolved")
    	                    VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
    	                    VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")

    	                    Data.date ++;

	    	            break;
    	    	        }
    	        VDP_waitVSync();
    	    }
    return Data;
}

