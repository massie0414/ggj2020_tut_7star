/**
 * (C) 2015 Nendo
 */
#ifndef _DRAW_SJIS_H_
#define _DRAW_SJIS_H_

//フォント画像の横幅
#define Font_Image_Width 3024

//フォントのセルサイズ（16x16）
#define Font_Cell_Size 2

//全角先頭Byteの補正値
#define Head_Byte_Offset 129

//全角後方Byteの補正値
#define Foot_Byte_Offset 64


/**
 *  \brief
 *      Draw japanese text in backgound plan.
 *
 *  \param plan
 *      Plan we want to use to draw text.<br/>
 *      Accepted values are:<br/>
 *      - VDP_PLAN_A<br/>
 *      - VDP_PLAN_B<br/>
 *  \param str
 *      String to draw.
 *  \param flags
 *      tile flags (see TILE_ATTR macro).
 *  \param x
 *      X position (in tile).
 *  \param y
 *      y position (in tile).
 *  \param use_dma
 *      Use DMA or software clear.
 *
 *  Using DMA permit faster clear operation but can lock Z80 execution.
 *
 *  This method uses the specified plan to draw the text.<br/>
 *  Each character fit in one tile (16x16 pixels).
 */
void draw_sjis_text(VDPPlan plan, const char * str, u16 flags, u16 x, u16 y, u8 use_dma);

#endif // _DRAW_SJIS_H_
