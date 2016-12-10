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
void enemyPlayer::DrawInitialize(MQO_MODEL setmodel){
	enemymodel=setmodel;
}

void enemyPlayer::Draw() {
	glPushMatrix();

	glColor3f(0.5,0.5,0.5);
	glTranslated(position.x,position.y,position.z);
	glRotated(180,0,1,0);
	mqoCallModel(enemymodel);

	glPopMatrix();
}
enemyPlayer::~enemyPlayer() {
	// TODO Auto-generated destructor stub
}

