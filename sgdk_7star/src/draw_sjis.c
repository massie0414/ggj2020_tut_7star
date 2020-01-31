/**
 * (C) 2015 Nendo
 */
#include <genesis.h>
#include "draw_sjis.h"
#include "resource.h"

void draw_sjis_text(VDPPlan plan, const char *str, u16 flags, u16 x, u16 y, u8 use_dma)
{
    u16 str_length = strlen(str);//文字数
    u16 pattern = flags & TILE_INDEX_MASK;//パターンテーブルの位置 // @suppress("Symbol is not resolved")
    u16 baseflags = flags & TILE_ATTR_MASK;//ネームテーブル登録時にフラグ合成の為に必要 // @suppress("Symbol is not resolved")
    u16 i;

    for(i = 0; i < str_length; i++)
    {
        //先頭の1Byteを取り出す
        u8 c = str[i];

        // 全角判定（シフトJIS）第二水準までの範囲内か判定
        if(c >= 0x81 && c <= 0x9F)
        {
            int font_x = ((u8)str[i + 1] - Foot_Byte_Offset) * 16 ;//X座標を計算
            int font_y = ((u8)str[i] - Head_Byte_Offset) * 2;//Y座標を計算

            //パターンテーブルに登録
            VDP_loadTileData( &sjis_font.tiles[font_x + (font_y * Font_Image_Width)], pattern, Font_Cell_Size, use_dma);//上半分
            pattern += Font_Cell_Size;
            VDP_loadTileData( &sjis_font.tiles[font_x + ((font_y + 1) * Font_Image_Width)], pattern, Font_Cell_Size, use_dma);//下半分
            pattern += Font_Cell_Size;

            //ネームテーブルに登録
            VDP_fillTileMapRectInc(
            		plan,
					baseflags | pattern -4,
					x + i,
					y,
					Font_Cell_Size,
					Font_Cell_Size
			);

            i++;
        }
    }
}
