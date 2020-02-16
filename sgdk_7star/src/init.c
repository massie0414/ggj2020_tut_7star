#include <genesis.h>
#include "main.h"

datas init(datas Data)
{
	//enum game_mode gm;
	Data.gm = INIT;

	Data.water=1000;
	Data.stone=1000;
	Data.metal=1000;
	Data.wood=1000;

	Data.attack=1;

	Data.hammer=0;
	Data.bucket=0;
	Data.bomb=0;
	Data.bflag=0;//”š’e‚Ìƒtƒ‰ƒO
	Data.saw=0;//ƒmƒRƒMƒŠ
	Data.chair=0;//ˆÖq
	Data.desk=0;//Š÷
	Data.chest=0;//ƒ^ƒ“ƒX
	Data.brick=0;//‚ê‚ñ‚ª
	Data.ring=0;//w—Ö
	Data.sculpture=0;//’¤
	Data.wHouse=0;//–Ø‚Ì‰Æ
	Data.sHouse=0;//Î‚Ì‰Æ
	Data.wMansion=0;//–Ø‚Ì‹“@
	Data.sMansion=0;//Î‚Ì‹“@
	Data.tank=0;//…‘…
	Data.date =1;
	Data.explore_mode=0;
	Data.money =0;

	Data.gm = DAY;

	return Data;

}
