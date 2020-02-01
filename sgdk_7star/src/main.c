#include <genesis.h>
#include "resource.h"
#include "main.h"

int main() {

    // VDP�A�N�Z�X���̊��荞�݂𖳌��ɂ���
    SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();
//  VDP_setScreenWidth256();

//  VDP_setScreenHeight224();

    // ���ׂẴX�v���C�g���N���A���AVDP�X�v���C�g�̊��蓖�Ă����Z�b�g���܂��i���݂���ꍇ�j�B
//  VDP_resetSprites();

    // ���ׂĂ�VDP�X�v���C�g���蓖�Ă�������܂��B
//  VDP_releaseAllSprites();

    // �L���b�V�����ꂽ�X�v���C�g���X�g��VDP�ɑ��M���܂��B
//  VDP_updateSprites(MAX_VDP_SPRITE, TRUE);

    // �w�肳�ꂽ���̃n�[�h�E�F�AVDP�X�v���C�g�����蓖�āA�����������N���܂��B
//  VDP_allocateSprites(MAX_VDP_SPRITE);

//  SPR_reset();
//  VDP_setSpriteSize(80,16);
//  VDP_setPlanSize(64,64);

//  VDP_clearPlan(PLAN_A, 0);
//  VDP_clearPlan(PLAN_B, 0);

    // init sprites engine
    /*
    u16 maxSprite = 80;	// �ő�X�v���C�g�� 0-127(0=40)
    u16 vramSize = 1280;	// VRAM�^�C���� 0-1406(0=384)
    u16 unpackBufferSize = 1280;	// �A���p�b�N�^�C���� 0-1406(0=256)
    SPR_init(
		maxSprite,
		vramSize,
		unpackBufferSize
	);
	*/

    SPR_init();	// ����ł����C������c�B

    // Setup the sprites
    /* BG������c�B�f�t�H���g�Ȃ���Ȃ��̂ŁA�f�t�H���g�ȊO�Ŏg���ꍇ�͒��ӂ���K�v�����肻���B
    u16 vramSize = 1024;	// ����VRAM�^�C�����蓖�Ă̂��߂�VRAM�̈��vramSize�T�C�Y�i�^�C���P�ʁj(0=512)
    u16 unpackBufferSize = 640;	// �X�v���C�g�^�C���Z�b�g��W�J���邽�߂̃o�b�t�@�̃T�C�Y�B(0=320)
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
