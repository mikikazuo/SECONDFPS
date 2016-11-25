/*
 * bullet.cpp
 *
 *  Created on: 2016/09/23
 *      Author: user
 */

#include "bullet.h"
#include "mouse.h"
#include "GL/glut.h"
#include "main.h"
#include "checkObjectHit.h"
#include <stdio.h>
#include "Game.h"
#include "player.h"

checkObjectHit bulletmovechecker;

bullet::bullet() {
	// TODO 自動生成されたコンストラクター・スタブ
	for(int i=0;i<MAXBULLET;i++)
		bullet_info[i].count=0;
}
void bullet::bullet_Initialize(){
	for(int i=0;i<MAXBULLET;i++)
		bullet_info[i].count=0;

}
void bullet::setInfo(vec3 playerposition,vec3 playerdir){


	for(int i=0;i<MAXBULLET;i++)
		if(bullet_info[i].count==0){
			bullet_info[i].position=playerposition;
			bullet_info[i].dir=playerdir;
			bullet_info[i].count++;
			break;
		}
}

//mobの弾専用（拠点にダメージを与えない）
void bullet::HitObj(){
	object *mapobject=get_mapobj()->get_obj();
	int mapn=get_mapobj()->get_objnum();
	Wall *playerwall=get_allplayerwall()[0];

	for(int i=0;i<mapn;i++){
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count)
				if(bulletmovechecker.LenOBBToPoint( mapobject[i],  bullet_info[j].position)==0    ){
					bullet_info[j].count=0;
					break;
				}
	}

	for(int i=0;i<WALLMAX;i++){
		for(int j=0;j<MAXBULLET;j++)
			if(playerwall[i].count)
				if(bullet_info[j].count)
					if(	bulletmovechecker.LenOBBToPoint(playerwall[i].wall,  bullet_info[j].position)==0    ){
						bullet_info[j].count=0;
						break;
					}


	}
}
//プレイヤーの弾専用(拠点にダメージを与える
void bullet::HitObj(Team enemyteam,float atk){
	object *mapobject=get_mapobj()->get_obj();
	int mapn=get_mapobj()->get_objnum();
	Wall *playerwall=get_allplayerwall()[0];

	for(int i=0;i<mapn;i++){
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count)
				if(bulletmovechecker.LenOBBToPoint( mapobject[i],  bullet_info[j].position)==0    ){
					for(int k=0;k<BASENUM;k++){
						if(get_mapobj()->get_Base(enemyteam)[k]==i){
							printf("%f\n",get_mapobj()->basehp[(int)enemyteam]);
							get_mapobj()->minus_BaseHp(enemyteam,atk);
							break;
						}
					}
					bullet_info[j].count=0;
					break;
				}
	}

	for(int i=0;i<WALLMAX;i++){
		for(int j=0;j<MAXBULLET;j++)
			if(playerwall[i].count)
				if(bullet_info[j].count)
					if(	bulletmovechecker.LenOBBToPoint(playerwall[i].wall,  bullet_info[j].position)==0    ){
						bullet_info[j].count=0;
						break;
					}


	}


}
void bullet::PlayerToMob(){
	for(int i=0;i<get_mobernum();i++){
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count)
				if(	bulletmovechecker.pointVsPoint(get_mober()[i].position,  bullet_info[j].position,1)){
					get_mober()[i].hp-=get_player()->atk;
					bullet_info[j].count=0;
					break;
				}
	}
}

void bullet::MobToPlayer(int atk){
	for(int j=0;j<MAXBULLET;j++)
		if(bullet_info[j].count)
			if(	bulletmovechecker.pointVsPoint(get_player()->position,  bullet_info[j].position,1)){
				get_player()->hp-=atk;
				bullet_info[j].count=0;
				break;
			}

}

void bullet::Update(){
	const float movespeed=30;
	for(int i=0;i<MAXBULLET;i++)
		if(bullet_info[i].count){
			vec3 move_delta;
			move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
			move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
			move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;
			bullet_info[i].position+=move_delta;//fps_getDeltaTime()* movespeed*bullet_info[i].dir;
			bullet_info[i].count++;
			if(bullet_info[i].count>UPDATEFPS*5)
				bullet_info[i].count=0;
		}

}

void bullet::Draw(){

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	for(int i=0;i<MAXBULLET;i++)
		if(bullet_info[i].count){
			glPushMatrix();
			float x=bullet_info[i].position.x;
			float y=bullet_info[i].position.y;
			float z=bullet_info[i].position.z;
			glTranslatef(x,y,z);

			glutSolidSphere( 0.01f, 50, 50 );
			glPopMatrix();

		}
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

}
bullet::~bullet() {
	// TODO Auto-generated destructor stub
}

