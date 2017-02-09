/*
 * get_sdata.cpp
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */
#include "stdio.h"
#include "net_common.h"
#include "net_client.h"
#include "Game.h"

int Bullets_number[8];

int get_bulletdata(S_CONTAINER sdata){

	for(int i=0;i<MAX_CLIENTS;i++){
		if(i==get_player()->myid)
			continue;

		Bullets_number[i]=0;
		get_player()->hp-=sdata.bullets[i].minusplayerhp[get_player()->myid];
		for(int j=0;j<MAXBULLET;j++){
			if(sdata.bullets[i].bullet_info[j].count>0){
				Bullets_number[i] += 1;
				get_enemy()[i].enemybullet.bullet_info[j].count=sdata.bullets[i].bullet_info[j].count;
				get_enemy()[i].enemybullet.bullet_info[j].position=sdata.bullets[i].bullet_info[j].pos;
				get_enemy()[i].enemybullet.bullet_info[j].angles=sdata.bullets[i].bullet_info[j].angles;
			}else
				get_enemy()[i].enemybullet.bullet_info[j].count=0;
			//弾の数の表示
			//	printf("bullets number = %d\n",j);


		}
	}


	return 0;
}

int get_playerdata(S_CONTAINER sdata){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(i==get_player()->myid)
			continue;
		get_enemy()[i].position=sdata.players[i].position;
		get_enemy()[i].angles=sdata.players[i].angles;
		get_enemy()[i].lookat=sdata.players[i].lookat;

		for(int j=0;j<WALLMAX;j++){
			get_enemy()[i].mywall[j].count=sdata.walls[i][j].count;
			get_enemy()[i].mywall[j].wall.set_m_Pos(sdata.walls[i][j].pos);
			get_enemy()[i].mywall[j].wall.set_m_Rot(sdata.walls[i][j].angles);
		}
		/*
		vec3 v3;
		double x,y,z;
		v3 = get_enemy()[i].position;
		x = v3.x;
		y = v3.y;
		z = v3.z;
		printf("player[%d]=(%f,%f,%f)\n",i,x,y,z);
	*/
	}
	return 0;
}

int get_MapData(S_CONTAINER sdata){
	for(int i=0;i<MOVABLE;i++){
		if(sdata.movablemapobj[i].objno==-1)
			break;
		vec3 pos=vec3(sdata.movablemapobj[i].position.x,sdata.movablemapobj[i].position.y,sdata.movablemapobj[i].position.z);
		get_mapobj()->get_obj()[sdata.movablemapobj[i].objno].set_m_Pos(pos);

		vec3 rot=vec3(sdata.movablemapobj[i].rotation.x,sdata.movablemapobj[i].rotation.y,sdata.movablemapobj[i].rotation.z);
		get_mapobj()->get_obj()[sdata.movablemapobj[i].objno].set_m_Rot(rot);
	}

	for(int i=0;i<2;i++)
		get_mapobj()->basehp[i]=sdata.basehp[i];

	return 0;
}

int get_MobData(S_CONTAINER sdata){
	for(int i=0;i<10;i++){
		get_mober()[i].position=sdata.mob[i].position;
		get_mober()[i].angles=sdata.mob[i].angles;
		get_mober()[i].hp=sdata.mob[i].hp;
		get_mober()[i].maxhp=sdata.mob[i].maxhp;
		get_mober()[i].atk=sdata.mob[i].atk;
	}
	return 0;
}


