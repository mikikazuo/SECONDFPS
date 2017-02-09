/*
 * charaanimation.cpp
 *
 *  Created on: 2016/12/16
 *      Author: c501506022
 */

#include "charaanimation.h"
#include "GLMetaseq.h"

MQO_MODEL animation;
int timee;
int anim_starttime[8];
int animechu[8];//アニメ中かどうか
int click[8];//各プレイヤーのマウスクリックの状態(もしくはショットの瞬間)を監視

MQO_MODEL char1[20];
MQO_MODEL char2[20];
MQO_MODEL char3[20];
MQO_MODEL char4[20];
MQO_MODEL char5[20];
MQO_MODEL char6[20];

void modelPP(MQO_MODEL MODEL,double x,double y,double z);
void stand(int model_no,double x,double y,double z,int player_no);

void n_arm(int model_no,double x,double y,double z);
void sn_arm(int model_no,double x,double y,double z);
void shot_arm(int model_no,double x,double y,double z,int player_no);

chara_animation::chara_animation() {
	// TODO 自動生成されたコンストラクター・スタブ

}

chara_animation::~chara_animation() {
	// TODO Auto-generated destructor stub
}

void chara_animation::Initialize()	{
	timee = 0;

	int i;
	for(i=0;i<8;i++){
		anim_starttime[i]=timee;
		animechu[i]=0;
		click[i]=0;
	}

	//click[8] = 0;//プレイヤーの皆さんのクリック状況(またはショットの瞬間を観測)
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
	for(int i=0;i<20;i++){
		if(char1[i]!=NULL)
		mqoDeleteModel(char1[i]);
		if(char2[i]!=NULL)
		mqoDeleteModel(char2[i]);
		if(char3[i]!=NULL)
		mqoDeleteModel(char3[i]);
		if(char4[i]!=NULL)
		mqoDeleteModel(char4[i]);
		if(char5[i]!=NULL)
		mqoDeleteModel(char5[i]);
		if(char6[i]!=NULL)
		mqoDeleteModel(char6[i]);
	}

}
void chara_animation::Update() {
	timee += 1;

	//各プレイヤーがショットている間,１にしてください
	//各プレイヤーがショットしていない間０にしてください
	//とりあえずplayer_no=model_noで仮置きしてます
	click[0] = 1;
	click[1] = 1;
	click[2] = 1;
	click[3] = 1;
	click[4] = 1;
	click[5] = 1;
	click[6] = 1;
	click[7] = 1;

	int i;
	if(timee % 300 < 150){
		for(i=0;i<8;i++){
			click[i]=0;
		}
	}
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

	//歩く

	walk(1,28,0,-17,1);
	walk(2,30,0,-17,2);
	walk(3,32,0,-17,3);
	walk(4,34,0,-17,4);
	walk(5,36,0,-17,5);
	walk(6,38,0,-17,6);

	//直立
	/*
	stand(1,28,0,-17,1);
	stand(2,30,0,-17,2);
	stand(3,32,0,-17,3);
	stand(4,34,0,-17,4);
	stand(5,36,0,-17,5);
	stand(6,38,0,-17,6);
	 */
	///*********************
}

void modelPP(MQO_MODEL MODEL,double x,double y,double z){
	glPushMatrix();
	glTranslated(x,y,z);
	mqoCallModel(MODEL);
	glPopMatrix();
}

