#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"
#include "game.h"

int work() {
	int y=10;
	int x=0;
	u16 pad1,pad0;
    // disable interrupt when accessing VDP
    SYS_disableInts();

    enum game_mode gm;
    gm = WORK;

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

    // fade in
    fadeIn();

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    while(1)
    {
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
            if((x==0 && y==10) && (stone>=10 && water>=10)&& hammer<1 ){//�n���}�[
           		stone-=10;
           		water-=10;
           		hammer+=1;
           	}
           	else if((x==0 && y==15)&& wood>=20 && bucket<1){//�o�P�c
           		wood -=20;
           		bucket+=1;
           	}
           	else if((x==0 && y==20) && (wood>=15 && stone>=15)&& bflag<1){//���e
           		wood-=15;
           		stone-=15;
           		bomb+=3;
           		bflag+=1;
           	}
           	else if((x==0 && y==25) && (wood>=10 && stone>=10)&& saw<1){//�m�R�M��
           		wood-=10;
           		stone-=10;
           		saw+=1;
           	}
				if((x==10 && y==10) && wood>=5){//�֎q
					wood-=5;
					chair+=1;
				}
				else if((x==10 && y==15)&&wood>=10 ){//��
					wood-=10;
					desk+=1;
				}
				else if((x==10 && y==20)&& (wood>=5 && metal>=2)){//�^���X
					wood-=5;
					metal-=2;
					chest+=1;
				}
				else if((x==10 && y==25) && stone>=5){//�����K
					stone-=5;
					brick+=1;
				}
					if((x==20 && y==10)&&metal>=2){//�w��
						metal-=2;
						ring+=1;
					}
					else if((x==20 && y==15) && stone>=10){//����
						stone-=10;
						sculpture+=1;
					}
					else if((x==20 && y==20) && (wood>=20 && metal>=2)){//�؂̉�
						wood-=20;
						metal-=2;
						wHouse+=1;
					}
					else if((x==20 && y==25) && (stone>=20 && metal>=2)){//�΂̉�
						stone-=20;
						metal-=2;
						sHouse+=1;
					}
						if((x==30 && y==10)&&(wood>=20 && metal>=5 && water>=10)){//�؂̍��@
							wood-=20;
							metal-=5;
							water-=10;
							wMansion+=1;
						}
						else if((x==30 && y==15) && (stone>=20 && metal>=5 && water>=10)){//�΂̍��@
							stone-=20;
							metal-=5;
							water-=10;
							sMansion+=1;
						}
						else if((x==30 && y>=20)&& water>=20 ){//����
							water-=20;
							tank+=1;
						}
						else if(x==30 && y==25 ){
							VDP_clearPlan(PLAN_A, TRUE);
							VDP_clearPlan(PLAN_B, TRUE);
							gm=GAME;
							break;
						}
		      }
		}
	    VDP_drawText(">", x, y);
        VDP_waitVSync();
    }
    return gm;
}
