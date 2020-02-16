#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"

const int WHAIT = 180;

datas day(datas Data) {

	SYS_disableInts();

	VDP_setWindowHPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setWindowVPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setTextPlan(PLAN_A);
	VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

	Data.gm = DAY;
	Data.explore_mode=0;
	u16 pad1;

	int count = 0;

	u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
//	text(Data.date,15,10);

	char *str1;

	switch ( Data.date ) {
	case 1:
		str1 = "‚P“ú–Ú";
		break;
	case 2:
		str1 = "‚Q“ú–Ú";
		break;
	case 3:
		str1 = "‚R“ú–Ú";
		break;
	case 4:
		str1 = "‚S“ú–Ú";
		break;
	case 5:
		str1 = "‚T“ú–Ú";
		break;
	case 6:
		str1 = "‚U“ú–Ú";
		break;
	case 7:
		str1 = "ÅI“ú";
		break;
	}

	draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 17, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str1) * 2;

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
		if (pad1 & BUTTON_START // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
		|| count > WHAIT
		) {
			Data.gm = GAME;
			break;
		}
		VDP_waitVSync();
	}

    return Data;
}


