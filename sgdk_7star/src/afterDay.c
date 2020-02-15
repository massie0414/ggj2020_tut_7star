#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"

const int WHAIT2 = 180;

datas afterDay(datas Data) {

    // disable interrupt when accessing VDP
    SYS_disableInts();

	VDP_setWindowHPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setWindowVPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setTextPlan(PLAN_A);
	VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

    Data.gm = AFTERDAY;

    u16 pad1;

    int count = 0;

	u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
//	text(Data.date,15,10);

	char *str1;

	switch ( Data.date ) {
	case 1:
		str1 = "‚P“ú–ÚI—¹";
		break;
	case 2:
		str1 = "‚Q“ú–ÚI—¹";
		break;
	case 3:
		str1 = "‚R“ú–ÚI—¹";
		break;
	case 4:
		str1 = "‚S“ú–ÚI—¹";
		break;
	case 5:
		str1 = "‚T“ú–ÚI—¹";
		break;
	case 6:
		str1 = "‚U“ú–ÚI—¹";
		break;
	case 7:
		str1 = "ÅI“úI—¹";
		break;
	}

	draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 14, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str1) * 2;

	char str2[] = "¡“ú‚Ì‰Ò‚¬";
	draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 16, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str2) * 2;

//	text(Data.money,20,20);

	char texts[10][3] = {"‚O", "‚P", "‚Q", "‚R", "‚S", "‚T", "‚U", "‚V", "‚W", "‚X" };
	draw_sjis_text(PLAN_A, texts[Data.addMoney/ 1 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 24, 18, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(texts[Data.addMoney/ 1 % 10]) * 2;
	if ( Data.addMoney >= 10 ) {
		draw_sjis_text(PLAN_A, texts[Data.addMoney/ 10 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 18, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.addMoney/ 10 % 10]) * 2;
	}
	if ( Data.addMoney >= 100 ) {
		draw_sjis_text(PLAN_A, texts[Data.addMoney/ 100 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 20, 18, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.addMoney/ 100 % 10]) * 2;
	}
	if ( Data.addMoney >= 1000 ) {
		draw_sjis_text(PLAN_A, texts[Data.addMoney/ 1000 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 18, 18, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.addMoney/ 1000 % 10]) * 2;
	}
	if ( Data.addMoney >= 10000 ) {
		draw_sjis_text(PLAN_A, texts[Data.addMoney/ 10000 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 16, 18, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.addMoney/ 10000 % 10]) * 2;
	}

	char str3[] = "‰~";
	draw_sjis_text(PLAN_A, str3, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 26, 18, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str3) * 2;

	char str4[] = "Ø‹à•ÔÏ‚Ü‚Å";
	draw_sjis_text(PLAN_A, str4, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 20, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str4) * 2;

	char str5[] = "‚ ‚Æ";
	draw_sjis_text(PLAN_A, str5, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 22, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str5) * 2;

	draw_sjis_text(PLAN_A, texts[Data.money/ 1 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 24, 22, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(texts[Data.money/ 1 % 10]) * 2;
	if ( Data.money >= 10 ) {
		draw_sjis_text(PLAN_A, texts[Data.money/ 10 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 22, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.money/ 10 % 10]) * 2;
	}
	if ( Data.money >= 100 ) {
		draw_sjis_text(PLAN_A, texts[Data.money/ 100 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 20, 22, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.money/ 100 % 10]) * 2;
	}
	if ( Data.money >= 1000 ) {
		draw_sjis_text(PLAN_A, texts[Data.money/ 1000 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 18, 22, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.money/ 1000 % 10]) * 2;
	}
	if ( Data.money >= 10000 ) {
		draw_sjis_text(PLAN_A, texts[Data.money/ 10000 % 10], TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 16, 22, 0); // @suppress("Symbol is not resolved")
		pattern +=  strlen(texts[Data.money/ 10000 % 10]) * 2;
	}

	char str6[] = "‰~";
	draw_sjis_text(PLAN_A, str6, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 26, 22, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str6) * 2;

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
		if ( ( pad1 & BUTTON_START ) // @suppress("Symbol is not resolved")
		 || count > WHAIT2
		) {
			Data.gm = DAY;

			fadeOut();

			VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
			VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")

			Data.date ++;

			break;
		}

		VDP_waitVSync();
	}

	// ¡“ú‚Ì‰Ò‚¬‚ğ‚¢‚Á‚½‚ñƒŠƒZƒbƒg
	Data.addMoney = 0;

    return Data;
}

