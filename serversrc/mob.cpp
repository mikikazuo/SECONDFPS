/*
 * mob.cpp
 *
 *  Created on: 2016/11/15
 *      Author: c501506022
 */

#include "mob.h"
#include <math.h>
#include "fps.h"

#include "GL/glut.h"
#include <time.h>
#include <stdio.h>

#include "map.h"

#include "checkObjectHit.h"

#include "server_main.h"
#include "net_common.h"
checkObjectHit mobhitobj;
//MQO_MODEL mobmqo;
//MQO_MODEL pre_mobmqo[10];			//異なるモデルを保存する




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


}

mob::~mob() {
	// TODO Auto-generated destructor stub
}

//位置、当たり半径、HP,攻撃力
void mob::Initialize(int no,vec3 pos,float ra,float sethp,float setatk,int setatktime,float setatkrange){
	dx=GetRandom(1,100);
	movecount=0;
	myno=no;

	position=pos;
	radi=ra;
	hp=maxhp=sethp;
	atk=setatk;
	atkrange=setatkrange;
	atktime=setatktime;
	vsinfo.findplayer=false;
	vsinfo.mobmode=noneaction;
	minushp=0;
	mobbullet.bullet_Initialize(Mob);
	dir=GetRandom(0,1)==0?-1:1;
}

void mob::minushpfunc(){
	if(minushp>0){
		hp-=minushp;
		minushp=0;
	}
}


//void mob::DrawInitialize(char *filename){
//	static char *flname='\0';
//	static int mqonum;
//	if(flname!=filename){
//		flname=filename;
//		pre_mobmqo[mqonum] =mobmqo=mqoCreateModel(flname,0.0025);
//		mqonum%=(int)(sizeof(pre_mobmqo)/sizeof(pre_mobmqo[0]));
//	}
//}
//
//void mob::DrawFinalize(){
//	for(int i=0;(int)(sizeof(pre_mobmqo)/sizeof(pre_mobmqo[0]));i++)
//		if(pre_mobmqo[i]!=NULL){
//			mqoDeleteModel( pre_mobmqo[i]);
//			pre_mobmqo[i]=NULL;
//		}
//}
void mob::Update(){
	movecount++;
	move();
	if(hp>0){
		launchBullet();
		mobbullet.HitObj();
		mobbullet.MobToPlayer(this->atk);
	}
	mobbullet.Update();
}
void mob::move(){
	const float mousespeed = 10;
	const float movespeed = 4;

	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
	vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);
	vec3 toplayer_dir = vec3((get_player()[vsinfo.playerid].position.x-position.x), (get_player()[vsinfo.playerid].position.y-position.y), (get_player()[vsinfo.playerid].position.z-position.z));
	float toplayer_dir_big=sqrt(toplayer_dir.x*toplayer_dir.x+toplayer_dir.y*toplayer_dir.y+toplayer_dir.z*toplayer_dir.z);
	toplayer_dir.x/=toplayer_dir_big;
	toplayer_dir.y/=toplayer_dir_big;
	toplayer_dir.z/=toplayer_dir_big;

	vec3 sampposition=position;
	if(!vsinfo.findplayer){
		angles.y=0;
		angles.x -= dx * mousespeed*get_mainfps().fps_getDeltaTime();
		dx=0;
		if(angles.x < -M_PI)
			angles.x += M_PI * 2;
		else if(angles.x > M_PI)
			angles.x -= M_PI * 2;






		sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();



		//TODO 壁衝突時のmob
		//マップに衝突時向きを反転
		if((mobhitobj.sethitcheck(get_mapobj()->get_objnum(),get_mapobj()->get_obj(),sampposition,radi)||
				mobhitobj.sethitcheck(WALLMAX,get_player(),sampposition,radi))	){
			angles.x -= M_PI;
			if(angles.x < -M_PI)
				angles.x += M_PI * 2;
			else if(angles.x > M_PI)
				angles.x -= M_PI * 2;

			forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
			//vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);

			this->hitmap=true;

			sampposition=position;
			sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();

		}else{
			this->hitmap=false;

		}

		if(!this->hitmap)
			if(movecount%(60*1)==0)
				dx=GetRandom(-10,10);

		//	static float gravity;
		//	gravity+=0.3f;
		//	sampposition.y-=(gravity*get_mainfps().fps_getDeltaTime());
		//

		position=sampposition;

		//	float x=pow(position.x-playerinfo->position.x,2);
		//	float y=pow(position.y-playerinfo->position.y,2);
		//	float z=pow(position.z-playerinfo->position.z,2);

		//	if(x+y+z<pow(5,2))
	}else{
		switch(vsinfo.mobmode){
		case sidestep:
			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
			sampposition.x+=right_dir.x*dir*movespeed * get_mainfps().fps_getDeltaTime();
			sampposition.z+=right_dir.z*dir*movespeed * get_mainfps().fps_getDeltaTime();

			if((mobhitobj.sethitcheck(get_mapobj()->get_objnum(),get_mapobj()->get_obj(),sampposition,radi)||
					mobhitobj.sethitcheck(WALLMAX,get_player(),sampposition,radi))	){
				dir*=-1;
			}else
				position=sampposition;

			break;
		case sidestephard:
			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
			sampposition.x+=right_dir.x*dir*movespeed * get_mainfps().fps_getDeltaTime();
			sampposition.z+=right_dir.z*dir*movespeed * get_mainfps().fps_getDeltaTime();
			sampposition.x+=toplayer_dir.x*movespeed * get_mainfps().fps_getDeltaTime()*0.5f;
			sampposition.z+=toplayer_dir.z*movespeed * get_mainfps().fps_getDeltaTime()*0.5f;
			if((mobhitobj.sethitcheck(get_mapobj()->get_objnum(),get_mapobj()->get_obj(),sampposition,radi)||
					mobhitobj.sethitcheck(WALLMAX,get_player(),sampposition,radi))	){
				dir*=-1;
			}else
				position=sampposition;
			break;
		case runaway:
			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
			sampposition.x+=right_dir.x*dir*movespeed * get_mainfps().fps_getDeltaTime();
			sampposition.z+=right_dir.z*dir*movespeed * get_mainfps().fps_getDeltaTime();
			sampposition.x-=forward_dir.x*movespeed * get_mainfps().fps_getDeltaTime();
			sampposition.z-=forward_dir.z*movespeed * get_mainfps().fps_getDeltaTime();
			if((mobhitobj.sethitcheck(get_mapobj()->get_objnum(),get_mapobj()->get_obj(),sampposition,radi)||
					mobhitobj.sethitcheck(WALLMAX,get_player(),sampposition,radi))	){
				dir*=-1;
			}else
				position=sampposition;
			break;
		case noneaction:
			angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
					atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
			break;
		}



	}
}

