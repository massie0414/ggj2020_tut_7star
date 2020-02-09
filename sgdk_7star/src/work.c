#include <genesis.h>
#include "resource.h"
#include "resource_game.h"
#include "main.h"
#include "draw_sjis.h"
#include "game.h"

datas work(datas Data) {
	int y=10;
	int x=0;
	u16 pad1,pad0;
    // disable interrupt when accessing VDP
    SYS_disableInts();

    //enum game_mode gm;
    Data.gm = WORK;

    u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")
    char str1[] = "������";
    draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 0, 5, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 2;
    char str2[] = "�n���}�[";
    draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 10, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str1) * 4;
    char str3[] = "�o�P�c";
    draw_sjis_text(PLAN_A, str3, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 15, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;
    char str4[] = "���e";
    draw_sjis_text(PLAN_A, str4, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 20, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str2) * 2;
    char str5[] = "�m�R�M��";
    draw_sjis_text(PLAN_A, str5, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 25, 0);
    pattern +=  strlen(str2) * 2;

    char str6[] = "���A�C�e��";
    draw_sjis_text(PLAN_A, str6, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 5, 0);
    pattern +=  strlen(str2) * 4;
    char str7[] = "�֎q";
    draw_sjis_text(PLAN_A, str7, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 10, 0);
    pattern +=  strlen(str2) * 2;
    char str8[] = "��";
    draw_sjis_text(PLAN_A, str8, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 15, 0);
    pattern +=  strlen(str2) * 2;
    char str9[] = "�^���X";
    draw_sjis_text(PLAN_A, str9, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 20, 0);
    pattern +=  strlen(str2) * 2;
    char str10[] = "�����K";
    draw_sjis_text(PLAN_A, str10, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 25, 0);
    pattern +=  strlen(str2) * 2;

    char str11[] = "�w��";
    draw_sjis_text(PLAN_A, str11, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 10, 0);
    pattern +=  strlen(str2) * 2;
    char str12[] = "����";
    draw_sjis_text(PLAN_A, str12, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 15, 0);
    pattern +=  strlen(str2) * 2;
    char str13[] = "�؂̉�";
    draw_sjis_text(PLAN_A, str13, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 20, 0);
    pattern +=  strlen(str2) * 2;
    char str14[] = "�΂̉�";
    draw_sjis_text(PLAN_A, str14, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 25, 0);
    pattern +=  strlen(str2) * 2;
    char str15[] = "�؂̍��@";
    draw_sjis_text(PLAN_A, str15, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 10, 0);
    pattern +=  strlen(str2) * 2;
    char str16[] = "�΂̍��@";
    draw_sjis_text(PLAN_A, str16, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 15, 0);
    pattern +=  strlen(str2) * 2;
    char str17[] = "����";
    draw_sjis_text(PLAN_A, str17, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 20, 0);
    pattern +=  strlen(str2) * 2;
    char str18[] = "���o����";
    draw_sjis_text(PLAN_A, str18, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 25, 0);
    pattern +=  strlen(str2) * 2;
    char str19[] = "��";
    draw_sjis_text(PLAN_A, str19, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 0, 0, 0);
    pattern +=  strlen(str2) * 2;
    char str20[] = "��";
    draw_sjis_text(PLAN_A, str20, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 7, 0, 0);
    pattern +=  strlen(str2) * 2;
    char str21[] = "�S";
    draw_sjis_text(PLAN_A, str21, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 14, 0, 0);
    pattern +=  strlen(str2) * 2;
    char str22[] = "��";
    draw_sjis_text(PLAN_A, str22, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 21, 0, 0);
    pattern +=  strlen(str2) * 2;

	u16 palette[64];
	memcpy(&palette[0], Player.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	// fade in
	fadeIn( palette );

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    while(1)
    {
    	text(Data.water,0,2);
    	text(Data.wood,7,2);
    	text(Data.metal,14,2);
    	text(Data.stone,21,2);
		pad1 = JOY_readJoypad(JOY_1);
		if (pad0 != pad1) {
					pad0 = pad1;
		if (pad1 & BUTTON_UP) {
			VDP_drawText(" ", x, y);  // �N���A
            y-=5;
        }
		if (pad1 & BUTTON_DOWN) {
			VDP_drawText(" ", x, y);  // �N���A
            y+=5;
        }
			if(pad1 & BUTTON_RIGHT){
				VDP_drawText(" ", x, y);  // �N���A
				x+=10;
			}
			if(pad1 & BUTTON_LEFT){
				VDP_drawText(" ", x, y);  // �N���A
				x-=10;
			}
            if ( y < 10 ) {
                y = 10;
                        }
                        else if ( y > 25 ) {
                            y = 25;
                        }
           if ( x < 0 ) {
            	x = 0;
						}
						else if( x > 30 ) {
							x = 30;
						}
           if (pad1 & BUTTON_START){
            if((x==0 && y==10) && (Data.wood>=10 && Data.stone>=10)&& Data.hammer<1 ){//�n���}�[
           		Data.wood-=10;
           		Data.stone-=10;
           		Data.hammer+=1;
           	}
           	else if((x==0 && y==15)&& Data.wood>=20 && Data.bucket<1){//�o�P�c
           		Data.wood -=20;
           		Data.bucket+=1;
           	}
           	else if((x==0 && y==20) && (Data.wood>=15 && Data.stone>=15)&& Data.bflag<1){//���e
           		Data.wood-=15;
           		Data.stone-=15;
           		Data.bomb+=3;
           		Data.bflag+=1;
           	}
           	else if((x==0 && y==25) && (Data.wood>=10 && Data.stone>=10)&& Data.saw<1){//�m�R�M��
           		Data.wood-=10;
           		Data.stone-=10;
           		Data.saw+=1;
           	}
				if((x==10 && y==10) && Data.wood>=5){//�֎q
					Data.wood-=5;
					Data.chair+=1;
				}
				else if((x==10 && y==15)&&Data.wood>=10 ){//��
					Data.wood-=10;
					Data.desk+=1;
				}
				else if((x==10 && y==20)&& (Data.wood>=5 && Data.metal>=2)){//�^���X
					Data.wood-=5;
					Data.metal-=2;
					Data.chest+=1;
				}
				else if((x==10 && y==25) && Data.stone>=5){//�����K
					Data.stone-=5;
					Data.brick+=1;
				}
					if((x==20 && y==10)&&Data.metal>=2){//�w��
						Data.metal-=2;
						Data.ring+=1;
					}
					else if((x==20 && y==15) && Data.stone>=10){//����
						Data.stone-=10;
						Data.sculpture+=1;
					}
					else if((x==20 && y==20) && (Data.wood>=20 && Data.metal>=2)){//�؂̉�
						Data.wood-=20;
						Data.metal-=2;
						Data.wHouse+=1;
					}
					else if((x==20 && y==25) && (Data.stone>=20 && Data.metal>=2)){//�΂̉�
						Data.stone-=20;
						Data.metal-=2;
						Data.sHouse+=1;
					}
						if((x==30 && y==10)&&(Data.wood>=20 && Data.metal>=5 && Data.water>=10)){//�؂̍��@
							Data.wood-=20;
							Data.metal-=5;
							Data.water-=10;
							Data.wMansion+=1;
						}
						else if((x==30 && y==15) && (Data.stone>=20 && Data.metal>=5 && Data.water>=10)){//�΂̍��@
							Data.stone-=20;
							Data.metal-=5;
							Data.water-=10;
							Data.sMansion+=1;
						}
						else if((x==30 && y>=20)&& Data.water>=20 ){//����
							Data.water-=20;
							Data.tank+=1;
						}
						else if(x==30 && y==25 ){
							VDP_clearPlan(PLAN_A, TRUE);
							VDP_clearPlan(PLAN_B, TRUE);
							//SPR_end();
							Data.explore_mode=1;
							Data.gm=GAME;
							break;
						}
		      }
		}
	    VDP_drawText(">", x, y);
        VDP_waitVSync();
    }
    return Data;
}