void stand(int model_no,double x,double y,double z,int player_no){
	double leg = y+0.5;
	double arm=0;
	arm = arm+1;
	double head=0;
	double body =0;

	switch(model_no){
	case 1:
		body = leg+0.8;
		arm = leg+0.9;
		head = leg+1.5;
		modelPP(char1[0],x,body,z);//body
		modelPP(char1[1],x,leg,z);//leg
		modelPP(char1[7],x,head,z);//head
		//modelPP(char1[4],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(1,x,y,z,player_no);
		}else{
			sn_arm(1,x,y,z);
		}
		break;
	case 2:
		body = leg+0.7;
		arm = leg+0.7;
		head = leg+1.5;
		modelPP(char2[0],x,body,z);//body
		modelPP(char2[4],x,leg,z);//leg
		modelPP(char2[2],x,head,z);//head
		//modelPP(char2[3],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(2,x,y,z,player_no);
		}else{
			sn_arm(2,x,y,z);
		}
		break;
	case 3:
		body = leg+0.7;
		arm = leg+0.9;
		head = leg+1.2;
		modelPP(char3[0],x,body,z);//body
		modelPP(char3[1],x,leg,z);//leg
		modelPP(char3[6],x,head,z);//head
		//modelPP(char3[4],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(3,x,y,z,player_no);
		}else{
			sn_arm(3,x,y,z);
		}
		break;
	case 4:
		body = leg+0.5;
		arm = leg+0.7;
		head = leg+1.1;
		modelPP(char4[0],x,body,z);//body
		modelPP(char4[1],x,leg,z);//leg
		modelPP(char4[6],x,head,z);//head
		//modelPP(char4[4],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(4,x,y,z,player_no);
		}else{
			sn_arm(4,x,y,z);
		}
		break;
	case 5:
		body = leg+0.5;
		arm = leg+0.6;
		head = leg+1.2;
		modelPP(char5[0],x,body,z);//body
		modelPP(char5[1],x,leg,z);//leg
		modelPP(char5[7],x,head,z);//head
		//modelPP(char5[4],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(5,x,y,z,player_no);
		}else{
			sn_arm(5,x,y,z);
		}
		break;
	case 6:
		body = leg+0.4;
		arm = leg+0.7;
		head = leg+1.4;
		modelPP(char6[2],x,body,z);//body
		modelPP(char6[3],x,leg,z);//leg
		modelPP(char6[5],x,head,z);//head
		//modelPP(char6[6],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(6,x,y,z,player_no);
		}else{
			sn_arm(6,x,y,z);
		}
		break;
	default:break;
	}
}

//歩かせる
void chara_animation::walk(int model_no,double x,double y,double z,int player_no){
	//歩行用アニメーション番号　no
	int no = 0;
	if(timee%60<15) no = 0;
	else if(timee%60<30) no = 1;
	else if(timee%60<45) no = 0;
	else no = 2;

	//legを0.5浮かせる
	double leg = y + 0.5;
	double body = 0;
	double arm = 0;
	arm = arm+1;
	double head = 0;

	switch(model_no){
	case 1:
		body = leg+0.8;
		arm = leg+0.9;
		head = leg+1.5;
		modelPP(char1[0],x,body,z);//body
		modelPP(char1[1+no],x,leg,z);//leg
		modelPP(char1[7],x,head,z);//head
		//modelPP(char1[4],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(1,x,y,z,player_no);
		}else{
			n_arm(1,x,y,z);
		}
		break;
	case 2:
		body = leg+0.7;
		arm = leg+0.7;
		head = leg+1.5;
		modelPP(char2[0],x,body,z);//body
		modelPP(char2[4+no],x,leg,z);//leg
		modelPP(char2[2],x,head,z);//head
		//modelPP(char2[3],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(2,x,y,z,player_no);
		}else{
			n_arm(2,x,y,z);
		}
		break;
	case 3:
		body = leg+0.7;
		arm = leg+0.9;
		head = leg+1.2;
		modelPP(char3[0],x,body,z);//body
		modelPP(char3[1+no],x,leg,z);//leg
		modelPP(char3[6],x,head,z);//head
		//modelPP(char3[4],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(3,x,y,z,player_no);
		}else{
			n_arm(3,x,y,z);
		}
		break;
	case 4:
		body = leg+0.5;
		arm = leg+0.7;
		head = leg+1.1;
		modelPP(char4[0],x,body,z);//body
		modelPP(char4[1+no],x,leg,z);//leg
		modelPP(char4[6],x,head,z);//head
		//modelPP(char4[4],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(4,x,y,z,player_no);
		}else{
			n_arm(4,x,y,z);
		}
		break;
	case 5:
		body = leg+0.5;
		arm = leg+0.6;
		head = leg+1.2;
		modelPP(char5[0],x,body,z);//body
		modelPP(char5[1+no],x,leg,z);//leg
		modelPP(char5[7],x,head,z);//head
		//modelPP(char5[4+no],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(5,x,y,z,player_no);
		}else{
			n_arm(5,x,y,z);
		}
		break;
	case 6:
		body = leg+0.4;
		arm = leg+0.7;
		head = leg+1.4;
		modelPP(char6[2],x,body,z);//body
		modelPP(char6[3+no%2],x,leg,z);//leg
		modelPP(char6[5],x,head,z);//head
		//modelPP(char6[6],x,arm,z);//arm
		if(click[player_no] == 1 || animechu[player_no] == 1){//画面クリック中かアニメ中ならショット用の腕
			shot_arm(6,x,y,z,player_no);
		}else{
			n_arm(6,x,y,z);
		}
		break;
	default:break;
	}

}

