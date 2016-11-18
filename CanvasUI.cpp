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


}

//描画関連の初期化
void CanvasUI::DrawInitialize(){
	handle[0]=image_Load("Data/image/capture2.png");

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

}


//毎フレーム描画
void CanvasUI::Draw() {
	image_DrawExRota(handle[0],500,200,0,1);
}


