/*
 * get_sdata.cpp
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */
#include "stdio.h"
#include "net_common.h"
#include "Game.h"

int get_bulletdata(S_CONTAINER sdata){
	int i;
	int count=0;
	for(i=0;i<MAXBULLET;i++){
		if(sdata.bullets[i].bullet_info.count>0) count++;
	}

	//弾の数の表示
	printf("bullets number = %d\n",count);

	return 0;
}

int get_playerdata(S_CONTAINER sdata){
	float x,y,z;
	int i;
	for(i=0;i<2;i++){

		x=sdata.players[i].position.x;
		y=sdata.players[i].position.y;
		z=sdata.players[i].position.z;
//
//		get_enemy()->position.x=x;
//		get_enemy()->position.y=y;
//		get_enemy()->position.z=z;
//
//		get_enemy()->position.x=sdata.players[i].angles.x;
//		get_enemy()->position.y=sdata.players[i].angles.y;
//		get_enemy()->position.z=sdata.players[i].angles.z;
//
//		get_enemy()->angles.x=sdata.players[i].angles.x;
//		get_enemy()->angles.y=sdata.players[i].angles.y;
//		get_enemy()->angles.z=sdata.players[i].angles.z;

//		get_enemy()->position.x=sdata.players[i].angles.;
//		get_enemy()->position.y=sdata.players[i].angles.;
//		get_enemy()->position.z=sdata.players[i].angles.;


//		get_enemy()->position.x=x;
//		get_enemy()->position.y=y;
//		get_enemy()->position.z=z;
		printf("player[%d]=(%f,%f,%f)\n",i,x,y,z);
	}
	return 0;
}

