#include <genesis.h>
#include "resource.h"
#include "main.h"
#include "draw_sjis.h"

datas work(datas Data) {
	int y=10;
	int x=0;
	u16 pad1,pad0;

	SYS_disableInts();

	// Window領域の定義
	VDP_setWindowHPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setWindowVPos(FALSE, 0); // @suppress("Symbol is not resolved")
	VDP_setTextPlan(PLAN_A);
	VDP_setTextPriority(TRUE); // @suppress("Symbol is not resolved")

	Data.gm = WORK;

	u16 pattern = TILE_USERINDEX; // @suppress("Symbol is not resolved")

	char str1[] = "★道具";
	draw_sjis_text(PLAN_A, str1, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 0, 5, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str1) * 2;

	char str2[] = "ハンマー";
	draw_sjis_text(PLAN_A, str2, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str2) * 2;

	char str3[] = "バケツ";
	draw_sjis_text(PLAN_A, str3, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 15, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str3) * 2;

	char str4[] = "爆弾";
	draw_sjis_text(PLAN_A, str4, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 20, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str4) * 2;

	char str5[] = "ノコギリ";
	draw_sjis_text(PLAN_A, str5, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 2, 25, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str5) * 2;

	char str6[] = "★アイテム";
	draw_sjis_text(PLAN_A, str6, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 5, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str6) * 2;

	char str7[] = "椅子";
	draw_sjis_text(PLAN_A, str7, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str7) * 2;

	char str8[] = "机";
	draw_sjis_text(PLAN_A, str8, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 15, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str8) * 2;

	char str9[] = "タンス";
	draw_sjis_text(PLAN_A, str9, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 20, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str9) * 2;

	char str10[] = "レンガ";
	draw_sjis_text(PLAN_A, str10, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 12, 25, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str10) * 2;

	char str11[] = "指輪";
	draw_sjis_text(PLAN_A, str11, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str11) * 2;

	char str12[] = "彫刻";
	draw_sjis_text(PLAN_A, str12, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 15, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str12) * 2;

	char str13[] = "木の家";
	draw_sjis_text(PLAN_A, str13, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 20, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str13) * 2;

	char str14[] = "石の家";
	draw_sjis_text(PLAN_A, str14, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 22, 25, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str14) * 2;

	char str15[] = "木の豪邸";
	draw_sjis_text(PLAN_A, str15, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 10, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str15) * 2;

	char str16[] = "石の豪邸";
	draw_sjis_text(PLAN_A, str16, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 15, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str16) * 2;

	char str17[] = "水槽";
	draw_sjis_text(PLAN_A, str17, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 20, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str17) * 2;

	char str18[] = "★出口→";
	draw_sjis_text(PLAN_A, str18, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 32, 25, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str18) * 2;

	char str19[] = "水";
	draw_sjis_text(PLAN_A, str19, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 3, 0, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str19) * 2;

	char str20[] = "木";
	draw_sjis_text(PLAN_A, str20, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 10, 0, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str20) * 2;

	char str21[] = "鉄";
	draw_sjis_text(PLAN_A, str21, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 17, 0, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str21) * 2;

	char str22[] = "石";
	draw_sjis_text(PLAN_A, str22, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 24, 0, 0); // @suppress("Symbol is not resolved")
	pattern +=  strlen(str22) * 2;

    char str23[] = "お金";
    draw_sjis_text(PLAN_A, str23, TILE_ATTR_FULL(PAL0, 0, 0, 0, pattern), 31, 0, 0); // @suppress("Symbol is not resolved")
    pattern +=  strlen(str23) * 2;

	u16 palette[64];
	memcpy(&palette[0], Player.palette->data, 16 * 2);
	memcpy(&palette[16], rock01.palette->data, 16 * 2);
	memcpy(&palette[32], soradesu_1_image.palette->data, 16 * 2);
	memcpy(&palette[48], zimensample_1_image.palette->data, 16 * 2);

	SPR_update();

	// fade in
	fadeIn( palette );

	// VDP process done, we can re enable interrupts
	SYS_enableInts();

	while(1)
	{
		text(Data.water ,  5,2);
		text(Data.wood  , 12,2);
		text(Data.metal , 19,2);
		text(Data.stone , 26,2);
		text(Data.money , 35,2);

		if ( Data.hammer >= 1 ) {
			VDP_drawText("E", 6, 12);
			VDP_drawText(" ", 6, 17);
			VDP_drawText(" ", 6, 22);
			VDP_drawText(" ", 6, 27);
		}
		else if ( Data.bucket >= 1 ) {
			VDP_drawText(" ", 6, 12);
			VDP_drawText("E", 6, 17);
			VDP_drawText(" ", 6, 22);
			VDP_drawText(" ", 6, 27);
		}
		else if ( Data.bomb >= 1 ) {
			VDP_drawText(" ", 6, 12);
			VDP_drawText(" ", 6, 17);
			VDP_drawText("E", 6, 22);
			VDP_drawText(" ", 6, 27);
		}
		else if ( Data.saw >= 1 ) {
			VDP_drawText(" ", 6, 12);
			VDP_drawText(" ", 6, 17);
			VDP_drawText(" ", 6, 22);
			VDP_drawText("E", 6, 27);
		}

		text(Data.chair , 16,12);
		text(Data.desk  , 16,17);
		text(Data.chest , 16,22);
		text(Data.brick , 16,27);

		text(Data.ring     , 26,12);
		text(Data.sculpture, 26,17);
		text(Data.wHouse   , 26,22);
		text(Data.sHouse   , 26,27);

		text(Data.wMansion, 36,12);
		text(Data.sMansion, 36,17);
		text(Data.tank    , 36,22);

		// 購入できるかどうか
		if ( ( Data.wood >= 10 && Data.stone >= 10 ) ) {
			// ハンマー
		    VDP_drawText("!", 1, 10);
		}
		else {
			VDP_drawText(" ", 1, 10);
		}

		if ( Data.wood >= 20 ){
			// バケツ
		    VDP_drawText("!", 1, 15);
		}
		else {
			VDP_drawText(" ", 1, 15);
		}

		if ( Data.wood >= 15 && Data.stone >= 15 ) {
			// 爆弾
		    VDP_drawText("!", 1, 20);
		}
		else {
			VDP_drawText(" ", 1, 20);
		}

		if ( Data.wood >= 10 && Data.stone >= 10 ) {
			// ノコギリ
		    VDP_drawText("!", 1, 25);
		}
		else {
			VDP_drawText(" ", 1, 25);
		}

		if ( Data.wood >= 5 ) {
			// 椅子
		    VDP_drawText("!", 11, 10);
		}
		else {
			VDP_drawText(" ", 11, 10);
		}

		if ( Data.wood >= 10 ) {
			// 机
		    VDP_drawText("!", 11, 15);
		}
		else {
			VDP_drawText(" ", 11, 15);
		}

		if ( Data.wood >= 5 && Data.metal >= 2 ) {
			// タンス
		    VDP_drawText("!", 11, 20);
		}
		else {
			VDP_drawText(" ", 11, 20);
		}

		if ( Data.stone >= 5 ) {
			// レンガ
		    VDP_drawText("!", 11, 25);
		}
		else {
			VDP_drawText(" ", 11, 25);
		}

		if ( Data.metal >= 2 ) {
			// 指輪
		    VDP_drawText("!", 21, 10);
		}
		else {
			VDP_drawText(" ", 21, 10);
		}

		if ( Data.stone >= 10 ) {
			// 彫刻
		    VDP_drawText("!", 21, 15);
		}
		else {
			VDP_drawText(" ", 21, 15);
		}

		if ( Data.wood >= 20 && Data.metal >= 2 ) {
			// 木の家
		    VDP_drawText("!", 21, 20);
		}
		else {
			VDP_drawText(" ", 21, 20);
		}

		if ( Data.stone >= 20 && Data.metal >= 2 ) {
			// 石の家
		    VDP_drawText("!", 21, 25);
		}
		else {
			VDP_drawText(" ", 21, 25);
		}

		if ( Data.wood >= 20 && Data.metal >= 5 ) {
			// 木の豪邸
		    VDP_drawText("!", 31, 10);
		}
		else {
			VDP_drawText(" ", 31, 10);
		}

		if ( Data.stone >= 20 && Data.metal >= 5 && Data.water >= 10 ) {
			// 石の豪邸
		    VDP_drawText("!", 31, 15);
		}
		else {
			VDP_drawText(" ", 31, 15);
		}

		if ( Data.water >= 20 ) {
			// 水槽
		    VDP_drawText("!", 31, 20);
		}
		else {
			VDP_drawText(" ", 31, 20);
		}

		pad1 = JOY_readJoypad(JOY_1); // @suppress("Symbol is not resolved")
		if (pad0 != pad1) {
			pad0 = pad1;
			if (pad1 & BUTTON_UP) { // @suppress("Symbol is not resolved")
				VDP_drawText(" ", x, y);  // クリア
				y-=5;
			}
			if (pad1 & BUTTON_DOWN) { // @suppress("Symbol is not resolved")
				VDP_drawText(" ", x, y);  // クリア
				y+=5;
			}
			if(pad1 & BUTTON_RIGHT){ // @suppress("Symbol is not resolved")
				VDP_drawText(" ", x, y);  // クリア
				x+=10;
			}
			if(pad1 & BUTTON_LEFT){ // @suppress("Symbol is not resolved")
				VDP_drawText(" ", x, y);  // クリア
				x-=10;
			}

			// カーソル移動範囲の制御
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

			// 必要数の表示
			if ( ( x == 0 && y == 10 ) ){
				// ハンマー
				text(  0,  5,3);	// water
				text(-10, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(-10, 26,3);	// stone
			}
			else if ( ( x == 0 && y == 15 ) ){
				// バケツ
				text(  0,  5,3);	// water
				text(-20, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 0 && y == 20 ) ) {
				// 爆弾
				text(  0,  5,3);	// water
				text(-15, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(-15, 26,3);	// stone
			}
			else if ( ( x == 0 && y == 25 ) ) {
				// ノコギリ
				text(  0,  5,3);	// water
				text(-10, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(-10, 26,3);	// stone
			}
			else if ( ( x == 10 && y == 10 ) ) {
				// 椅子
				text(  0,  5,3);	// water
				text( -5, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 10 && y == 15 ) ) {
				// 机
				text(  0,  5,3);	// water
				text(-10, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 10 && y == 20 ) ) {
				// タンス
				text(  0,  5,3);	// water
				text( -5, 12,3);	// wood
				text( -2, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 10 && y == 25 ) ) {
				// レンガ
				text(  0,  5,3);	// water
				text(  0, 12,3);	// wood
				text(  0, 19,3);	// metal
				text( -5, 26,3);	// stone
			}
			else if ( ( x == 20 && y == 10 ) ) {
				// 指輪
				text(  0,  5,3);	// water
				text(  0, 12,3);	// wood
				text( -2, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 20 && y == 15 ) ) {
				// 彫刻
				text(  0,  5,3);	// water
				text(  0, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(-10, 26,3);	// stone
			}
			else if ( ( x == 20 && y == 20 ) ) {
				// 木の家
				text(  0,  5,3);	// water
				text(-20, 12,3);	// wood
				text( -2, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 20 && y == 25 ) ) {
				// 石の家
				text(  0,  5,3);	// water
				text(  0, 12,3);	// wood
				text( -2, 19,3);	// metal
				text(-20, 26,3);	// stone
			}
			else if ( ( x == 30 && y == 10 ) ) {
				// 木の豪邸
				text(-10,  5,3);	// water
				text(-20, 12,3);	// wood
				text( -5, 19,3);	// metal
				text(  0, 26,3);	// stone
			}
			else if ( ( x == 30 && y == 15 ) ) {
				// 石の豪邸
				text(-10,  5,3);	// water
				text(  0, 12,3);	// wood
				text( -5, 19,3);	// metal
				text(-20, 26,3);	// stone
			}
			else if ( ( x == 30 && y == 20 ) ) {
				// 水槽
				text(-20,  5,3);	// water
				text(  0, 12,3);	// wood
				text(  0, 19,3);	// metal
				text(  0, 26,3);	// stone
			}

			if (pad1 & BUTTON_START // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
			 || pad1 & BUTTON_A // @suppress("Symbol is not resolved") // @suppress("Suggested parenthesis around expression")
			){
				// 購入
				if((x==0 && y==10) && (Data.wood>=10 && Data.stone>=10)&& Data.hammer<1 ){//ハンマー
					Data.wood-=10;
					Data.stone-=10;
					Data.hammer+=1;

					Data.bucket = 0;
					Data.bomb = 0;
					Data.saw = 0;
				}
				else if((x==0 && y==15)&& Data.wood>=20 && Data.bucket<1){//バケツ
					Data.wood -=20;
					Data.bucket+=1;

					Data.hammer = 0;
					Data.bomb = 0;
					Data.saw = 0;
				}
				else if((x==0 && y==20) && (Data.wood>=15 && Data.stone>=15)&& Data.bflag<1){//爆弾
					Data.wood-=15;
					Data.stone-=15;
					Data.bomb+=1;
					Data.bflag+=1;

					Data.hammer = 0;
					Data.bucket = 0;
					Data.saw = 0;
				}
				else if((x==0 && y==25) && (Data.wood>=10 && Data.stone>=10)&& Data.saw<1){//ノコギリ
					Data.wood-=10;
					Data.stone-=10;
					Data.saw+=1;

					Data.hammer = 0;
					Data.bucket = 0;
					Data.bomb = 0;
				}
				else if((x==10 && y==10) && Data.wood>=5){//椅子
					Data.wood-=5;
					Data.chair+=1;
				}
				else if((x==10 && y==15)&&Data.wood>=10 ){//机
					Data.wood-=10;
					Data.desk+=1;
				}
				else if((x==10 && y==20)&& (Data.wood>=5 && Data.metal>=2)){//タンス
					Data.wood-=5;
					Data.metal-=2;
					Data.chest+=1;
				}
				else if((x==10 && y==25) && Data.stone>=5){//レンガ
					Data.stone-=5;
					Data.brick+=1;
				}
				else if((x==20 && y==10)&&Data.metal>=2){//指輪
					Data.metal-=2;
					Data.ring+=1;
				}
				else if((x==20 && y==15) && Data.stone>=10){//彫刻
					Data.stone-=10;
					Data.sculpture+=1;
				}
				else if((x==20 && y==20) && (Data.wood>=20 && Data.metal>=2)){//木の家
					Data.wood-=20;
					Data.metal-=2;
					Data.wHouse+=1;
				}
				else if((x==20 && y==25) && (Data.stone>=20 && Data.metal>=2)){//石の家
					Data.stone-=20;
					Data.metal-=2;
					Data.sHouse+=1;
				}
				else if((x==30 && y==10)&&(Data.wood>=20 && Data.metal>=5 && Data.water>=10)){//木の豪邸
					Data.wood-=20;
					Data.metal-=5;
					Data.water-=10;
					Data.wMansion+=1;
				}
				else if((x==30 && y==15) && (Data.stone>=20 && Data.metal>=5 && Data.water>=10)){//石の豪邸
					Data.stone-=20;
					Data.metal-=5;
					Data.water-=10;
					Data.sMansion+=1;
				}
				else if((x==30 && y==20)&& Data.water>=20 ){//水槽
					Data.water-=20;
					Data.tank+=1;
				}
				else if(x==30 && y==25 ){
					// 出口
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
