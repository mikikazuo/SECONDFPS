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

int get_bulletdata(S_CONTAINER sdata){

	for(int i=0;i<MAX_CLIENTS;i++){
		if(i==get_player()->myid){
			for(int j=0;j<MAXBULLET;j++){
				if(sdata.bullets[i].bullet_info[j].count>0){
					get_playerbullet().bullet_info[j].count=sdata.bullets[i].bullet_info[j].count;
					get_playerbullet().bullet_info[j].position=sdata.bullets[i].bullet_info[j].pos;
					get_playerbullet().bullet_info[j].angles=sdata.bullets[i].bullet_info[j].angles;

				}else
					get_playerbullet().bullet_info[j].count=0;

			}
		}else{
			for(int j=0;j<MAXBULLET;j++){
				if(sdata.bullets[i].bullet_info[j].count>0){
					get_enemy()->enemybullet.bullet_info[j].count=sdata.bullets[i].bullet_info[j].count;
					get_enemy()->enemybullet.bullet_info[j].position.x=sdata.bullets[i].bullet_info[j].pos.x;
					get_enemy()->enemybullet.bullet_info[j].position.y=sdata.bullets[i].bullet_info[j].pos.y;
					get_enemy()->enemybullet.bullet_info[j].position.z=sdata.bullets[i].bullet_info[j].pos.z;
					get_enemy()->enemybullet.bullet_info[j].angles.x=sdata.bullets[i].bullet_info[j].angles.x;
					get_enemy()->enemybullet.bullet_info[j].angles.y=sdata.bullets[i].bullet_info[j].angles.y;
					get_enemy()->enemybullet.bullet_info[j].angles.z=sdata.bullets[i].bullet_info[j].angles.z;

				}else
					get_enemy()->enemybullet.bullet_info[j].count=0;
				//弾の数の表示
				//	printf("bullets number = %d\n",j);
			}
		}
	}


	return 0;
}

int get_playerdata(S_CONTAINER sdata){
	float x,y,z;
	int i;
	for(i=0;i<2;i++){
		if(i==get_player()->myid)
			continue;
		x=sdata.players[i].position.x;
		y=sdata.players[i].position.y;
		z=sdata.players[i].position.z;

		get_enemy()->position.x=x;
		get_enemy()->position.y=y;
		get_enemy()->position.z=z;

		get_enemy()->angles.x=sdata.players[i].angles.x;
		get_enemy()->angles.y=sdata.players[i].angles.y;
		get_enemy()->angles.z=sdata.players[i].angles.z;

		get_enemy()->lookat.x=sdata.players[i].lookat.x;
		get_enemy()->lookat.y=sdata.players[i].lookat.y;
		get_enemy()->lookat.z=sdata.players[i].lookat.z;

		//		get_enemy()->position.x=sdata.players[i].angles.;
		//		get_enemy()->position.y=sdata.players[i].angles.;
		//		get_enemy()->position.z=sdata.players[i].angles.;


		get_enemy()->position.x=x;
		get_enemy()->position.y=y;
		get_enemy()->position.z=z;

		//printf("player[%d]=(%f,%f,%f)\n",i,x,y,z);
	}
	return 0;
}

int get_MapData(S_CONTAINER sdata){
	for(int i=0;i<50;i++){
		if(sdata.movablemapobj[i].objno==-1)
			break;
		vec3 pos=vec3(sdata.movablemapobj[i].position.x,sdata.movablemapobj[i].position.y,sdata.movablemapobj[i].position.z);
		get_mapobj()->get_obj()[sdata.movablemapobj[i].objno].set_m_Pos(pos);

		vec3 rot=vec3(sdata.movablemapobj[i].rotation.x,sdata.movablemapobj[i].rotation.y,sdata.movablemapobj[i].rotation.z);
		get_mapobj()->get_obj()[sdata.movablemapobj[i].objno].set_m_Rot(rot);
	}

	for(int i=0;i<2;i++)
		get_mapobj()->basehp[i]=sdata.hp[i].basehp;

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


