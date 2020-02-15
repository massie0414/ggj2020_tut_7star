#include <genesis.h>

#include "resource.h"
#include "main.h"

s16 goal_in=5000;

struct playerScene
{
	s16 x;
	s16 y;
};

struct sozai
{
	s16 item_id;
	s16 x;
	s16 y;
	char showed;	// �\��
	s16 water;
	s16 stone;
	s16 metal;
	s16 wood;
	s16 HP;
	s16 width;
};

struct irainin
{
	s16 amount;
	s16 item_id;
	s16 reward;
	s16 x;
	s16 y;
};


datas game(datas Data) {

	SYS_disableInts();

	// Window�̈�̒�`
	VDP_setWindowHPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setWindowVPos(FALSE, 5); // @suppress("Symbol is not resolved")
	VDP_setTextPlan(PLAN_WINDOW);
	VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

	struct playerScene PlayerData;
	PlayerData.x=0;
	PlayerData.y=122;
	struct camera Camera;
	Camera.x=0;
	Camera.y=122;

	u16 NPCs[1][5]=
	{
			//�A�C�e��ID,��,��V,   X,   Y
			{        1,  1,100, 400, 124}
	};

	struct sozai Sozais[SOZAI_SUU];
	for(s16 i=0;i<SOZAI_SUU;i++)
	{
		Sozais[i].showed=0;
	}
	s16 next_sozai = SOZAI_SUU;

	Data.gm = GAME;

	u16 palette[128];

	// BGM�Đ�
	SND_startPlay_4PCM_ENV(
		BGM_Sub_8,
		sizeof(BGM_Sub_8),
		SOUND_PCM_CH1,	// @suppress("Symbol is not resolved")
		TRUE 			// @suppress("Symbol is not resolved")
	);

	memcpy(&palette[0], NPC.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	// �s�����A�肩
	if ( Data.explore_mode == 1 ) {
		// �A��
		memcpy(&palette[32], sorayuugata_image.palette->data, 16 * 2);
		memcpy(&palette[48], zimenyuugata_image.palette->data, 16 * 2);
	}

	// �v���C���[
	sprites[0] = SPR_addSprite(&Player, 0, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
	SPR_setPosition(sprites[0], 0 ,0);

	// �w�iB
	int vdp_b_count = 0;
	int vdp_b_x = 0;
	int ind_b[5];
	u16 ind = TILE_USERINDEX; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")
	ind_b[vdp_b_count] = ind; ind = VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++; vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

	// �w�iA
	int vdp_a_count = 0;
	int vdp_a_x = 0;
	int ind_a[5];
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")
	ind_a[vdp_a_count] = ind; ind = VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")

	// �ǉ��w�iB
	VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image );	vdp_b_count++;	vdp_b_count %= 5;	vdp_b_x += 8; vdp_b_x %= 64; // @suppress("Symbol is not resolved")

	// �ǉ��w�iA
	VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image );	vdp_a_count++;	vdp_a_count %= 5;	vdp_a_x += 8; vdp_a_x %= 64; // @suppress("Symbol is not resolved")

    char str19[] = "��";
    draw_sjis_text(PLAN_WINDOW, str19, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind),  3, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str19) * 2;

    char str20[] = "��";
    draw_sjis_text(PLAN_WINDOW, str20, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 10, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str20) * 2;

    char str21[] = "�S";
    draw_sjis_text(PLAN_WINDOW, str21, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 17, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str21) * 2;

    char str22[] = "��";
    draw_sjis_text(PLAN_WINDOW, str22, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 24, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str22) * 2;

    char str23[] = "����";
    draw_sjis_text(PLAN_WINDOW, str23, TILE_ATTR_FULL(PAL0, 0, 0, 0, ind), 31, 0, 0); // @suppress("Symbol is not resolved")
    ind +=  strlen(str23) * 2;

	SYS_enableInts();

	fadeIn( palette );

	int walk_count = 0;
	int fightMode = 0;
	int fightModeTimer = 0;

	int bg_b_count = 0;
	int bg_a_count = 0;

	//�˗��l�֌W
	s16 Irainin_showed=0;
	struct irainin Irainins[1];
	for (s16 i = 0; i < 1; i++ ) {
		Irainins[i].item_id = NPCs[i][0];
		Irainins[i].amount = NPCs[i][1];
		Irainins[i].reward = NPCs[i][2];
		Irainins[i].x = NPCs[i][3];
		Irainins[i].y = NPCs[i][4];
	}
	s16 completedSwitch = 0;

	// �R�C��
