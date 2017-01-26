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
#include "net_common.h"
#include "key.h"
#include "math.h"

checkObjectHit bulletmovechecker;

bullet::bullet() {
	// TODO 自動生成されたコンストラクター・スタブ
}
void bullet::bullet_Initialize(){
	bulletradi=0.01f;

	for(int i=0;i<MAXBULLET;i++)
		bullet_info[i].count=0;
	launchbulletcount=0;
	reloadtime=0;



	lifetime=6;


	switch(mode){
	case Crossbow:
		reloadmax=5;
		speed=50;
		break;
	case Rifle:
		reloadmax=10;
		speed=50;
		break;
	case Gatling:
		reloadmax=100;
		speed=20;
		break;
	case Spear:
		reloadmax=1;
		speed=40;
		break;
	case Magicstick:
		reloadmax=20;
		speed=15;
		break;
	case Magic:
		reloadmax=30;
		speed=15;
		break;
	case Mob:
		reloadmax=30;
		speed=10;
		break;
	default:
		break;
	}

}

void bullet::bullet_DrawInitialize(Role setbulletmode){
	char *flname=(char*)"Data/charamodel/char5/char5_tama.mqo";


	mode=setbulletmode;
	switch(mode){
	case Crossbow:
		flname=(char*)"Data/charamodel/char1/char1_tama.mqo";
		bulletmodel=mqoCreateModel(flname,0.01);
		break;
	case Rifle:
		flname=(char*)"Data/charamodel/char2/char2_tama.mqo";
		bulletmodel=mqoCreateModel(flname,0.005);
		break;
	case Gatling:
		flname=(char*)"Data/charamodel/char2/char2_tama.mqo";
		bulletmodel=mqoCreateModel(flname,0.002);
		break;
	case Spear:
		flname=(char*)"Data/charamodel/char4/char4_tama.mqo";
		bulletmodel=mqoCreateModel(flname,0.01);
		break;
	case Magicstick:
		flname=(char*)"Data/charamodel/char5/char5_tama.mqo";
		bulletmodel=mqoCreateModel(flname,0.005);
		break;
	case Magic:
		flname=(char*)"Data/charamodel/char6/char6_tama.mqo";
		bulletmodel=mqoCreateModel(flname,0.01);
		break;
	case Mob:
		bulletmodel=mqoCreateModel(flname,0.001);
		break;
	default:
		break;
	}
}
void bullet::setInfo(vec3 playerposition,vec3 playerdir){

	//vec3 forward_dir = vec3(sinf(get_player()->angles.x), 0, cosf(get_player()->angles.x));
	//vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);

//	if(mode==Magic){
//		for(int i=0;i<MAXBULLET;i++)
//			if(launchbulletcount<reloadmax)
//				if(bullet_info[i].count==0){
//					for(int j=0;j<3;j++){
//						if(i+j>MAXBULLET)
//							break;
//						bullet_info[i+j].position=playerposition;
//						switch(j){
//						case 0:
//							bullet_info[i+j].position+=right_dir*0.2f;
//							break;
//						case 1:
//							bullet_info[i+j].position-=right_dir*0.2f;
//							break;
//						case 2:
//							bullet_info[i+j].position.y-=0.2f;
//							break;
//						}
//						bullet_info[i+j].dir=playerdir;
//						bullet_info[i+j].count++;
//					}
//					break;
//				}
//	}else{
		for(int i=0;i<MAXBULLET;i++)
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
					bullet_info[i].count++;
					break;
				}
	//}

}

void bullet::reload(){

	if(key_getmove(Reload)==2&&reloadtime==0&&launchbulletcount!=0){
		reloadtime++;
	}


	if(reloadtime>0)
		reloadtime++;
	if(reloadtime>UPDATEFPS*3){
		reloadtime=0;
		launchbulletcount=0;
	}


}


