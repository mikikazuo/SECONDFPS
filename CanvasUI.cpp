/*
 * CanvasUI.cpp
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#include "CanvasUI.h"
#include "GL/glut.h"
#include "image.h"
#include "Game.h"

CanvasUI::CanvasUI() {
	// TODO 自動生成されたコンストラクター・スタブ

}

CanvasUI::~CanvasUI() {
	// TODO Auto-generated destructor stub
}

//計算関連の初期化
void CanvasUI::Initialize(){
	dam = 0;
	a = 100;
	time = 0;
	shakeX = 0;
	shakeY = 0;

	int i;
	for(i=0;i<5;i++){
		wall_info[i]=100;
	}
}

//描画関連の初期化
void CanvasUI::DrawInitialize(){
	//handle[0]=image_Load("Data/image/capture2.png");
	handle[0]=image_Load("Data/image/assist.png");
	handle[1]=image_Load("Data/image/man.png");
	handle[2]=image_Load("Data/image/man_B.png");
	handle[3]=image_Load("Data/image/level.png");
	handle[4]=image_Load("Data/image/player_HP_bar.png");

	//HPbar 10-13
	handle[10]=image_Load("Data/image/HP_bar_back.png");//下地B
	handle[11]=image_Load("Data/image/HP_bar_back_Red.png");//下地R
	handle[12]=image_Load("Data/image/HP_bar_tex.png");//質感
	handle[13]=image_Load("Data/image/HP_bar_frame.png");//枠

	//Wallinfo
	handle[14]=image_Load("Data/image/3wall_info.png");//壁情報

}


//描画関連の終了処理
void CanvasUI::DrawFinalize(){
	for(int i=0;i<(int)(sizeof handle/sizeof handle[0]);i++)
		image_free(handle[i]);

}


//2D描画用に変換
void CanvasUI::view2D() {
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,w,h,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
}

//毎フレーム計算
void CanvasUI::Update() {
	time += 1;

	//	if(time % 150 >= 149){//一定時間ごとに自動ダメージ
	//		dam = time;
	//		a -= 5+rand()%20;
	//		if(a<0) a=100;
	//
	//		int i;
	//		for(i=0;i<5;i++){//壁ダメ変化
	//			wall_info[i]=rand()%100;
	//			if(rand()%10==0) wall_info[i]=-1;
	//		}
	//
	//	}else{
	//		//dam = 0;
	//	}

	//	if((time-dam)<30){
	//		if((time-dam)%3 == 0){
	//			shakeX = rand()%15-7;
	//			shakeY = rand()%15-7;
	//		}
	//	}else{
	//		shakeX = 0;
	//		shakeY = 0;
	//	}

	shake(get_player()->hp);
}

void CanvasUI::shake(float nowhp){
	static int shakecount;
	static float prehp=prehp==0?nowhp:prehp;


	if(shakecount>40){
		prehp=nowhp;
		shakecount=0;
	}else if(nowhp!=prehp){
		shakecount++;

	}

	if(shakecount%10==0&&shakecount!=0){
		shakeX = rand()%15-7;
		shakeY = rand()%15-7;
	}else{
		shakeX = 0;
		shakeY = 0;
	}

}
//毎フレーム描画
void CanvasUI::Draw() {
	//image_DrawExRota(handle[0],500,200,0,1);
	image_DrawExRota(handle[0],600,350,0,1);//照準

	//自陣HP
	glColor3d(1.0,0.2,0.2);//赤指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[11],10+shakeX,10+shakeY,280*0.01*a,60);//ゲージ描画
	image_DrawExRota(handle[11],150+shakeX,50+shakeY,0,1);//背景

	image_DrawExRota(handle[12],150+shakeX,50+shakeY,0,1);//ハイライト,質感
	image_DrawExRota(handle[13],150+shakeX,50+shakeY,0,1);//枠

	//敵陣HP
	glColor3d(0.2,0.2,1.0);//青指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[9],1190-280*0.01*100*(get_mapobj()->basehp[BlueTeam]/get_mapobj()->basemaxhp[BlueTeam])+shakeX,
			10+shakeY,280*0.01*100*(get_mapobj()->basehp[BlueTeam]/get_mapobj()->basemaxhp[BlueTeam])+shakeX,60);//ゲージ描画
	image_DrawExRota(handle[10],1050+shakeX,50+shakeY,0,1);//背景

	image_DrawExRota(handle[12],1050+shakeX,50+shakeY,0,1);//ハイライト、質感
	image_DrawExRota(handle[13],1050+shakeX,50+shakeY,0,1);//枠

	//image_DrawExRota(handle[3],75+shakeX,680+shakeY,0,2);//Lv

	glColor3d(1.0*0.01*100*(1-get_player()->hp/get_player()->maxhp),1.0*0.01*100*get_player()->hp/get_player()->maxhp,0);//色指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[3],170+shakeX,650+shakeY,300*get_player()->hp/get_player()->maxhp,49);//ゲージ描画
	image_DrawExRota(handle[4],320+shakeX,662+shakeY,0,1);//playerHP

	int i;
	for(i=0;i<4;i++){
		image_DrawExRota(handle[1],350+55*i+shakeX,40+shakeY,0,1);
		image_DrawExRota(handle[2],850-55*i+shakeX,40+shakeY,0,1);
	}

	//	for(i=0;i<5;i++){
	//		GLdouble R=0,G=0,B=0;
	//		switch(wall_info[i]){
	//		case -1:
	//			R=0.2;
	//			G=0.2;
	//			B=0.2;
	//			break;
	//		default:
	//			R=1.0*0.01*(100-wall_info[i]);
	//			G=1.0*0.01*wall_info[i];
	//			B=0.0;
	//			break;
	//		}
	//	}
	for(i=0;i<WALLMAX;i++){
		GLdouble R=0,G=0,B=0;
		if(get_player()->mywall[i].count>0){
			R=0.0;
			G=1.0;
			B=0.0;

		}
		else{
			R=0.2;
			G=0.2;
			B=0.2;
		}


		glColor3d(R,G,B);//青指定

		rect_Draw2D(handle[14],850+(50*i)+shakeX,650+shakeY,34,34);//壁情報ランプ
	}
	image_DrawExRota(handle[14],948+shakeX,668+shakeY,0,1);//壁情報枠

}


