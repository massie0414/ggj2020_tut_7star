/**
 * (C) 2015 Nendo
 */
#include <genesis.h>
#include "draw_sjis.h"
#include "resource.h"

void draw_sjis_text(VDPPlan plan, const char *str, u16 flags, u16 x, u16 y, u8 use_dma)
{
    u16 str_length = strlen(str);//������
    u16 pattern = flags & TILE_INDEX_MASK;//�p�^�[���e�[�u���̈ʒu // @suppress("Symbol is not resolved")
    u16 baseflags = flags & TILE_ATTR_MASK;//�l�[���e�[�u���o�^���Ƀt���O�����ׂ̈ɕK�v // @suppress("Symbol is not resolved")
    u16 i;

    for(i = 0; i < str_length; i++)
    {
        //�擪��1Byte�����o��
        u8 c = str[i];

        // �S�p����i�V�t�gJIS�j��񐅏��܂ł͈͓̔�������
        if(c >= 0x81 && c <= 0x9F)
        {
            int font_x = ((u8)str[i + 1] - Foot_Byte_Offset) * 16 ;//X���W���v�Z
            int font_y = ((u8)str[i] - Head_Byte_Offset) * 2;//Y���W���v�Z

            //�p�^�[���e�[�u���ɓo�^
            VDP_loadTileData( &sjis_font.tiles[font_x + (font_y * Font_Image_Width)], pattern, Font_Cell_Size, use_dma);//�㔼��
            pattern += Font_Cell_Size;
            VDP_loadTileData( &sjis_font.tiles[font_x + ((font_y + 1) * Font_Image_Width)], pattern, Font_Cell_Size, use_dma);//������
            pattern += Font_Cell_Size;

            //�l�[���e�[�u���ɓo�^
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
