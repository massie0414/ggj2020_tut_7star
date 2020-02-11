#include <genesis.h>
#include "resource.h"
#include "main.h"


const int WAIT = 20;

datas title(datas Data) {

    // VDPアクセス時の割り込みを無効にする
    SYS_disableInts();

    // start music
    SND_startPlay_4PCM_ENV(
    		BGM_Sub_8,
            sizeof(BGM_Sub_8),
            SOUND_PCM_CH1, // @suppress("Symbol is not resolved")
            FALSE // @suppress("Symbol is not resolved")
    );

    u16 palette[64];

    //enum game_mode gm;
    Data.gm = TITLE;

    u16 pad0;
    u16 pad1;

    int count = 0;
    int y = 18;

    int vdp_b_count = 0;
    int vdp_b_x = 0;
    u16 ind = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
    ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
    ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
    ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
    ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

    VDP_drawImageEx(
        PLAN_A,
        &title_image,
        TILE_ATTR_FULL(PAL1, 0, 0, 0, ind), // @suppress("Symbol is not resolved")
        0,  // x
        1,  // y
        0,
		1
    );

    ind = TILE_USERINDEX; // @suppress("Symbol is not resolved") // @suppress("Symbol is not resolved")
    ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

    // prepare palettes
    memcpy(&palette[0], soradesu_1_image.palette->data, 16 * 2);
    memcpy(&palette[16], title_image.palette->data, 16 * 2);
    memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
    memcpy(&palette[48], title_image.palette->data, 16 * 2);

    // fade in
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE); // @suppress("Symbol is not resolved")

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

	int bg_b_count = 0;
    struct camera Camera;
    Camera.x=0;
    Camera.y=122;

    while(1)
    {
    	bg_b_count += CAMERA_MOVE;

    	if ( bg_b_count >= 64 * 8 ) {
    		ind = VDP_BG( PLAN_B, PAL2, ind, vdp_b_count++, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); // @suppress("Symbol is not resolved")

    		vdp_b_count %= 5;
    		if ( vdp_b_count == 0 ) {
    			ind = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    		}
    		vdp_b_x += 8;
    		vdp_b_x %= 64;
    	    bg_b_count -= 64 * 8;
    	}

    	Camera.x += CAMERA_MOVE;
		VDP_setHorizontalScroll(PLAN_B,-Camera.x >> 3);

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

            if (pad1 & BUTTON_START // @suppress("Suggested parenthesis around expression") // @suppress("Symbol is not resolved")
             && count >= WAIT
            ) {
                if ( y == 18 ) {
                    // ゲームスタート

                	// BGMストップ
                    if (SND_isPlaying_4PCM_ENV(SOUND_PCM_CH1_MSK)){ // @suppress("Symbol is not resolved")
                        SND_stopPlay_4PCM_ENV(SOUND_PCM_CH1); // @suppress("Symbol is not resolved")
                    }

                    VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE); // @suppress("Symbol is not resolved")

                    VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
                    VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
                    Data.gm = INIT;
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

    return Data;
}
