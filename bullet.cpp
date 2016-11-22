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

bullet::bullet() {
	// TODO 自動生成されたコンストラクター・スタブ
	for(int i=0;i<MAXBULLET;i++)
		bullet_info[i].count=0;
}

void bullet::setInfo(vec3 playerposition,vec3 playerdir){

	if(get_mousebutton_count(LEFT_BUTTON)%10==1)
		for(int i=0;i<MAXBULLET;i++)
			if(bullet_info[i].count==0){
				bullet_info[i].position=playerposition;
				bullet_info[i].dir=playerdir;
				bulletcollider[i].setOBB((vec3)bullet_info[i].position,vec3(1,1,1));
				bullet_info[i].count++;
				break;
			}
}
void bullet::Update(){
	const float movespeed=10;
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

