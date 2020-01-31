#include <genesis.h>
#include "resource.h"
#include "main.h"

const int START = 180;

int logo(){

    // VDPアクセス時の割り込みを無効にする
    SYS_disableInts();

    u16 palette[64];

    enum game_mode gm;
    gm = LOGO;

    int count = 0;

    u16 x = 15;
    u16 y = 10;
    u16 loadpal = FALSE; // @suppress("Symbol is not resolved")
    TransferMethod tm = TRUE; // @suppress("Symbol is not resolved")
    VDP_drawImageEx(
        PLAN_B,
        &logo16,
        TILE_ATTR_FULL(
        		PAL0, // @suppress("Symbol is not resolved")
				0,	// Tile priority
				0,	// Vertical flip
				0,	// Horizontal flip
				TILE_USERINDEX	// Tile index // @suppress("Symbol is not resolved")
		),
        x,
        y,
		loadpal,
		tm
    );

    // prepare palettes
    memcpy(&palette[0], logo16.palette->data, 16 * 2);

    // fade in
    VDP_fadeIn(0, (1 * 16) - 1, palette, 20, FALSE); // @suppress("Symbol is not resolved")

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    while(1)
    {
        count++;

        u16 pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
        if (pad1 & BUTTON_START // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
         || count > START
        ) {
            gm = TITLE;

            // 効果音
        	SND_startPlayPCM_XGM(64, 1, SOUND_PCM_CH2); // @suppress("Symbol is not resolved")

            VDP_fadeOut(0, (1 * 16) - 1, 20, FALSE); // @suppress("Symbol is not resolved")

            VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
            VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
            break;
        }
        VDP_waitVSync();
    }
    return gm;
}