//	sprites[7]=SPR_addSprite(
//			&jump_coin,
//			350,
//			0,
//			TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
//	);
	s16 coin_time=0;

	int action = PLAYER_PUNCH;
	int next_x = 0;

	while ( TRUE ) { // @suppress("Symbol is not resolved")
		bg_b_count += CAMERA_MOVE;

		// �w�iB
		if ( bg_b_count >= 64 * 8 ) {
			VDP_BG( PLAN_B, PAL2, ind_b[vdp_b_count], vdp_b_count, vdp_b_x, 0, soradesu_1_image, soradesu_2_image, soradesu_3_image, soradesu_4_image, soradesu_5_image ); // @suppress("Symbol is not resolved")
			vdp_b_count++;
			vdp_b_count %= 5;
			vdp_b_x += 8;
			vdp_b_x %= 64;
			bg_b_count -= 64 * 8;
		}

		// �w�iA
		bg_a_count += CAMERA_MOVE;
		if ( bg_a_count >= 64 ) {
			VDP_BG( PLAN_A, PAL3, ind_a[vdp_a_count], vdp_a_count, vdp_a_x, 0, zimensample_1_image, zimensample_2_image, zimensample_3_image, zimensample_4_image, zimensample_5_image ); // @suppress("Symbol is not resolved")
			vdp_a_count++;
			vdp_a_count %= 5;
			vdp_a_x += 8;
			vdp_a_x %= 64;
			bg_a_count -= 64;
		}

		// �f�ސ�������
		text(Data.water, 5,2);
		text(Data.wood ,12,2);
		text(Data.metal,19,2);
		text(Data.stone,26,2);
		text(Data.money,35,2);

		u16 pad1 = JOY_readJoypad(JOY_1);	// @suppress("Symbol is not resolved")

		if( ( pad1 & BUTTON_A ) && fightMode == 0 ) {	// @suppress("Symbol is not resolved")
			// ���ʉ��i�U���j
			SND_startPlay_4PCM_ENV(
				SE_Punch_8,
				sizeof(SE_Punch_8),
				SOUND_PCM_CH2,	// @suppress("Symbol is not resolved")
				FALSE 			// @suppress("Symbol is not resolved")
			);

			fightMode=1;
			if ( Data.hammer > 0 ) {
				action = PLAYER_HAMMER;
				fightModeTimer=30;
			}
			else if ( Data.bucket > 0 ) {
				action = PLAYER_BUCKET;
				fightModeTimer=25;
			}
			else if ( Data.bomb > 0 ) {
				action = PLAYER_BOMB;
				fightModeTimer=30;
			}
			else if ( Data.saw > 0 ) {
				action = PLAYER_SAW;
				fightModeTimer=30;
			}
			else {
				action = PLAYER_PUNCH;
				fightModeTimer=30;
			}
		}

		// �ړ�
		s16 walkMode = 0;
		if ( pad1 & BUTTON_LEFT ){ // @suppress("Symbol is not resolved")
			PlayerData.x -= 2;
			walkMode = 1;
		}
		if ( pad1 & BUTTON_RIGHT ){ // @suppress("Symbol is not resolved")
			PlayerData.x += 2;
			walkMode = 1;
		}
		if ( pad1 & BUTTON_UP ){	// @suppress("Symbol is not resolved")
			PlayerData.y -= 1;
			walkMode = 1;
		}
		if ( pad1 & BUTTON_DOWN ){ // @suppress("Symbol is not resolved")
			PlayerData.y += 1;
			walkMode = 1;
		}

		//�͂���������
		if ( PlayerData.y > BOTTOM_HEIGHT ) {
			PlayerData.y = BOTTOM_HEIGHT;
		}
		if ( PlayerData.y < TOP_HEIGHT ) {
			PlayerData.y = TOP_HEIGHT;
		}
		if ( PlayerData.x < 0 ) {
			PlayerData.x = 0;
			walkMode = 1;
		}
		if ( PlayerData.x < Camera.x ) {
			PlayerData.x = Camera.x;
			walkMode = 1;
		}
		if ( PlayerData.x > Camera.x + WIDTH - PLAYER_WIDTH ) {
			PlayerData.x = Camera.x + WIDTH - PLAYER_WIDTH;
		}

		if ( walkMode == 1 && fightMode != 1 ) {
			// �����Ă���
			SPR_setAnim(sprites[0], PLAYER_WALK);

			// 30�t���[���ɂP��A������炷
			if ( walk_count == 0 ) {
				// ���ʉ���炵�Ă݂�
				SND_startPlay_4PCM_ENV(
						SE_Footstep_8,
						sizeof(SE_Footstep_8),
						SOUND_PCM_CH3,	// @suppress("Symbol is not resolved")
						FALSE			// @suppress("Symbol is not resolved")
				);
			}
			walk_count++;
			if ( walk_count > 30 ) {
				walk_count = 0;
			}

		}
		else if ( fightMode != 1 && walkMode != 1 ) {
			// �~�܂��Ă���
			SPR_setAnim(sprites[0], PLAYER_WAIT);
			walk_count = 0;
		}
		else if ( fightMode == 1 ) {
			// �U��
			fightModeTimer--;
			SPR_setAnim(sprites[0],action);
			if ( fightModeTimer <= 0 ) {
				fightMode = 0;
			}
		}

		// �J�����̈ړ�
		Camera.x += CAMERA_MOVE;
		VDP_setHorizontalScroll(PLAN_A, -Camera.x);
		VDP_setHorizontalScroll(PLAN_B,-Camera.x >> 3);

		// �J�����̈ړ��ɍ��킹�āA�v���C���[���ړ�����
		SPR_setPosition(
			sprites[0],PlayerData.x - Camera.x,
			PlayerData.y
		);

		// �f��
		for ( s16 i = 0; i < SOZAI_SUU; i++ ) {

			// ����
			if ( Sozais[i].showed == 0 && next_x < WIDTH + Camera.x ) {

				Sozais[i].item_id = (int)random() % 16 + 1;
				Sozais[i].x = WIDTH + Camera.x + (int)random() % 128;
				Sozais[i].y = 150 + (int)random() % 24;

				next_x = Sozais[i].x + Sozais[i].width;

				switch ( Sozais[i].item_id ) {
				case ITEM_ID_KI01:
					// �؂̕c
					sprites[i+1] = SPR_addSprite(&ki01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 1;
					Sozais[i].HP = 15;
					break;
				case ITEM_ID_KI02:
					// �؁i���j
					sprites[i+1] = SPR_addSprite(&ki02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 5;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_KI03:
					// �؁i���j
					sprites[i+1] = SPR_addSprite(&ki03,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 1;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 20;
					Sozais[i].HP = 150;
					break;
				case ITEM_ID_KI04:
					// �؁i��j
					sprites[i+1] = SPR_addSprite(&ki04,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 5;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 50;
					Sozais[i].HP = 300;
					break;
				case ITEM_ID_KINNZANN01:
					// ���R
					sprites[i+1] = SPR_addSprite(&kinnzann01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 30;
					Sozais[i].metal = 15;
					Sozais[i].wood = 30;
					Sozais[i].HP = 100;
					break;
				case ITEM_ID_koori01:
					// �X�i���j
					sprites[i+1] = SPR_addSprite(&koori01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 1;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 10;
					break;
				case ITEM_ID_koori02:
					// �X�i���j
					sprites[i+1] = SPR_addSprite(&koori02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 5;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 30;
					break;
				case ITEM_ID_koori03:
					// �X�i��j
					sprites[i+1] = SPR_addSprite(&koori02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 20;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_KOUMYAKU01:
					// �z���i���j
					sprites[i+1] = SPR_addSprite(&koumyaku01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 5;
					Sozais[i].wood = 0;
					Sozais[i].HP = 150;
					break;
				case ITEM_ID_KOUMYAKU02:
					// �z���i���j
					sprites[i+1] = SPR_addSprite(&koumyaku02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 10;
					Sozais[i].wood = 0;
					Sozais[i].HP = 500;
					break;
				case ITEM_ID_MIZU01:
					// �r�i���j
					sprites[i+1] = SPR_addSprite(&mizu01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 5;
					Sozais[i].stone = 0;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 30;
					break;
				case ITEM_ID_MIZU02:
					// �r�i��j
					sprites[i+1] = SPR_addSprite(&mizu02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 20;
					Sozais[i].stone = 1;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_ROCK01:
					// ��i���j
					sprites[i+1] = SPR_addSprite(&rock01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 5;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 60;
					break;
				case ITEM_ID_ROCK02:
					// ��i���j
					sprites[i+1] = SPR_addSprite(&rock02,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 20;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 150;
					break;
				case ITEM_ID_ROCK03:
					// ��i��j
					sprites[i+1] = SPR_addSprite(&rock03,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 50;
					Sozais[i].metal = 0;
					Sozais[i].wood = 0;
					Sozais[i].HP = 300;
					break;
				case ITEM_ID_TETUKUZU01:
					// �S����
					sprites[i+1] = SPR_addSprite(&tetukuzu01,Sozais[i].x-Camera.x,Sozais[i].y,TILE_ATTR(PAL1, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
					Sozais[i].width = 32;
					Sozais[i].water = 0;
					Sozais[i].stone = 0;
					Sozais[i].metal = 1;
					Sozais[i].wood = 0;
					Sozais[i].HP = 30;
					break;
				}
				Sozais[i].showed = 1;
			}

			if ( Sozais[i].showed == 1 ) {
				// �f�ނ��ړ�����
				SPR_setPosition(
					sprites[i+1],
					(Sozais[i].x-Camera.x) + Sozais[i].HP % 5,	// �_���[�W���󂯂����̗h��
					Sozais[i].y
				);

				if ( fightMode == 1 ) { // @suppress("Symbol is not resolved")
					// �U����

					// �����蔻�� TODO �����Ŕ��肵�������ǂ��C������
					if ( PlayerData.x+24 > Sozais[i].x
					  && PlayerData.x+24 < Sozais[i].x+48
					  && PlayerData.y+48 > Sozais[i].y
					  && PlayerData.y+48 < Sozais[i].y+48
					) {
						// ��������
						Sozais[i].HP -= 1;

						if ( Sozais[i].HP <= 0 ) {
							// ��ꂽ

							// ���ʉ��i�j��j
							SND_startPlay_4PCM_ENV(
									SE_Explosion_8,
									sizeof(SE_Explosion_8),
									SOUND_PCM_CH4, 	// @suppress("Symbol is not resolved")
									FALSE 			// @suppress("Symbol is not resolved")
							);

							Data.water += Sozais[i].water;
							Data.stone += Sozais[i].stone;
							Data.metal += Sozais[i].metal;
							Data.wood  += Sozais[i].wood;

							// �X�v���C�g�̏���
							SPR_releaseSprite(sprites[i+1]);
							Sozais[i].showed = 0;
						}
					}
				}

				// ��ʊO
				if ( Sozais[i].x + Sozais[i].width - Camera.x < 0 && Sozais[i].showed == 1 ) {
					// �X�v���C�g�̏���
					SPR_releaseSprite(sprites[i+1]);
					Sozais[i].showed = 0;
				}
			}
		}

		// �˗��l
		if ( Data.explore_mode == 1 ) {
			// �A��̏��� TODO �s�����˗��l�͂���

			//�˗��l
			if ( Camera.x >= 0 && Irainin_showed != 1 ) {
				sprites[17] = SPR_addSprite(
						&NPC,
						Irainins[Data.date-1].x,
						Irainins[Data.date-1].y,
						TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
				);
				Irainin_showed = 1;
			}
			if ( Irainin_showed == 1 ) {
				SPR_setPosition(
					sprites[17],
					Irainins[Data.date-1].x - Camera.x,	// �J�����ړ����ӎ����邽�߁A���t���[������
					Irainins[Data.date-1].y
				);
			}

			// ��ʊO�ɂ������烊���[�X
			if ( Irainins[Data.date-1].x - Camera.x + PLAYER_WIDTH < 0){
				SPR_releaseSprite(sprites[17]);
			}

			//�v���C���[�̈˗��l�֌W����
			if ( PlayerData.x > Irainins[Data.date-1].x-48
			  && PlayerData.x < Irainins[Data.date-1].x+48
			  && PlayerData.y > Irainins[Data.date-1].y-48
			  && PlayerData.y < Irainins[Data.date-1].y+48
			  && completedSwitch == 0
			) {
				// �˗��l�ƐڐG
				Data.hammer = 1;
				s16 ans = 0;
				switch ( Irainins[Data.date-1].item_id )
				{
					case 0:
						// �֎q
						ans = ( Data.chair >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 1:
						// ��
						ans = ( Data.desk >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 2:
						// ����
						ans = ( Data.sculpture >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 3:
						// ����
						ans = ( Data.tank >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 4:
						// �w��
						ans = ( Data.ring >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 5:
						// �΂̉�
						ans = ( Data.sHouse >= Irainins[Data.date-1].amount? 1:0 );
						break;
					case 6:
						// �؂̍��@
						ans = ( Data.wMansion >= Irainins[Data.date-1].amount? 1:0 );
						break;
				}

				ans = 1;	// TODO �f�o�b�O

				if ( ans == 1 ) {
					// �˗��l�̗~�������̂������Ă���
					Data.hammer -= Irainins[Data.date-1].amount;
					Data.money += Irainins[Data.date-1].reward;
					Data.addMoney += Irainins[Data.date-1].reward;

					// ���ł���A�j���[�V����
					SPR_setAnim(sprites[17],1);

					// ���ʉ��i�R�C���j
					SND_startPlay_4PCM_ENV(
							SE_Explosion_8,
							sizeof(SE_Explosion_8),
							SOUND_PCM_CH4,	// @suppress("Symbol is not resolved")
							FALSE 			// @suppress("Symbol is not resolved")
					);

					// �R�C��
					SPR_setPosition(sprites[18],PlayerData.x,PlayerData.y);
					SPR_setAnim(sprites[18],0);
					coin_time = 30;
				}
				completedSwitch = 1;
			}

			if ( coin_time > 1 ) {
				coin_time--;
			}

			if ( coin_time == 1 ) {
				coin_time--;
				SPR_setPosition(sprites[18],350,0);
			}
		}

		SPR_update();
		VDP_waitVSync();

		// �f�o�b�O�R�}���h
		if ( ( pad1 & BUTTON_START || Camera.x>goal_in ) // @suppress("Suggested parenthesis around expression") // @suppress("Symbol is not resolved")
			&& Data.explore_mode == 1
		){
			Data.gm=AFTERDAY;
			break;
		}
		if ( ( pad1 & BUTTON_START || Camera.x>goal_in ) && Data.explore_mode==0 ){ // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
			Data.gm=WORK;
			break;
		}
	}

    // �㏈��
	VDP_clearPlan(PLAN_A, TRUE); // @suppress("Symbol is not resolved")
	VDP_clearPlan(PLAN_B, TRUE); // @suppress("Symbol is not resolved")
	VDP_setHorizontalScroll(PLAN_B, 0);
	VDP_setVerticalScroll(PLAN_B, 0);
	VDP_setHorizontalScroll(PLAN_A, 0);
	VDP_setVerticalScroll(PLAN_A, 0);

	// �X�v���C�g�̍폜
	s16 i = 0;
	for (i = 0; i < SPRITE_NUM; i++) {
		SPR_releaseSprite(sprites[i]);
	}
	SPR_update();

	fadeOut();

    return Data;
}
