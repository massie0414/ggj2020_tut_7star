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
	char name[64];
	s16 x;
	s16 y;
	char showed;	// �\��
	char broke;
	s16 genso[4];
	s16 HP;
};

struct irainin
{
	s16 amount;
	s16 item_id;
	char name[64];
	s16 reward;
	s16 x;
	s16 y;
};


datas game(datas Data) {

	SYS_disableInts();

	struct playerScene PlayerData;
	PlayerData.x=0;
	PlayerData.y=122;
	struct camera Camera;
	Camera.x=0;
	Camera.y=122;
	u16 tests[SOZAI_SUU][9]=
	{
			//  x,   y,showed,broke,genso1,genso2,genso3,genso4,HP
			{ 400, 180, FALSE,FALSE,     1,     2,     4,     8, 60 } // @suppress("Symbol is not resolved")
	};
	char tests_name[SOZAI_SUU][64]=
	{
			"�Ă���Ȃ���"
	};
	u16 NPCs[7][5]=
	{
			//�A�C�e��ID/��/��V/X/Y
			{1,1,100, 400, 124}
	};
	char NPCsItemName[7][64]=
	{
			"�n���}�["
	};

	struct sozai Sozais[SOZAI_SUU];
	for(s16 i;i<SOZAI_SUU;i++)
	{
		for(s16 h;h<64;h++)
		{
			Sozais[i].name[h]=tests_name[i][h];
		}
		Sozais[i].x = tests[i][0];
		Sozais[i].y = tests[i][1];
		Sozais[i].showed=tests[i][2];
		Sozais[i].broke=tests[i][3];
		Sozais[i].genso[0]=tests[i][4];
		Sozais[i].genso[1]=tests[i][5];
		Sozais[i].genso[2]=tests[i][6];
		Sozais[i].genso[3]=tests[i][7];
		Sozais[i].HP=tests[i][8];
	}

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

	// �v���C���[
	sprites[0] = SPR_addSprite(&Player, 0, 0, TILE_ATTR(PAL0, TRUE, FALSE, FALSE)); // @suppress("Symbol is not resolved")
	SPR_setPosition(sprites[0], 0 ,0);

	// ��
	Sozais[0].showed =1;
	sprites[3] = SPR_addSprite(
			&rock01,
			Sozais[0].x-Camera.x,
			Sozais[0].y,
			TILE_ATTR(PAL1, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
	);

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
		for ( s16 h = 0; h < 64; h++ ) {
			Irainins[i].name[h] = NPCsItemName[i][h];
		}
		Irainins[i].item_id = NPCs[i][0];
		Irainins[i].amount = NPCs[i][1];
		Irainins[i].reward = NPCs[i][2];
		Irainins[i].x = NPCs[i][3];
		Irainins[i].y = NPCs[i][4];
	}
	s16 completedSwitch = 0;

	// �R�C��
	sprites[7]=SPR_addSprite(
			&jump_coin,
			350,
			0,
			TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
	);
	s16 coin_time=0;

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

		u16 pad1 = JOY_readJoypad(JOY_1);	// @suppress("Symbol is not resolved")

		if( ( pad1 & BUTTON_A ) && fightMode == 0 ) {	// @suppress("Symbol is not resolved")
			// ���ʉ��i�U���j
			SND_startPlay_4PCM_ENV(
				Punch_wav,
				sizeof(Punch_wav),
				SOUND_PCM_CH2,	// @suppress("Symbol is not resolved")
				FALSE 			// @suppress("Symbol is not resolved")
			);

			fightMode=1;
			fightModeTimer=30;
			if ( Data.hammer > 0 ) {
				SPR_setAnim(sprites[0],3);
			}
			else {
				SPR_setAnim(sprites[0],2);
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
			SPR_setAnim(sprites[0], 1);

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
			SPR_setAnim(sprites[0], 0);
			walk_count = 0;
		}
		else if ( fightMode == 1 ) {
			// �U��
			fightModeTimer--;
			SPR_setAnim(sprites[0],2);
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
			if ( Sozais[i].broke == 1 ) {
				// ���Ă����珈�����Ȃ�
				continue;
			}

			if ( Sozais[i].showed == 1 ) {
				// �f�ނ��ړ�����
				SPR_setPosition(
					sprites[i+3],
					(Sozais[i].x-Camera.x),
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

							Data.water=Sozais[i].genso[0];
							Data.stone=Sozais[i].genso[1];
							Data.metal=Sozais[i].genso[2];
							Data.wood=Sozais[i].genso[3];

							// �X�v���C�g�̏���
							SPR_releaseSprite(sprites[i+3]);
							Sozais[i].broke=1;
						}
					}
				}

				// ��ʊO
				if ( Sozais[i].x < Camera.x && Sozais[i].broke == 0 ) {
					// �X�v���C�g�̏���
					SPR_releaseSprite(sprites[i+3]);
					Sozais[i].broke=1;
				}
			}
		}

		// �˗��l
		if ( Data.explore_mode == 1 ) {
			// �A��̏��� TODO �s�����˗��l�͂���

			//�˗��l
			if ( Camera.x >= 0 && Irainin_showed != 1 ) {
				sprites[6] = SPR_addSprite(
						&NPC,
						Irainins[Data.date-1].x,
						Irainins[Data.date-1].y,
						TILE_ATTR(PAL0, TRUE, FALSE, FALSE) // @suppress("Symbol is not resolved")
				);
				Irainin_showed = 1;
			}
			if ( Irainin_showed == 1 ) {
				SPR_setPosition(
					sprites[6],
					Irainins[Data.date-1].x - Camera.x,	// �J�����ړ����ӎ����邽�߁A���t���[������
					Irainins[Data.date-1].y
				);
			}

			// ��ʊO�ɂ������烊���[�X
			if ( Irainins[Data.date-1].x - Camera.x + PLAYER_WIDTH < 0){
				SPR_releaseSprite(sprites[6]);
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
					SPR_setAnim(sprites[6],1);

					// ���ʉ��i�R�C���j
					SND_startPlay_4PCM_ENV(
							SE_Explosion_8,
							sizeof(SE_Explosion_8),
							SOUND_PCM_CH4,	// @suppress("Symbol is not resolved")
							FALSE 			// @suppress("Symbol is not resolved")
					);

					// �R�C��
					SPR_setPosition(sprites[7],PlayerData.x,PlayerData.y);
					SPR_setAnim(sprites[7],0);
					coin_time = 30;
				}
				completedSwitch = 1;
			}

			if ( coin_time > 1 ) {
				coin_time--;
			}

			if ( coin_time == 1 ) {
				coin_time--;
				SPR_setPosition(sprites[7],350,0);
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