//mobの弾専用（拠点にダメージを与えない）
void bullet::HitObj(){
	object *mapobject=get_mapobj()->get_obj();
	int mapn=get_mapobj()->get_objnum();
	Wall *playerwall=get_player()->get_mywall();

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
	Wall *playerwall=get_player()->get_mywall();


	for(int i=0;i<mapn;i++){
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count)
				if(bulletmovechecker.LenOBBToPoint( mapobject[i],  bullet_info[j].position)<0.3f ){
					for(int k=0;k<BASENUM;k++){
						if(get_mapobj()->get_Base(enemyteam)[k]==i){
							//printf("%f\n",get_mapobj()->basehp[(int)enemyteam]);
							//	get_mapobj()->minus_BaseHp(enemyteam,atk);
							get_mapobj()->serverminushp[enemyteam]+=get_player()->atk;

							break;
						}
					}
					bullet_info[j].count=0;
					break;
				}
	}

	for(int k=0;k<MAX_CLIENTS;k++)
		for(int i=0;i<WALLMAX;i++)
			for(int j=0;j<MAXBULLET;j++){
				if(k==get_player()->myid){
					if(playerwall[i].count>0)
						if(bullet_info[j].count)
							if(	bulletmovechecker.LenOBBToPoint(playerwall[i].wall,  bullet_info[j].position)<0.3f    ){
								bullet_info[j].count=0;
								break;
							}
				}else{
					if(get_enemy()[k].mywall[i].count>0)
						if(bullet_info[j].count)
							if(	bulletmovechecker.LenOBBToPoint(get_enemy()[k].mywall[i].wall,  bullet_info[j].position)<0.3f  ){
								bullet_info[j].count=0;
								break;
							}
				}

			}

}

//
void bullet::EnemyPlayerToPlayer(){
	for(int j=0;j<MAXBULLET;j++)
		if(bullet_info[j].count)
			if(	bulletmovechecker.pointVsPoint(get_player()->position,  bullet_info[j].position,1)){
				get_player()->hp-=20;
				bullet_info[j].count=0;
				break;
			}

}

//
void bullet::PlayerToEnemy(){
	for(int i=0;i<MAX_CLIENTS;i++){
		if(i==get_player()->myid||get_enemy()[i].myteam==get_player()->myteam)
			continue;
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count)
				if(	bulletmovechecker.pointVsPoint(get_enemy()[i].position,  bullet_info[j].position,1)){
					get_enemy()[i].serverminushp+=10;
					bullet_info[j].count=0;
					break;
				}
	}

}

void bullet::PlayerToMob(){
	for(int i=0;i<get_mobernum();i++){
		for(int j=0;j<MAXBULLET;j++)
			if(bullet_info[j].count)
				if(get_mober()[i].hp>0)
					if(	bulletmovechecker.pointVsPoint(get_mober()[i].position,  bullet_info[j].position,1)){
						get_mober()[i].serverminushp+=get_player()->atk;
						//あてるだけで手に入るexp
						get_player()->exp+=10;
						get_mober()[i].hitred++;

						if(get_mober()[i].hp-get_player()->atk<=0){
							printf("dead mob!!\n");
							get_player()->exp+=GETEXP;


						}
						if(get_player()->exp+GETEXP>=100)
							get_player()->level+=(get_player()->exp/100);
						get_player()->exp%=100;
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
				bullet_info[i].angles.y-=0.1f;
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
	reload();
}

void bullet::Draw(){

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	for(int i=0;i<MAXBULLET;i++)
		if(bullet_info[i].count>0){
			glPushMatrix();
			float x=bullet_info[i].position.x;
			float y=bullet_info[i].position.y;
			float z=bullet_info[i].position.z;
			glTranslatef(x,y,z);
			glRotated(bullet_info[i].angles.x * 180 /M_PI ,0,1,0);
			glRotated(-bullet_info[i].angles.y * 180 /M_PI ,1,0,0);
			mqoCallModel(bulletmodel);
			glPopMatrix();
		}
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

}
bullet::~bullet() {
	// TODO Auto-generated destructor stub
}

