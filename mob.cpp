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

	dir=GetRandom(0,3);
	flag=0;

}

mob::~mob() {
	// TODO Auto-generated destructor stub
}

//位置、当たり半径、HP,攻撃力
void mob::Initialize(int no,vec3 pos,float ra,int sethp,int setatk,float setatkrange){
	dx=GetRandom(1,100);
	movecount=0;
	myno=no;
	flag=0;
	position=pos;
	mobbullet.bullet_Initialize();
	radi=ra;
	hp=sethp;
	atk=setatk;
	atkrange=setatkrange;

}
void mob::DrawInitialize(){

	char *flname=(char*)"Data/a/a.mqo";
	mobmqo=mqoCreateModel(flname,0.0035);

}
void mob::Update(){
	movecount++;
	move();
	launchBullet();
	mobbullet.HitObj();
	mobbullet.MobToPlayer(this->atk);

}
void mob::move(){
	const float mousespeed = 10;
	const float movespeed = 4;


	if(movecount%(60*1)==0)
		dx=GetRandom(-10,10);
	if(flag>10)
		angles.x -= dx * mousespeed*get_mainfps().fps_getDeltaTime();
	else{
		angles.x -= 0* mousespeed*get_mainfps().fps_getDeltaTime();
	}

	dx=0;
	if(angles.x < -M_PI)
		angles.x += M_PI * 2;
	else if(angles.x > M_PI)
		angles.x -= M_PI * 2;

	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));



	vec3 sampposition;
	sampposition=position;


	if(flag>10)
		sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
	else{
		sampposition += forward_dir * 0* get_mainfps().fps_getDeltaTime();
		flag++;
	}



	//マップに衝突時向きを反転
	if(mobhitobj.sethitcheck(get_mapobj()->get_objnum(),get_mapobj()->get_obj(),sampposition,1)){
		angles.x -= M_PI;
		if(angles.x < -M_PI)
			angles.x += M_PI * 2;
		else if(angles.x > M_PI)
			angles.x -= M_PI * 2;

		vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
		//vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);



		vec3 sampposition;
		sampposition=position;


		sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();

	}

//	static float gravity;
//	gravity+=0.3f;
//	sampposition.y-=(gravity*get_mainfps().fps_getDeltaTime());
//

	position=sampposition;

	//	float x=pow(position.x-playerinfo->position.x,2);
	//	float y=pow(position.y-playerinfo->position.y,2);
	//	float z=pow(position.z-playerinfo->position.z,2);

	//	if(x+y+z<pow(5,2))



}

void mob::Draw(){
	if(hp<=0)
		return;
	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	float x=position.x;
	float y=position.y;
	float z=position.z;

	glTranslatef(x,y,z);

			glutSolidSphere( 1, 50, 50 );

	glRotated(angles.x * 180 /M_PI ,0,1,0);

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
	if(radi>=x+y+z&&movecount%30==0){
		//mobbullet.setInfo(position,vec3(0, 1, 0));
		mobbullet.setInfo(position,vec3((get_player()->position.x-position.x)/big, (get_player()->position.y-position.y)/big, (get_player()->position.z-position.z)/big));
		PlayMobMusic(myno);
	}
	mobbullet.Update();
}

