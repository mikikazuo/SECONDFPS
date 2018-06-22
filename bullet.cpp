/*
 * bullet.cpp
 *
 *  Created on: 2016/09/23
 *      Author: user
 */

#include "bullet.h"

#include "GL/glut.h"

#include <stdio.h>



#include "math.h"
#include "checkObjectHit.h"
#include "server_main.h"
#include "net_common.h"
checkObjectHit bulletmovechecker;

bullet::bullet() {
	// TODO 自動生成されたコンストラクター・スタブ
	for(int i=0;i<MAXBULLET;i++)
		bullet_info[i].count=0;
}
void bullet::bullet_Initialize(Role setbulletmode){
	bulletradi=0.01f;

	for(int i=0;i<MAXBULLET;i++)
		bullet_info[i].count=0;
	launchbulletcount=0;
	reloadtime=0;
	mode=setbulletmode;


	lifetime=3;


	switch(setbulletmode){
	case Crossbow:
		reloadmax=5;
		speed=50;


		break;
	case Rifle:
		reloadmax=10;
		speed=50;
		break;
	case Gatling:
		reloadmax=150;
		speed=8;
		break;
	case Spear:
		reloadmax=1;
		speed=5;
		break;
	case Magicstick:
		reloadmax=20;
		speed=8;
		break;
	case Magic:
		reloadmax=30;
		speed=9;
		break;
	case Mob:
		reloadmax=30;
		speed=30;
		break;
	default:
		break;
	}

}
void bullet::setInfo(vec3 playerposition,vec3 playerdir){


	for(int i=0;i<(mode==Mob)?MOBMAXBULLET:MAXBULLET;i++)
		if(launchbulletcount<reloadmax)
			if(bullet_info[i].count==0){
				bullet_info[i].position=playerposition;
				bullet_info[i].dir=playerdir;
				if(mode==Gatling){
					bullet_info[i].dir.x+=0.01*GetRandom(-5,5);
					bullet_info[i].dir.y+=0.01*GetRandom(-5,5);
					bullet_info[i].dir.z+=0.01*GetRandom(-5,5);
				}

				bullet_info[i].angles=vec3(atan2(bullet_info[i].dir.x,bullet_info[i].dir.z),
						atan2(bullet_info[i].dir.y,bullet_info[i].dir.x*bullet_info[i].dir.x+bullet_info[i].dir.z*bullet_info[i].dir.z),
						atan2(bullet_info[i].dir.z,bullet_info[i].dir.x));
				if(mode!=Mob)
					launchbulletcount++;
				bullet_info[i].count++;
				break;
			}


}


//void bullet::reload(){
//
//	if(key_getmove(Reload)==2&&reloadtime==0){
//		reloadtime++;
//	}
//
//
//	if(reloadtime>0)
//		reloadtime++;
//	if(reloadtime>UPDATEFPS*3){
//		reloadtime=0;
//		launchbulletcount=0;
//	}
//
//
//}
//

