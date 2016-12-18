/*
 * get_data.cpp
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */

#include "get_data.h"
#include "stdio.h"
#include "net_common.h"
#include "bullet.h"
#include "server_main.h"
#include "map.h"


void get_walldata(int id,C_CONTAINER cdata,S_CONTAINER *sdata){

}

//
//void minus_PlayerHp(int id,C_CONTAINER cdata,S_CONTAINER *sdata){
//	for(int i=0;i<2;i++){
//		if(i==id)
//			continue;
//		player_minushp[i]+=
//	}
//}
int get_playerdata(int id,C_CONTAINER cdata,S_CONTAINER *sdata){

	sdata->players[id] = cdata.my_player;
	sdata->bullets[id] = cdata.my_bullet;
	for(int i=0;i<WALLMAX;i++)
	sdata->walls[id][i] = cdata.my_wall[i];

	for(int i=0;i<10;i++){
		get_mober()[i].minushp+=cdata.my_bullet.minusmobhp[i];

	}
	for(int i=0;i<2;i++)
		get_mapobj()->minushp[i]+=cdata.my_bullet.minusbasehp[i];
	return 0;
}

void set_MapData(int id,S_CONTAINER* sdata){

	for(int i=0;i<MOVABLE;i++){
		if(get_movableno()[i]==-1)
			break;
		sdata->movablemapobj[i].objno=get_movableno()[i];
		sdata->movablemapobj[i].position=get_mapobj()->get_obj()[get_movableno()[i]].get_m_Pos();
		sdata->movablemapobj[i].rotation=get_mapobj()->get_obj()[get_movableno()[i]].get_m_Rot();
	}
	for(int i=0;i<2;i++){
	sdata->basehp[i]=get_mapobj()->basehp[i];
	}
}

void set_MobData(int id,S_CONTAINER* sdata){

	for(int i=0;i<10;i++){
		sdata->mob[i].position=get_mober()[i].position;
		sdata->mob[i].angles=get_mober()[i].angles;
		sdata->mob[i].hp=get_mober()[i].hp;
		sdata->mob[i].maxhp=get_mober()[i].maxhp;
		sdata->mob[i].atk=get_mober()[i].atk;
		//sdata->mob[i].bullets.count=get_mober()[i].bullets.count;
	}

}

