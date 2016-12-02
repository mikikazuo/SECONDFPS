/*
 * get_sdata.cpp
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */
#include "stdio.h"
#include "net_common.h"

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

		printf("player[%d]=(%f,%f,%f)\n",i,x,y,z);
	}
	return 0;
}