//void mob::Draw(){
//	if(hp<=0)
//		return;
//	glMatrixMode(GL_MODELVIEW);
//
//
//	glPushMatrix();
//	float x=position.x;
//	float y=position.y;
//	float z=position.z;
//
//	glTranslatef(x,y,z);
//
//	//glutSolidSphere( 1, 50, 50 );
//
//	glRotated(angles.x * 180 /M_PI ,0,1,0);
//	glRotated(-angles.y * 180 /M_PI ,1,0,0);
//	mqoCallModel(mobmqo);
//
//	glPopMatrix();
//	mobbullet.Draw();
//
//}


void mob::launchBullet(){
	float big;
	vec3  sa;
	float radi=atkrange*atkrange;
	if(!vsinfo.findplayer){
		for(int i=0;i<MAX_CLIENTS;i++){
			sa.x=pow(position.x-get_player()[i].position.x,2);
			sa.y=pow(position.y-get_player()[i].position.y,2);
			sa.z=pow(position.z-get_player()[i].position.z,2);
			big=sqrt(sa.x+sa.y+sa.z);

			if(radi>=sa.x+sa.y+sa.z){
				vsinfo.findplayer=true;
				vsinfo.mobmode=(attackmode)GetRandom(0,2);
				vsinfo.playerid=i;
				break;
			}
		}
	}else{
		sa.x=pow(position.x-get_player()[vsinfo.playerid].position.x,2);
		sa.y=pow(position.y-get_player()[vsinfo.playerid].position.y,2);
		sa.z=pow(position.z-get_player()[vsinfo.playerid].position.z,2);
		big=sqrt(sa.x+sa.y+sa.z);
		if(movecount%atktime==0)
			mobbullet.setInfo(position,vec3((get_player()[vsinfo.playerid].position.x-position.x)/big, (get_player()[vsinfo.playerid].position.y-position.y)/big, (get_player()[vsinfo.playerid].position.z-position.z)/big));
		//		PlayMobMusic(myno);
		if(vsinfo.mobmode==runaway){
			if(radi*1.3f<sa.x+sa.y+sa.z)
				vsinfo.findplayer=false;
		}
		else if(radi<sa.x+sa.y+sa.z){
			vsinfo.findplayer=false;
		}

	}


}


