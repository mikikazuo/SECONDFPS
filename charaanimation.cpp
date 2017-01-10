/*
 * charaanimation.cpp
 *
 *  Created on: 2016/12/16
 *      Author: c501506022
 */

#include "charaanimation.h"
#include "GLMetaseq.h"

MQO_MODEL animation;
int time;
MQO_MODEL char2[20];

void modelPP(MQO_MODEL MODEL,double x,double y,double z);

chara_animation::chara_animation() {
	// TODO 自動生成されたコンストラクター・スタブ

}

chara_animation::~chara_animation() {
	// TODO Auto-generated destructor stub
}

void chara_animation::Initialize()	{
	time = 0;
}

void chara_animation::DrawInitialize(){
	char *flname=(char*)"Data/charamodel/char2/相手/char2_ene_body1.mqo";
	char2[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/相手/char2_ene_leg1.mqo";
	char2[1]=mqoCreateModel(flname,0.0035);
}

void chara_animation::DrawFinalize(){

}
void chara_animation::Update() {
	time += 1;

}

void chara_animation::Draw() {
	//glPushMatrix();
	//glTranslated(5+(11-6)*5,1+1,-17);
	//mqoCallModel(char2[0]);
	//glPopMatrix();

	modelPP(char2[0],5+(11-6)*5,1+1,-17);
	modelPP(char2[1],5+(11-6)*5,1,-17);
}

void modelPP(MQO_MODEL MODEL,double x,double y,double z){
	glPushMatrix();
	glTranslated(x,y,z);
	mqoCallModel(MODEL);
	glPopMatrix();
}
