#include <genesis.h>
#include "resource.h"
#include "main.h"

const int WAIT = 20;

int title() {

    // VDPアクセス時の割り込みを無効にする
    SYS_disableInts();

    u16 palette[64];

    enum game_mode gm;
    gm = TITLE;

    u16 pad0;
    u16 pad1;

    int count = 0;
    int y = 18;

    VDP_drawImageEx(
        PLAN_B,
        &title16,
        TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USERINDEX), // @suppress("Symbol is not resolved")
        0,  // x
        1,  // y
        0,
        1
    );

    // prepare palettes
    memcpy(&palette[0], title16.palette->data, 16 * 2);

    // fade in
    VDP_fadeIn(0, (1 * 16) - 1, palette, 20, FALSE); // @suppress("Symbol is not resolved")

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    while(1)
    {
        count++;
        if ( count >= WAIT ) {
            count = WAIT;
        }

        pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
        if (pad0 != pad1) {
            pad0 = pad1;
            if (pad1 & BUTTON_UP) { // @suppress("Symbol is not resolved")
                y--;
            }
            if (pad1 & BUTTON_DOWN) { // @suppress("Symbol is not resolved")
                y++;

            }

            if ( y < 18 ) {
                y = 18;
            }
            else if ( y > 20 ) {
                y = 20;
            }

            if (pad1 & BUTTON_LEFT) { // @suppress("Symbol is not resolved")

            }
            if (pad1 & BUTTON_RIGHT) { // @suppress("Symbol is not resolved")

            }
            if (pad1 & BUTTON_A) { // @suppress("Symbol is not resolved")

            }
            if (pad1 & BUTTON_B) { // @suppress("Symbol is not resolved")

            }
            if (pad1 & BUTTON_C) { // @suppress("Symbol is not resolved")

            }
            if (pad1 & BUTTON_START // @suppress("Suggested parenthesis around expression") // @suppress("Symbol is not resolved")
             && count >= WAIT
            ) {
                if ( y == 18 ) {
                    // ゲームスタート
                //  SND_setPCM_XGM(64, se1_14k, sizeof(se1_14k));
                //  SND_startPlayPCM_XGM(64, 10, SOUND_PCM_CH1);

                    VDP_fadeOut(0, (1 * 16) - 1, 20, FALSE); // @suppress("Symbol is not resolved")

                    VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
                    VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
                    gm = GAME;
                    break;
                }
                else if ( y == 19 ) {

                }
                else if ( y == 20 ) {

                }
            }
        }

        // カーソル
        VDP_drawText(" ", 12, 18);  // クリア
        VDP_drawText(" ", 12, 19);  // クリア
        VDP_drawText(" ", 12, 20);  // クリア
        VDP_drawText(">", 12, y);

        VDP_drawText("GAME START ", 13, 18);
        VDP_drawText("HOW TO PLAY", 13, 19);
        VDP_drawText("CREDIT"     , 13, 20);

        VDP_drawText("(C)2020 TEAM NAME", 10, 22);

        VDP_waitVSync();
    }
    return gm;
}
