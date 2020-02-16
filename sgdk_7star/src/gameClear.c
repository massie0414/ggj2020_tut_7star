#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"

datas gameClear(datas Data) {

	SYS_disableInts();

	VDP_setWindowHPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setWindowVPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setTextPlan(PLAN_A);
	VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

	Data.gm = GAME_CLEAR;
	u16 pad1;

	u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
	char str1[] = "ゲームクリア！";
	draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 13, 8, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str1) * 2;

	u16 palette[64];
	memcpy(&palette[0], Player.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	sprites[0] = SPR_addSprite(
			&NPC,
			136,
			100,
			TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
	);
	SPR_setAnim(sprites[0],1);

	// fade in
	fadeIn( palette );

	// VDP process done, we can re enable interrupts
	SYS_enableInts();

	while(1)
	{
		pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
		if ( pad1 & BUTTON_START ) { // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
			Data.gm = TITLE;
			break;
		}

		SPR_update();
		VDP_waitVSync();
	}

	return Data;
}


