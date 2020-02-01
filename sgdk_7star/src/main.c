#include <genesis.h>
#include "resource.h"
#include "main.h"

int main() {

    // VDPアクセス時の割り込みを無効にする
    SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();
//  VDP_setScreenWidth256();

//  VDP_setScreenHeight224();

    // すべてのスプライトをクリアし、VDPスプライトの割り当てをリセットします（存在する場合）。
//  VDP_resetSprites();

    // すべてのVDPスプライト割り当てを解放します。
//  VDP_releaseAllSprites();

    // キャッシュされたスプライトリストをVDPに送信します。
//  VDP_updateSprites(MAX_VDP_SPRITE, TRUE);

    // 指定された数のハードウェアVDPスプライトを割り当て、それらをリンクします。
//  VDP_allocateSprites(MAX_VDP_SPRITE);

//  SPR_reset();
//  VDP_setSpriteSize(80,16);
//  VDP_setPlanSize(64,64);

//  VDP_clearPlan(PLAN_A, 0);
//  VDP_clearPlan(PLAN_B, 0);

    // init sprites engine
    /*
    u16 maxSprite = 80;	// 最大スプライト数 0-127(0=40)
    u16 vramSize = 1280;	// VRAMタイル数 0-1406(0=384)
    u16 unpackBufferSize = 1280;	// アンパックタイル数 0-1406(0=256)
    SPR_init(
		maxSprite,
		vramSize,
		unpackBufferSize
	);
	*/

    SPR_init();	// これでいい気がする…。

    // Setup the sprites
    /* BGが壊れる…。デフォルトなら壊れないので、デフォルト以外で使う場合は注意する必要がありそう。
    u16 vramSize = 1024;	// 自動VRAMタイル割り当てのためのVRAM領域のvramSizeサイズ（タイル単位）(0=512)
    u16 unpackBufferSize = 640;	// スプライトタイルセットを展開するためのバッファのサイズ。(0=320)
    SPR_initEx(
    	vramSize,
		unpackBufferSize
	);
	*/

//    VDP_setTextPlan(PLAN_WINDOW);
//    VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

    // init sonic sprite
//    int i = 0;
//    for ( i = 0; i < TEST_SIZE; i++ ) {
//		sprites[i] = SPR_addSprite(
//			&sonic_sprite,
//			i*8,
//			i*8,
//			TILE_ATTR(
//				PAL0, // @suppress("Symbol is not resolved")
//				i,
//				FALSE, // @suppress("Symbol is not resolved")
//				FALSE // @suppress("Symbol is not resolved")
//			)
//		);
//
//	    /* Disable auto tile upload */
//		/*
//	    SPR_setAutoTileUpload(
//	    		sprites[i],
//				FALSE
//		);
//		*/
//    }



    // set all palette to black
    u16 index = 0;	// Color index where to start to write (0-63).
    u16 count = 64;	// Number of color to set.
    VDP_setPaletteColors(
    		index,
			(u16*)palette_black,
			count
	);

    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH1,
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );
    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH2,
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );
    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH3,
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );
    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH4,
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );

    SYS_enableInts();

    enum game_mode gm;
    gm = LOGO;

    while(1) {
        switch ( gm ) {
        case LOGO:
            gm = logo();
            break;
        case TITLE:
            gm = title();
            break;
        case GAME:
            gm = game();
            break;
        case GAME2:
            gm = game2();
            break;
        case GAME3:
            gm = game3();
            break;
        case WORK:
        	gm=work();
        	break;
        }
    }

	return (0);
}
