#include <genesis.h>
#include "resource.h"
#include "resource_game.h"
#include "main.h"

void text( int num, int x, int y ) {
    char texts[10][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    VDP_drawText(texts[ num /      1 % 10 ], x+4, y);
    VDP_drawText(texts[ num /     10 % 10 ], x+3, y);
    VDP_drawText(texts[ num /    100 % 10 ], x+2, y);
    VDP_drawText(texts[ num /   1000 % 10 ], x+1, y);
    VDP_drawText(texts[ num /  10000 % 10 ], x+0, y);
}

void fadeIn( u16 palette[] ) {
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

void fadeOut() {
	u16 fromcol = 0;	// Start color index for the fade operation (0-63).
	u16 tocol = (4 * 16) - 1;	// End color index for the fade operation (0-63 and >= fromcol).
	u16 numframe = 20;
	u8 async = FALSE; // @suppress("Symbol is not resolved")
	VDP_fadeOut(
		fromcol,
		tocol,
		numframe,
		async
	);
}

//”wŒi‚Ì•`‰æ
int VDP_BG(
		VDPPlan PLAN,
		int PAL,
		int ind,
		int type,
		int tile_x,
		int tile_y,
		Image image1,
		Image image2,
		Image image3,
		Image image4,
		Image image5
) {
	Image image;

	switch ( type ) {
	case 0:
		image = image1;
		break;
	case 1:
		image = image2;
		break;
	case 2:
		image = image3;
		break;
	case 3:
		image = image4;
		break;
	case 4:
		image = image5;
		break;
	}

	VDP_drawImageEx(
			PLAN,
			&image,
			TILE_ATTR_FULL(PAL, FALSE, FALSE, FALSE, ind), // @suppress("Symbol is not resolved")
			tile_x,
			tile_y,
			FALSE, // @suppress("Symbol is not resolved")
			TRUE // @suppress("Symbol is not resolved")
	);

	ind += image.tileset->numTile;

	return ind;
}

//s16 playerMoveOn(u16 pad1, s16 *x,s16 *y,s16 cameraX,s16 cameraY)
//{
//	s16 mode=0;
//	if ( pad1 & BUTTON_LEFT ){ // @suppress("Symbol is not resolved")
//		*x-=2;
//		mode=1;
//	}
//	if ( pad1 & BUTTON_RIGHT ){ // @suppress("Symbol is not resolved")
//		*x+=2;
//		mode=1;
//	}
//	if ( pad1 & BUTTON_UP ){	// @suppress("Symbol is not resolved")
//		*y-=1;
//		mode=1;
//	}
//	if ( pad1 & BUTTON_DOWN ){ // @suppress("Symbol is not resolved")
//		*y+=1;
//		mode=1;
//	}
//
//	//‚Í‚¶‚Á‚±ˆ—
//	if ( *y > BOTTOM_HEIGHT ) {
//		*y = BOTTOM_HEIGHT;
//	}
//	if ( *y < TOP_HEIGHT ) {
//		*y = TOP_HEIGHT;
//	}
//	if ( *x < 0 ) {
//		*x=0;
//		mode=1;
//	}
//	if ( *x < cameraX ) {
//		*x = cameraX;
//		mode = 1;
//	}
//	if ( *x > cameraX + 320 - 48 ) {
//		*x = cameraX + 320 - 48;
//	}
//	return mode;
//}
