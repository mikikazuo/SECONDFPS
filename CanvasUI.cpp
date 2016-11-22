/*
 * CanvasUI.cpp
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#include "CanvasUI.h"
#include "GL/glut.h"
#include "image.h"

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

	if(time % 150 >= 149){
		dam = time;
		a -= 5+rand()%20;
		if(a<0) a=100;
	}else{
		//dam = 0;
	}

	if((time-dam)<30){
		if((time-dam)%3 == 0){
			shakeX = rand()%15-7;
			shakeY = rand()%15-7	;
		}
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
	rect_Draw2D(handle[9],1190-280*0.01*a+shakeX,10+shakeY,280*0.01*a,60);//ゲージ描画
	image_DrawExRota(handle[10],1050+shakeX,50+shakeY,0,1);//背景

	image_DrawExRota(handle[12],1050+shakeX,50+shakeY,0,1);//ハイライト、質感
	image_DrawExRota(handle[13],1050+shakeX,50+shakeY,0,1);//枠

	//image_DrawExRota(handle[3],75+shakeX,680+shakeY,0,2);//Lv

	glColor3d(1.0*0.01*(100-a),1.0*0.01*a,0);//緑指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[3],170+shakeX,650+shakeY,300*0.01*a,49);//ゲージ描画
	image_DrawExRota(handle[4],320+shakeX,662+shakeY,0,1);//playerHP

	int i;
	for(i=0;i<4;i++){
		image_DrawExRota(handle[1],350+55*i+shakeX,40+shakeY,0,1);
		image_DrawExRota(handle[2],850-55*i+shakeX,40+shakeY,0,1);
	}
}


