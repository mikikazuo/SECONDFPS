


#include "Game.h"
#include "player.h"

#include "OBB.h"

#include "checkObjectHit.h"
#include "bullet.h"
#include "math.h"

#include "image.h"
#include "fps.h"

#include "glm.h"
#include "mouse.h"
#include "GLMetaseq.h"
#include "CanvasUI.h"
#include "map.h"



MQO_MODEL mqomodel;

player player1;

CanvasUI gamecanvas;
map mapobj;

bool che=false;
checkObjectHit hitChecker;




GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess = 65.0;


//初期化
void Game::Initialize(){
	gamecanvas.Initialize();
	mapobj.Initialize();

}

void Game::DrawInitialize(){
	gamecanvas.DrawInitialize();
	mapobj.DrawInitialize();

	mqoInit();
	char *flname=(char*)"Data/a/a.mqo";
	mqomodel=mqoCreateModel(flname,0.0035);
}

void Game::DrawFinalize(){
	gamecanvas.DrawFinalize();
	mapobj.DrawFinalize();
}

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}


//更新
void Game::Update(){
	player1.Update(mapobj);
	gamecanvas.Update();
	mapobj.Update();




}


void Square2D(int x1,int y1,int x2, int y2,float size){
	glLineWidth(size);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1,y1);
	glVertex2i(x2,y1);
	glVertex2i(x2,y2);
	glVertex2i(x1,y2);
	glEnd();
	glLineWidth(1);
}


//描画
void Game::Draw(){
	//BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	player1.Draw();

	mapobj.Draw();






	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPushMatrix();

	glColor3f(0.5,0.5,0.5);
	glTranslated(5,0,-8);
	glRotated(180,0,1,0);
	mqoCallModel(mqomodel );

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glPopMatrix();





	//////////////////3dここまで///////////////

	gamecanvas.view2D();

	gamecanvas.Draw();





	glPopMatrix();// 現在のモデルビュー行列を保存






}

