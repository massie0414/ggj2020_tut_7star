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

	// ƒXƒvƒ‰ƒCƒg—Ìˆæ‚ð”ð‚¯‚é
	if ( 900 < ind  && ind < 1100 ) {
		ind = 1100;
	}

	switch ( type ) {
	case 1:
		image = image1;
		break;
	case 2:
		image = image2;
		break;
	case 3:
		image = image3;
		break;
	case 4:
		image = image4;
		break;
	case 5:
		image = image5;
		break;
	}

	VDP_drawImageEx(
			PLAN,
			&image,
			TILE_ATTR_FULL(PAL, FALSE, FALSE, FALSE, ind), // @suppress("Symbol is not resolved")
		//	TILE_ATTR_FULL(PAL, FALSE, FALSE, FALSE, 1),
			tile_x,
			tile_y,
			FALSE, // @suppress("Symbol is not resolved")
			TRUE // @suppress("Symbol is not resolved")
	);
	ind += image.tileset->numTile;

//	if ( ind > 400 && ind < 500 ) {
//		ind = TILE_USERINDEX;
//	}


//	if ( ind > 1350 ) {
//		ind = 500;
//	}

//	text( ind, 0, 2 );

	return ind;
}

