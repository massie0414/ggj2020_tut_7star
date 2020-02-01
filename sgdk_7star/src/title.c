#include <genesis.h>
#include "resource.h"
#include "resource_game.h"
#include "main.h"

const int WAIT = 20;

int title() {

    // VDPアクセス時の割り込みを無効にする
    SYS_disableInts();

    // start music
    SND_startPlay_4PCM_ENV(
    		BGM_Sub_8,
            sizeof(BGM_Sub_8),
            SOUND_PCM_CH1,
            FALSE
    );

    u16 palette[64];

    enum game_mode gm;
    gm = TITLE;

    u16 pad0;
    u16 pad1;

    int count = 0;
    int y = 18;

    u16 ind = TILE_USERINDEX;
    VDP_drawImageEx(
        PLAN_B,
        &soradesu_image,
        TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), // @suppress("Symbol is not resolved")
        0,  // x
        1,  // y
        0,
		1
    );
    ind += soradesu_image.tileset->numTile;
    VDP_drawImageEx(
        PLAN_A,
        &title_image,
        TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), // @suppress("Symbol is not resolved")
        0,  // x
        1,  // y
        0,
		1
    );
    ind += title_image.tileset->numTile;

    // prepare palettes
    memcpy(&palette[0], soradesu_image.palette->data, 16 * 2);
    memcpy(&palette[16], title_image.palette->data, 16 * 2);

    // fade in
    VDP_fadeIn(0, (2 * 16) - 1, palette, 20, FALSE); // @suppress("Symbol is not resolved")

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
                // 効果音を鳴らしてみる
                SND_startPlay_4PCM_ENV(
                		SE_Explosion_8,
                        sizeof(SE_Explosion_8),
                        SOUND_PCM_CH2,
                        FALSE
                );
            }
            if (pad1 & BUTTON_B) { // @suppress("Symbol is not resolved")
                // 効果音を鳴らしてみる
                SND_startPlay_4PCM_ENV(
                		SE_Footstep_8,
                        sizeof(SE_Footstep_8),
                        SOUND_PCM_CH3,
                        FALSE
                );
            }
            if (pad1 & BUTTON_C) { // @suppress("Symbol is not resolved")
                // 効果音を鳴らしてみる
                SND_startPlay_4PCM_ENV(
                		SE_Footsteps_cave_8,
                        sizeof(SE_Footsteps_cave_8),
                        SOUND_PCM_CH4,
                        FALSE
                );
            }
            if (pad1 & BUTTON_START // @suppress("Suggested parenthesis around expression") // @suppress("Symbol is not resolved")
             && count >= WAIT
            ) {
                if ( y == 18 ) {
                    // ゲームスタート

                	// BGMストップ
                    if (SND_isPlaying_4PCM_ENV(SOUND_PCM_CH1_MSK)){
                        SND_stopPlay_4PCM_ENV(SOUND_PCM_CH1);
                    }

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
        VDP_drawText(" ", 22, 18);  // クリア
        VDP_drawText(" ", 22, 19);  // クリア
        VDP_drawText(" ", 22, 20);  // クリア
        VDP_drawText(">", 22, y);

        VDP_drawText("GAME START ", 23, 18);
        VDP_drawText("HOW TO PLAY", 23, 19);
        VDP_drawText("CREDIT"     , 23, 20);

        VDP_drawText("(C)2020 7STAR", 22, 22);

        VDP_waitVSync();
    }

    return gm;
}
