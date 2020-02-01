#include <genesis.h>
#include "resource.h"
#include "main.h"

int main() {

    // VDPアクセス時の割り込みを無効にする
    SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();
    VDP_setPlanSize(64,32);
    SPR_init();

//    VDP_setWindowHPos(FALSE, 0);
//    VDP_setWindowVPos(FALSE, 6);
//    VDP_setTextPlan(PLAN_WINDOW);
//    VDP_setTextPriority(TRUE);

    // BGMの初期化
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
            SOUND_PCM_CH4, // @suppress("Symbol is not resolved")
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