//mobの弾専用（拠点にダメージを与えない）
void bullet::HitObj(){
	object *mapobject=get_mapobj()->get_obj();
	int mapn=get_mapobj()->get_objnum();


	for(int i=0;i<mapn;i++){
		for(int j=0;j<MOBMAXBULLET;j++)
			if(bullet_info[j].count)
				if(bulletmovechecker.LenOBBToPoint( mapobject[i],  bullet_info[j].position)<0.5f     ){
					bullet_info[j].count=0;
					break;
				}
	}

	for(int k=0;k<MAX_CLIENTS;k++){
		Wall *playerwall=get_player()[k].get_mywall();
		for(int i=0;i<WALLMAX;i++){
			for(int j=0;j<MOBMAXBULLET;j++)
				if(playerwall[i].count)
					if(bullet_info[j].count)
						if(	bulletmovechecker.LenOBBToPoint(playerwall[i].wall,  bullet_info[j].position)<0.5f    ){
							bullet_info[j].count=0;
							break;
						}


		}
	}
}
////プレイヤーの弾専用(拠点にダメージを与える
//void bullet::HitObj(Team enemyteam,float atk){
//	object *mapobject=get_mapobj()->get_obj();
//	int mapn=get_mapobj()->get_objnum();
//	Wall *playerwall=get_allplayerwall()[0];
//
//	for(int i=0;i<mapn;i++){
//		for(int j=0;j<MAXBULLET;j++)
//			if(bullet_info[j].count)
//				if(bulletmovechecker.LenOBBToPoint( mapobject[i],  bullet_info[j].position)==0    ){
//					for(int k=0;k<BASENUM;k++){
//						if(get_mapobj()->get_Base(enemyteam)[k]==i){
//							//printf("%f\n",get_mapobj()->basehp[(int)enemyteam]);
//							get_mapobj()->minus_BaseHp(enemyteam,atk);
//							break;
//						}
//					}
//					bullet_info[j].count=0;
//					break;
//				}
//	}
//
//	for(int i=0;i<WALLMAX;i++){
//		for(int j=0;j<MAXBULLET;j++)
//			if(playerwall[i].count)
//				if(bullet_info[j].count)
//					if(	bulletmovechecker.LenOBBToPoint(playerwall[i].wall,  bullet_info[j].position)==0    ){
//						bullet_info[j].count=0;
//						break;
//					}
//
//
//	}
//
//
//}
void bullet::PlayerToMob(){
	for(int i=0;i<get_mobernum();i++){
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count>0)
				if(	bulletmovechecker.pointVsPoint(get_mober()[i].position,  bullet_info[j].position,1)){
					get_mober()[i].hp-=50;
					bullet_info[j].count=0;
					printf("hitenemy\n");
					break;
				}
	}
}

void bullet::MobToPlayer(int atk){
	for(int i=0;i<MAX_CLIENTS;i++)
		for(int j=0;j<MOBMAXBULLET;j++)
			if(bullet_info[j].count)
				if(	bulletmovechecker.pointVsPoint(get_player()[i].position,  bullet_info[j].position,1)){
					get_player()[i].minushp+=atk;
					bullet_info[j].count=0;
					break;
				}

}

void bullet::Update(){
	const float movespeed=speed;
	for(int i=0;i<MAXBULLET;i++)
		if(bullet_info[i].count){
			vec3 move_delta;
			switch(mode){
			case Crossbow:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				bullet_info[i].dir.y-=0.005f;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;

				break;
			case Rifle:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;
				break;
			case Gatling:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;
				break;
			case Spear:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				bullet_info[i].dir.y-=0.01f;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;
				break;
			case Magicstick:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;
				break;
			case Magic:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;
				break;
			case Mob:
				move_delta.x=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.x;
				move_delta.y=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.y;
				move_delta.z=get_mainfps().fps_getDeltaTime()* movespeed*bullet_info[i].dir.z;

				break;
			default:
				break;
			}




			bullet_info[i].position+=move_delta;//fps_getDeltaTime()* movespeed*bullet_info[i].dir;
			bullet_info[i].count++;
			if(bullet_info[i].count>UPDATEFPS*lifetime)
				bullet_info[i].count=0;
		}
	//reload();
}

//void bullet::Draw(){
//
//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHTING);
//
//
//	for(int i=0;i<MAXBULLET;i++)
//		if(bullet_info[i].count){
//			glPushMatrix();
//			float x=bullet_info[i].position.x;
//			float y=bullet_info[i].position.y;
//			float z=bullet_info[i].position.z;
//			glTranslatef(x,y,z);
//
//			glutSolidSphere( bulletradi, 50, 50 );
//			glPopMatrix();
//
//		}
//	glDisable(GL_LIGHT0);
//	glDisable(GL_LIGHTING);
//
//}
bullet::~bullet() {
	// TODO Auto-generated destructor stub
}

