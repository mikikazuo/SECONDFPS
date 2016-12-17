/*
 * enemyPlayer.cpp
 *
 *  Created on: 2016/12/09
 *      Author: c501506022
 */

#include "enemyPlayer.h"




enemyPlayer::enemyPlayer() {
	// TODO 自動生成されたコンストラクター・スタブ

}

void enemyPlayer::Initialize(){
	enemybullet.bullet_Initialize(Crossbow);
}
void enemyPlayer::DrawInitialize(MQO_MODEL setmodel){
	enemymodel=setmodel;

	enemybullet.bullet_DrawInitialize();
}

void enemyPlayer::Draw() {
	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
	//vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);

	glPushMatrix();

	glColor3f(0.5,0.5,0.5);
	glTranslated(position.x,position.y,position.z);
	glRotated(angles.x * 180 /M_PI ,0,1,0);
	//glRotated(-angles.y * 180 /M_PI ,1,0,0);

	mqoCallModel(enemymodel);

	glPopMatrix();

	enemybullet.Draw();
}

void enemyPlayer::resetminushp(){
	serverminushp=0;
}


enemyPlayer::~enemyPlayer() {
	// TODO Auto-generated destructor stub
}

