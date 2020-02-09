#include <genesis.h>
#include "resource.h"
#include "resource_game.h"
#include "main.h"

int main() {
	datas Data;

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
            SOUND_PCM_CH1, // @suppress("Symbol is not resolved")
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );
    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH2, // @suppress("Symbol is not resolved")
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );
    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH3, // @suppress("Symbol is not resolved")
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );
    SND_setVolume_4PCM_ENV(
            SOUND_PCM_CH4, // @suppress("Symbol is not resolved")
            15    // Volume to set : 16 possible level from 0 (minimum) to 15 (maximum).
    );

    SYS_enableInts();

    Data.gm = LOGO;

    while(1) {
        switch ( Data.gm ) {
        case LOGO:
            Data = logo(Data);
            break;
        case TITLE:
        	Data = title(Data);
            break;
        case DAY:
        	Data = day(Data);
        	break;
        case AFTERDAY:
        	Data = afterDay(Data);
        	break;
        case INIT:
        	Data = init(Data);
        	break;
        case GAME:
        	Data = game(Data);
            break;
        case WORK:
        	Data=work(Data);
        	break;
        }
    }

	return (0);
}
