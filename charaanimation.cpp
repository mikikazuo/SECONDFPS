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

MQO_MODEL char1[20];
MQO_MODEL char2[20];
MQO_MODEL char3[20];
MQO_MODEL char4[20];
MQO_MODEL char5[20];
MQO_MODEL char6[20];

void modelPP(MQO_MODEL MODEL,double x,double y,double z);
void walk(int model_no,double x,double y,double z);

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
	char *flname=(char*)"Data/charamodel/char2/char2_ene_body1.mqo";
	char2[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_leg1.mqo";
	char2[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_head.mqo";
	char2[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_arm.mqo";
	char2[3]=mqoCreateModel(flname,0.0035);

	flname=(char*)"Data/charamodel/char2/char2_ene_leg1.mqo";
	char2[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_leg2.mqo";
	char2[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_leg3.mqo";
	char2[6]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_shoot.mqo";
	char2[7]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_shooted.mqo";
	char2[8]=mqoCreateModel(flname,0.0035);



	flname=(char*)"Data/charamodel/char1/char1_ene_body.mqo";
	char1[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_leg1.mqo";
	char1[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_leg2.mqo";
	char1[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_leg3.mqo";
	char1[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_shooted.mqo";
	char1[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_hand2.mqo";
	char1[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_hand3.mqo";
	char1[6]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_head.mqo";
	char1[7]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_shoot.mqo";
	char1[8]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_ene_shooted.mqo";
	char1[9]=mqoCreateModel(flname,0.0035);


	flname=(char*)"Data/charamodel/char3/char3_ene_body.mqo";
	char3[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/char3_ene_leg1.mqo";
	char3[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/char3_ene_leg2.mqo";
	char3[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/char3_ene_leg3.mqo";
	char3[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/char3_ene_arm1.mqo";
	char3[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/char3_ene_arm2.mqo";
	char3[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char3/char3_ene_head.mqo";
	char3[6]=mqoCreateModel(flname,0.0035);
	//flname=(char*)"Data/charamodel/char3/char3_ene_shoot.mqo";
	//char3[7]=mqoCreateModel(flname,0.0035);
	//flname=(char*)"Data/charamodel/char3/char3_ene_shooted.mqo";
	//char3[8]=mqoCreateModel(flname,0.0035);


	flname=(char*)"Data/charamodel/char4/char4_ene_body1.mqo";
	char4[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_leg1.mqo";
	char4[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_leg2.mqo";
	char4[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_leg3.mqo";
	char4[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_arm1.mqo";
	char4[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_arm2.mqo";
	char4[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_head.mqo";
	char4[6]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_arm_shoot.mqo";
	char4[7]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_ene_arm_shooted.mqo";
	char4[8]=mqoCreateModel(flname,0.0035);

	flname=(char*)"Data/charamodel/char5/char5_ene_body.mqo";
	char5[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_leg1.mqo";
	char5[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_leg2.mqo";
	char5[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_leg3.mqo";
	char5[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_arm1.mqo";
	char5[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_arm2.mqo";
	char5[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_arm3.mqo";
	char5[6]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_head.mqo";
	char5[7]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_ene_arm_shoot.mqo";
	char5[8]=mqoCreateModel(flname,0.0035);


	flname=(char*)"Data/charamodel/char6/char6_ene_body.mqo";
	char6[0]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_body1.mqo";
	char6[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_body2.mqo";
	char6[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_leg1.mqo";
	char6[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_leg2.mqo";
	char6[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_head.mqo";
	char6[5]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_shoot.mqo";
	char6[6]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char6/char6_ene_shooted.mqo";
	char6[7]=mqoCreateModel(flname,0.0035);
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

	/*
	///歩き
	modelPP(char2[0],5+(11-6)*5,1.2,-17);//body
	//modelPP(char2[1],5+(11-6)*5,1,-17);//leg
	modelPP(char2[2],5+(11-6)*5,2.0,-17);//head
	modelPP(char2[3],5+(11-6)*5,1.2,-17);//arm
	int no = 0;
	if(time%60<15) no = 0;
	else if(time%60<30) no = 1;
	else if(time%60<45) no = 0;
	else no = 2;
	modelPP(char2[4+no],5+(11-6)*5,0.5,-17);//leg

	modelPP(char1[0],28,1.3,-17);//body
	modelPP(char1[1+no],28,0.5,-17);//leg
	modelPP(char1[7],28,2.0,-17);//head
	modelPP(char1[4],28,1.4,-17);//arm

	modelPP(char3[0],32,1.2,-17);//body
	modelPP(char3[1+no],32,0.5,-17);//leg
	modelPP(char3[6],32,1.7,-17);//head
	modelPP(char3[4],32,1.4,-16.8);//arm

	modelPP(char4[0],34,1.0,-17);//body
	modelPP(char4[1+no],34,0.5,-17);//leg
	modelPP(char4[6],34,1.6,-17);//head
	modelPP(char4[4],34,1.2,-17);//arm

	modelPP(char5[0],36,1.0,-17);//body
	modelPP(char5[1+no],36,0.5,-17);//leg
	modelPP(char5[7],36,1.8,-17);//head
	modelPP(char5[4+no],36,1.1,-17);//arm

	modelPP(char6[2],38,0.9,-17);//body
	modelPP(char6[3+no%2],38,0.5,-17);//leg
	modelPP(char6[5],38,1.9,-17);//head
	modelPP(char6[6+no%2],38,1.2,-17);//arm
	*/
	walk(1,28,0,-17);
	walk(2,30,0,-17);
	walk(3,32,0,-17);
	walk(4,34,0,-17);
	walk(5,36,0,-17);
	walk(6,38,0,-17);
	///*********************
}

void modelPP(MQO_MODEL MODEL,double x,double y,double z){
	glPushMatrix();
	glTranslated(x,y,z);
	mqoCallModel(MODEL);
	glPopMatrix();
}


//歩かせる
void walk(int model_no,double x,double y,double z){
	//歩行用アニメーション番号　no
	int no = 0;
	if(time%60<15) no = 0;
	else if(time%60<30) no = 1;
	else if(time%60<45) no = 0;
	else no = 2;

	//legを0.5浮かせる
	double leg = y + 0.5;
	double body = 0;
	double arm = 0;
	double head = 0;

	switch(model_no){
	case 1:
		body = leg+0.8;
		arm = leg+0.9;
		head = leg+1.5;
		modelPP(char1[0],x,body,z);//body
		modelPP(char1[1+no],x,leg,z);//leg
		modelPP(char1[7],x,head,z);//head
		modelPP(char1[4],x,arm,z);//arm
		break;
	case 2:
		body = leg+0.7;
		arm = leg+0.7;
		head = leg+1.5;
		modelPP(char2[0],x,body,z);//body
		modelPP(char2[4+no],x,leg,z);//leg
		modelPP(char2[2],x,head,z);//head
		modelPP(char2[3],x,arm,z);//arm
		break;
	case 3:
		body = leg+0.7;
		arm = leg+0.9;
		head = leg+1.2;
		modelPP(char3[0],x,body,z);//body
		modelPP(char3[1+no],x,leg,z);//leg
		modelPP(char3[6],x,head,z);//head
		modelPP(char3[4],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
		break;
	case 4:
		body = leg+0.5;
		arm = leg+0.7;
		head = leg+1.1;
		modelPP(char4[0],x,body,z);//body
		modelPP(char4[1+no],x,leg,z);//leg
		modelPP(char4[6],x,head,z);//head
		modelPP(char4[4],x,arm,z);//arm
		break;
	case 5:
		body = leg+0.5;
		arm = leg+0.6;
		head = leg+1.3;
		modelPP(char5[0],x,body,z);//body
		modelPP(char5[1+no],x,leg,z);//leg
		modelPP(char5[7],x,head,z);//head
		modelPP(char5[4+no],x,arm,z);//arm
		break;
	case 6:
		body = leg+0.4;
		arm = leg+0.7;
		head = leg+1.4;
		modelPP(char6[2],x,body,z);//body
		modelPP(char6[3+no%2],x,leg,z);//leg
		modelPP(char6[5],x,head,z);//head
		modelPP(char6[6],x,arm,z);//arm
		break;
	default:break;
	}

}

//ニュートラルな腕
void arm(int model_no,double x,double y,double z){
	//歩行用アニメーション番号　no
	int no = 0;
	if(time%60<15) no = 0;
	else if(time%60<30) no = 1;
	else if(time%60<45) no = 0;
	else no = 2;

	double leg = y + 0.5;
	double arm = leg;

	switch(model_no){
		case 1:
			arm = leg+0.9;
			modelPP(char1[4],x,arm,z);//arm
			break;
		case 2:
			arm = leg+0.7;
			modelPP(char2[4+no],x,leg,z);//leg
			modelPP(char2[2],x,head,z);//head
			modelPP(char2[3],x,arm,z);//arm
			break;
		case 3:
			body = leg+0.7;
			arm = leg+0.9;
			head = leg+1.2;
			modelPP(char3[0],x,body,z);//body
			modelPP(char3[1+no],x,leg,z);//leg
			modelPP(char3[6],x,head,z);//head
			modelPP(char3[4],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
			break;
		case 4:
			body = leg+0.5;
			arm = leg+0.7;
			head = leg+1.1;
			modelPP(char4[0],x,body,z);//body
			modelPP(char4[1+no],x,leg,z);//leg
			modelPP(char4[6],x,head,z);//head
			modelPP(char4[4],x,arm,z);//arm
			break;
		case 5:
			body = leg+0.5;
			arm = leg+0.6;
			head = leg+1.3;
			modelPP(char5[0],x,body,z);//body
			modelPP(char5[1+no],x,leg,z);//leg
			modelPP(char5[7],x,head,z);//head
			modelPP(char5[4+no],x,arm,z);//arm
			break;
		case 6:
			body = leg+0.4;
			arm = leg+0.7;
			head = leg+1.4;
			modelPP(char6[2],x,body,z);//body
			modelPP(char6[3+no%2],x,leg,z);//leg
			modelPP(char6[5],x,head,z);//head
			modelPP(char6[6],x,arm,z);//arm
			break;
		default:break;
		}
}


//ショット用(腕だけ)
void shot_arm(int model_no,double x,double y,double z){
	static int start = 0;//アニメーション開始時間
	static int anim = 0;//アニメーション中かどうか

	if(anim == 0){
		start = time;
		anim = 1;
	}

	if(anim == 1){
		if((time-start)>60){//60秒後ならアニメ終わり
			anim = 0;
		}else if((time-start)>0 && (time-start)<=30){//30秒後まで

		}else if((time-start)>30 && (time-start)<=60){//30-60病後

		}
	}
}

