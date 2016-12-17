


#include "Game.h"

#include "bullet.h"
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
#include "sound.h"

#include "enemyPlayer.h"
#include "charaanimation.h"
#define PLAYERNUM 5


MQO_MODEL mqomodel[12];

player player1;
mob mober[10];

CanvasUI gamecanvas;
map mapobj;


Wall *allplayerwall [PLAYERNUM];

bool che=false;
checkObjectHit hitChecker;


enemyPlayer enemy;
chara_animation chara;

GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess = 65.0;


void Game::setInfoPlayerWall(){
	allplayerwall[0]=player1.get_mywall();
	for(int i=1;i<PLAYERNUM;i++)
		for(int j=0;j<WALLMAX;j++){

		}
}

//初期化
void Game::Initialize(){

	SoundInit();
	gamecanvas.Initialize();
	mapobj.Initialize();

	player1.Initialize(vec3(30,10,-10),1,Crossbow,RedTeam);
	chara.Initialize();
	//TODO
	//	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
	//		mober[i].Initialize(i,vec3(-10,2.5f,-5),1,100,1,30,10);

	enemy.Initialize();
}

void Game::DrawInitialize(){
	//mqoInitは1回だけでいい模様
	mqoInit();

	gamecanvas.DrawInitialize();
	mapobj.DrawInitialize();
	player1.DrawInitialize();

	chara.DrawInitialize();
	char *flname=(char*)"Data/charamodel/char1/char1_exp_ver2.mqo";
	mqomodel[0]=mqoCreateModel(flname,0.0035);

	flname=(char*)"Data/charamodel/char2/一人称/char2_firstside_shoot.mqo";
	mqomodel[1]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_firstside_shooted.mqo";
	mqomodel[2]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char4/char4_firstside_shooted.mqo";
	mqomodel[3]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char5/char5_firstside_shooted.mqo";
	mqomodel[4]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_firstside_shooted.mqo";
	mqomodel[5]=mqoCreateModel(flname,0.0035);


	flname=(char*)"Data/charamodel/char1/char1_firstside_shooted.mqo";
	mqomodel[6]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_firstside_shooted.mqo";
	mqomodel[7]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char1/char1_firstside_shooted.mqo";
	mqomodel[8]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_head.mqo";
	mqomodel[9]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_ene_leg1.mqo";
	mqomodel[10]=mqoCreateModel(flname,0.0035);
	flname=(char*)"Data/charamodel/char2/char2_exp_ver2.mqo";
	mqomodel[11]=mqoCreateModel(flname,0.0035);

	//	flname=(char*)"Data/charamodel/char5/char5_exp.mqo";
	//	mqomodel[6]=mqoCreateModel(flname,0.0035);


	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
		mober[i].DrawInitialize((char*)"Data/charamodel/enemy1/enemy2_exp.mqo");



	enemy.DrawInitialize(mqomodel[0]);

}

void Game::DrawFinalize(){
	gamecanvas.DrawFinalize();
	mapobj.DrawFinalize();
	player1.DrawFinalize();
	//モデルの読み込みを最低限に抑えたため添字０の文だけでよい
	mober[0].DrawFinalize();
	chara.DrawFinalize();
}

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}


//更新
void Game::Update(){
	setInfoPlayerWall();

	//追加??
	//キャラクターの座標表示
	//	printf("x = %lf y = %lf z = %lf \n",player1.position.x,player1.position.y,player1.position.z);
	chara.Update();
	player1.Update();
	gamecanvas.Update();
	mapobj.Update();
//	enemy.enemybullet.EnemyPlayerToPlayer();
	//TODO
	//	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++){
	//		mober[i].Update();
	//		setMobSound(i,mober[i].position);
	//	}
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
	enemy.Draw();
	mapobj.Draw();
	chara.Draw();
	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
		mober[i].Draw();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPushMatrix();


	glColor3f(0.5,0.5,0.5);

	for(int i=0;i<12;i++){

		glPushMatrix();
		if(i>=6)
			glTranslated(5+(i-6)*5,1,-20);
		else
			glTranslated(5+i*5,1,-24);
		glRotated(180,0,1,0);

		mqoCallModel(mqomodel[i]);
		glPopMatrix();
	}


	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glPopMatrix();

	//////////////////3dここまで///////////////

	gamecanvas.view2D();

	gamecanvas.Draw();

	glPopMatrix();// 現在のモデルビュー行列を保存
}

//マップクラスのアドレスを返す関数
map *get_mapobj(){
	return &mapobj;
}

Wall **get_allplayerwall(){
	return allplayerwall;
}
player *get_player(){
	return &player1;
}
mob *get_mober(){
	return mober;
}
int get_mobernum(){
	return (int)(sizeof(mober)/sizeof(mober[0]));
}


enemyPlayer *get_enemy(){
	return &enemy;
}

