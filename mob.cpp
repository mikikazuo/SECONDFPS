/*
 * mob.cpp
 *
 *  Created on: 2016/11/15
 *      Author: c501506022
 */

#include "mob.h"
#include <math.h>
#include "fps.h"
#include "main.h"
#include "GL/glut.h"
#include <time.h>

#include "GLMetaseq.h"
#include "map.h"

#include "checkObjectHit.h"
#include "Game.h"

#include "mouse.h"
#include "sound.h"

checkObjectHit mobhitobj;
MQO_MODEL mobmqo;





int GetRandom(int min,int max)
{
	static int flag;

	if (flag == 0) {
		srand((unsigned int)time(NULL));
		flag = 1;
	}

	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

mob::mob() {
	// TODO 自動生成されたコンストラクター・スタブ

	flag=0;

}

mob::~mob() {
	// TODO Auto-generated destructor stub
}

////位置、当たり半径、HP,攻撃力
//void mob::Initialize(int no,vec3 pos,float ra,float sethp,float setatk,int setatktime,float setatkrange){
//	dx=GetRandom(1,100);
//	movecount=0;
//	myno=no;
//	flag=0;
//	position=pos;
//	mobbullet.bullet_Initialize();
//	radi=ra;
//	hp=maxhp=sethp;
//	atk=setatk;
//	atkrange=setatkrange;
//	atktime=setatktime;
//	vsinfo.findplayer=false;
//	vsinfo.mobmode=noneaction;
//
//}

void mob::resetminushp(){
	serverminushp=0;
}
void mob::DrawInitialize(char *filename){
	mobmqo=mqoCreateModel(filename,0.0025);
	mobbullet.bullet_DrawInitialize(Mob);
}

void mob::DrawFinalize(){

	mqoDeleteModel(mobmqo);
	mobbullet.bullet_DrawFinalize();
}
//void mob::Update(){
//	movecount++;
//	move();
//	launchBullet();
//	mobbullet.HitObj();
//	mobbullet.MobToPlayer(this->atk);
//
//}
//void mob::move(){
//	const float mousespeed = 10;
//	const float movespeed = 4;
//
//	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
//	vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);
//	vec3 toplayer_dir = vec3((get_player()->position.x-position.x), (get_player()->position.y-position.y), (get_player()->position.z-position.z));
//
//	if(!vsinfo.findplayer){
//		angles.y=0;
//		if(movecount%(60*1)==0)
//			dx=GetRandom(-10,10);
//
//		angles.x -= dx * mousespeed*get_mainfps().fps_getDeltaTime();
//
//
//
//		dx=0;
//		if(angles.x < -M_PI)
//			angles.x += M_PI * 2;
//		else if(angles.x > M_PI)
//			angles.x -= M_PI * 2;
//
//
//
//
//
//		vec3 sampposition;
//		sampposition=position;
//
//
//		if(flag>10)
//			sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
//		else{
//			sampposition += forward_dir * 0* get_mainfps().fps_getDeltaTime();
//			flag++;
//		}
//
//
//
//		//マップに衝突時向きを反転
//		if(!this->hitmap&&(mobhitobj.sethitcheck(get_mapobj()->get_objnum(),get_mapobj()->get_obj(),sampposition,radi)||
//				mobhitobj.sethitcheck(WALLMAX,get_player()->get_mywall(),sampposition,radi))	){
//			angles.x -= M_PI;
//			if(angles.x < -M_PI)
//				angles.x += M_PI * 2;
//			else if(angles.x > M_PI)
//				angles.x -= M_PI * 2;
//
//			vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
//			//vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);
//
//			this->hitmap=true;
//
//			vec3 sampposition;
//			sampposition=position;
//			sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
//
//		}else{
//			this->hitmap=false;
//
//		}
//
//
//		//	static float gravity;
//		//	gravity+=0.3f;
//		//	sampposition.y-=(gravity*get_mainfps().fps_getDeltaTime());
//		//
//
//		position=sampposition;
//
//		//	float x=pow(position.x-playerinfo->position.x,2);
//		//	float y=pow(position.y-playerinfo->position.y,2);
//		//	float z=pow(position.z-playerinfo->position.z,2);
//
//		//	if(x+y+z<pow(5,2))
//	}else{
//		switch(vsinfo.mobmode){
//		case sidestep:
//			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
//					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
//			position.x+=forward_dir.x*movespeed * get_mainfps().fps_getDeltaTime();
//			position.z+=forward_dir.z*movespeed * get_mainfps().fps_getDeltaTime();
//			break;
//		case sidestephard:
//			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
//					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
//			position.x+=forward_dir.x*movespeed * get_mainfps().fps_getDeltaTime();
//			position.z+=forward_dir.z*movespeed * get_mainfps().fps_getDeltaTime();
//			break;
//		case runaway:
//			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
//					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
//
//			position.x-=forward_dir.x*movespeed * get_mainfps().fps_getDeltaTime();
//			position.z-=forward_dir.z*movespeed * get_mainfps().fps_getDeltaTime();
//			break;
//		case noneaction:
//
//			break;
//		}
//
//
//	}
//}

void mob::Draw(){
	if(hp<=0)
		return;
	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	float x=position.x;
	float y=position.y;
	float z=position.z;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glTranslatef(x,y,z);

	//glutSolidSphere( 1, 50, 50 );

	glRotated(angles.x * 180 /M_PI ,0,1,0);
	glRotated(-angles.y * 180 /M_PI ,1,0,0);


	mqoCallModel(mobmqo);


	glPopMatrix();
	mobbullet.Draw();

}

void mob::launchBullet(){
	float x=pow(position.x-get_player()->position.x,2);
	float y=pow(position.y-get_player()->position.y,2);
	float z=pow(position.z-get_player()->position.z,2);
	float big=sqrt(x+y+z);
	float radi=atkrange*atkrange;

	if(hp>0){
		if(radi>=x+y+z){
			if(movecount%atktime==0){
				//mobbullet.setInfo(position,vec3(0, 1, 0));
				mobbullet.setInfo(position,vec3((get_player()->position.x-position.x)/big, (get_player()->position.y-position.y)/big, (get_player()->position.z-position.z)/big));
				PlayMobMusic(myno);
			}
			if(!vsinfo.findplayer){
				vsinfo.findplayer=true;
				vsinfo.mobmode=runaway;//(attackmode)GetRandom(0,2);
			}
		}else if(vsinfo.mobmode==runaway){
			if(radi*2<=x+y+z)
				vsinfo.findplayer=false;
		}else
			vsinfo.findplayer=false;

		mobbullet.Update();
	}

}


