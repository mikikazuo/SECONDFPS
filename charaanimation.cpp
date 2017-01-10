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
MQO_MODEL char3[20];
MQO_MODEL char4[20];

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
	flname=(char*)"Data/charamodel/char2/相手/char2_ene_head.mqo";
	char2[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/相手/char2_ene_arm.mqo";
	char2[3]=mqoCreateModel(flname,0.0035);

	flname=(char*)"Data/charamodel/char2/相手/char2_ene_leg1.mqo";
	char2[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/相手/char2_ene_leg2.mqo";
	char2[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/相手/char2_ene_leg3.mqo";
	char2[6]=mqoCreateModel(flname,0.0035);

	flname=(char*)"Data/charamodel/char3/相手/char3_ene_body.mqo";
	char3[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/相手/char3_ene_leg1.mqo";
	char3[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/相手/char3_ene_leg2.mqo";
	char3[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/相手/char3_ene_leg3.mqo";
	char3[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/相手/char3_ene_arm1.mqo";
	char3[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/相手/char3_ene_arm2.mqo";
	char3[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/相手/char3_ene_head.mqo";
	char3[6]=mqoCreateModel(flname,0.0035);

	flname=(char*)"Data/charamodel/char4/相手/char4_ene_body1.mqo";
	char4[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/相手/char4_ene_leg1.mqo";
	char4[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/相手/char4_ene_leg2.mqo";
	char4[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/相手/char4_ene_leg3.mqo";
	char4[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/相手/char4_ene_arm1.mqo";
	char4[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/相手/char4_ene_arm2.mqo";
	char4[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/相手/char4_ene_head.mqo";
	char4[6]=mqoCreateModel(flname,0.0035);
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

	modelPP(char2[0],5+(11-6)*5,1.7,-17);//body
	//modelPP(char2[1],5+(11-6)*5,1,-17);//leg
	modelPP(char2[2],5+(11-6)*5,2.5,-17);//head
	modelPP(char2[3],5+(11-6)*5,1.7,-17);//arm

	int no = 0;
	if(time%60<15) no = 0;
	else if(time%60<30) no = 1;
	else if(time%60<45) no = 0;
	else no = 2;
	modelPP(char2[4+no],5+(11-6)*5,1,-17);//leg


	modelPP(char3[0],32,1.7,-17);//body
	modelPP(char3[1+no],32,1,-17);//leg
	modelPP(char3[6],32,2.5,-17);//head
	modelPP(char3[4],32,1.7,-17);//arm

	modelPP(char4[0],34,1.7,-17);//body
	modelPP(char4[1+no],34,1,-17);//leg
	modelPP(char4[6],34,2.5,-17);//head
	modelPP(char4[4],34,1.7,-17);//arm
}

void modelPP(MQO_MODEL MODEL,double x,double y,double z){
	glPushMatrix();
	glTranslated(x,y,z);
	mqoCallModel(MODEL);
	glPopMatrix();
}
