#include <genesis.h>
#include "main.h"
#include "game.h"

struct datas init(struct datas Data)
{
	//enum game_mode gm;
	    Data.gm = INIT;

	Data.water=0;
	Data.stone=0;
	Data.metal=0;
	Data.wood=0;

	Data.attack=1;

	Data.hammer=0;
	Data.bucket=0;
	Data.bomb=0;
	Data.bflag=0;//���e�̃t���O
	Data.saw=0;//�m�R�M��
	Data.chair=0;
	Data.desk=0;
	Data.chest=0;//�^���X
	Data.brick=0;//���
	Data.ring=0;
	Data.sculpture=0;//����
	Data.wHouse=0;//�؂̉�
	Data.sHouse=0;//�΂̉�
	Data.wMansion=0;//�؂̍��@
	Data.sMansion=0;//�΂̍��@
	Data.tank=0;

	Data.gm = GAME;

	return Data;

}
