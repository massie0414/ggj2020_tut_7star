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
	Data.bflag=0;//���e�̃t���O
	Data.saw=0;//�m�R�M��
	Data.chair=0;//�֎q
	Data.desk=0;//��
	Data.chest=0;//�^���X
	Data.brick=0;//���
	Data.ring=0;//�w��
	Data.sculpture=0;//����
	Data.wHouse=0;//�؂̉�
	Data.sHouse=0;//�΂̉�
	Data.wMansion=0;//�؂̍��@
	Data.sMansion=0;//�΂̍��@
	Data.tank=0;//����
	Data.date =1;
	Data.explore_mode=0;
	Data.money =0;

	Data.gm = DAY;

	return Data;

}