//歩行中のニュートラルな腕
void n_arm(int model_no,double x,double y,double z){
	//歩行用アニメーション番号　no
	int no = 0;
	if(timee%60<15) no = 0;
	else if(timee%60<30) no = 1;
	else if(timee%60<45) no = 0;
	else no = 2;

	double leg = y + 0.5;
	double arm = leg;

	switch(model_no){
	case 1:
		arm = leg+0.9;
		modelPP(char1[5+no%2],x,arm,z);//arm
		break;
	case 2:
		arm = leg+0.7;
		modelPP(char2[3],x,arm,z);//arm
		break;
	case 3:
		arm = leg+0.9;
		modelPP(char3[4],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
		break;
	case 4:
		arm = leg+0.7;
		modelPP(char4[4],x,arm,z);//arm
		break;
	case 5:
		arm = leg+0.6;
		modelPP(char5[4+no],x,arm,z);//arm
		break;
	case 6:
		arm = leg+0.7;
		modelPP(char6[6],x,arm,z);//arm
		break;
	default:break;
	}
}

//直立中のニュートラルなうで
void sn_arm(int model_no,double x,double y,double z){
	double leg = y + 0.5;
	double arm = leg;

	switch(model_no){
	case 1:
		arm = leg+0.9;
		modelPP(char1[8],x,arm,z);//arm
		break;
	case 2:
		arm = leg+0.7;
		modelPP(char2[3],x,arm,z);//arm
		break;
	case 3:
		arm = leg+0.9;
		modelPP(char3[4],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
		break;
	case 4:
		arm = leg+0.7;
		modelPP(char4[4],x,arm,z);//arm
		break;
	case 5:
		arm = leg+0.6;
		modelPP(char5[5],x,arm,z);//arm
		break;
	case 6:
		arm = leg+0.7;
		modelPP(char6[6],x,arm,z);//arm
		break;
	default:break;
	}
}

//ショット中のアーム
void shot_arm(int model_no,double x,double y,double z,int player_no){
	int arm_no = 0;

	int anim = animechu[player_no];
	int start = anim_starttime[player_no];

	if(anim == 0){//アニメ中でないなら(アニメの始まり)
		anim_starttime[player_no] = timee;
		animechu[player_no] = 1;
		switch(model_no){
		case 1:
			arm_no = 9;
			break;
		case 2:
			arm_no = 7;
			break;
		case 3:
			arm_no = 4;
			break;
		case 4:
			arm_no = 7;
			break;
		case 5:
			arm_no = 8;
			break;
		case 6:
			arm_no = 6;
			break;
		default:break;
		}
	}

	double leg = 0.5;
	double arm = 0;

	if(anim == 1){
		if((timee-start)>=60){//60秒後ならアニメ終わり
			animechu[player_no] = 0;
			switch(model_no){
			case 1:
				arm_no = 4;
				break;
			case 2:
				arm_no = 3;
				break;
			case 3:
				arm_no = 4;
				break;
			case 4:
				arm_no = 4;
				break;
			case 5:
				arm_no = 4;
				break;
			case 6:
				arm_no = 6;
				break;
			default:break;
			}
		}else if((timee-start)>=0 && (timee-start)<=30){//30秒後まで
			switch(model_no){
			case 1:
				arm_no = 8;
				break;
			case 2:
				arm_no = 7;
				break;
			case 3:
				arm_no = 4;
				break;
			case 4:
				arm_no = 7;
				break;
			case 5:
				arm_no = 8;
				break;
			case 6:
				arm_no = 6;
				break;
			default:break;
			}
		}else if((timee-start)>30 && (timee-start)<=60){//30-60病後
			switch(model_no){
			case 1:
				arm_no = 9;
				break;
			case 2:
				arm_no = 8;
				break;
			case 3:
				arm_no = 5;
				break;
			case 4:
				arm_no = 8;
				break;
			case 5:
				arm_no = 4;
				break;
			case 6:
				arm_no = 7;
				break;
			default:break;
			}

		}
	}

	switch(model_no){
	case 1:
		arm = leg+0.9;
		modelPP(char1[arm_no],x,arm,z);//arm
		break;
	case 2:
		arm = leg+0.7;
		modelPP(char2[arm_no],x,arm,z);//arm
		break;
	case 3:
		arm = leg+0.9;
		modelPP(char3[arm_no],x,arm,z+0.2);//arm 腕がもげるのでｚも補正
		break;
	case 4:
		arm = leg+0.7;
		modelPP(char4[arm_no],x-0.2,arm,z);//arm 槍が顔に刺さるのでxも補正
		break;
	case 5:
		arm = leg+0.6;
		modelPP(char5[arm_no],x,arm,z);//arm
		break;
	case 6:
		arm = leg+0.7;
		modelPP(char6[arm_no],x,arm,z);//arm
		break;
	default:break;
	}
}

