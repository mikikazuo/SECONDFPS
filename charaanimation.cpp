/*
 * charaanimation.cpp
 *
 *  Created on: 2016/12/16
 *      Author: c501506022
 */

#include "charaanimation.h"
#include "GLMetaseq.h"

MQO_MODEL animation;

chara_animation::chara_animation() {
	// TODO 自動生成されたコンストラクター・スタブ

}

chara_animation::~chara_animation() {
	// TODO Auto-generated destructor stub
}

void chara_animation::Initialize()	{

}

void chara_animation::DrawInitialize(){
	char *flname=(char*)"Data/charamodel/char2/相手/char2_ene_body1.mqo";
	animation=mqoCreateModel(flname,0.0035);
}

void chara_animation::DrawFinalize(){

}
void chara_animation::Update() {


}

void chara_animation::Draw() {
	glPushMatrix();

	glTranslated(5+(11-6)*5,1,-17);
	mqoCallModel(animation);


	glPopMatrix();
}
