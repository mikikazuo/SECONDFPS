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


static bool initflag;

bool get_initflag(){
	return initflag;
}

void get_teamnum(int id,C_CONTAINER cdata,S_CONTAINER *sdata){
	sdata->start[id]=cdata.start;
	get_player()[id].start=cdata.start;

	if(initflag==false&&id==0&&cdata.start==false)
		initflag=true;
	if(initflag==true&&cdata.start==true)
		initflag=false;
}

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
		sdata->walls[id][i] = cdata.my_player.mywall[i];
	sdata->players[id].delmove = get_player()[id].delmove;
	get_player()[id].delmove=vec3(0,0,0);

	get_player()[id].position=cdata.my_player.position;
	get_player()[id].angles=cdata.my_player.angles;
	get_player()[id].hp=cdata.my_player.hp;
	sdata->bullets[id].minusplayerhp[id] +=get_player()[id].minushp;
	get_player()[id].minushp=0;

	for(int i=0;i<WALLMAX;i++){
		get_player()[id].mywall[i].count=cdata.my_player.mywall[i].count;
		get_player()[id].mywall[i].wall.set_m_Pos(cdata.my_player.mywall[i].pos);
		get_player()[id].mywall[i].wall.set_m_Rot(cdata.my_player.mywall[i].angles);

	}

	for(int i=0;i<MOBNUM;i++)
		get_mober()[i].minushp+=cdata.my_bullet.minusmobhp[i];
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

	for(int i=0;i<MOBNUM;i++){
		sdata->mob[i].position=get_mober()[i].position;
		sdata->mob[i].angles=get_mober()[i].angles;
		sdata->mob[i].hp=get_mober()[i].hp;
		sdata->mob[i].maxhp=get_mober()[i].maxhp;
		sdata->mob[i].atk=get_mober()[i].atk;
		for(int j=0;j<MOBMAXBULLET;j++){
			if(get_mober()[i].mobbullet.bullet_info[j].count>0){
				sdata->mob[i].mobbullet[j].count=get_mober()[i].mobbullet.bullet_info[j].count;
				sdata->mob[i].mobbullet[j].pos=get_mober()[i].mobbullet.bullet_info[j].position;
				sdata->mob[i].mobbullet[j].angles=get_mober()[i].mobbullet.bullet_info[j].angles;
			}else
				sdata->mob[i].mobbullet[j].count=0;
		}

	}

}

void set_CountDownTime(int id,S_CONTAINER* sdata){
	sdata->countdowntime=get_countdowntime();
}


