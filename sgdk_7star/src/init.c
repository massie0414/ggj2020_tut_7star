#include <genesis.h>
#include "main.h"

datas init(datas Data)
{
	//enum game_mode gm;
	    Data.gm = INIT;

	Data.water=100;
	Data.stone=100;
	Data.metal=100;
	Data.wood=100;

	Data.attack=1;

	Data.hammer=0;
	Data.bucket=0;
	Data.bomb=0;
	Data.bflag=0;//”š’e‚Ìƒtƒ‰ƒO
	Data.saw=0;//ƒmƒRƒMƒŠ
	Data.chair=1;
	Data.desk=0;
	Data.chest=0;//ƒ^ƒ“ƒX
	Data.brick=0;//‚ê‚ñ‚ª
	Data.ring=0;
	Data.sculpture=0;//’¤
	Data.wHouse=0;//–Ø‚Ì‰Æ
	Data.sHouse=0;//Î‚Ì‰Æ
	Data.wMansion=0;//–Ø‚Ì‹“@
	Data.sMansion=0;//Î‚Ì‹“@
	Data.tank=0;
	Data.date =1;
	Data.explore_mode=0;
	Data.money =0;

	Data.gm = DAY;

	return Data;

}
