/*
 * Game.cpp
 *
 *  Last edit: 2017/2/10
 *      Author: 三木
 */


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
#include "net_common.h"
#include "enemyPlayer.h"

#include "main.h"
#include "Letter.h"
#include "net_client.h"
#include "Start.h"
#define PLAYERNUM 5



player player1;
mob mober[10];

CanvasUI gamecanvas;
map mapobj;
Team myteam;



bool che=false;
checkObjectHit hitChecker;


enemyPlayer enemy[MAX_CLIENTS];
chara_animation chara;

GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess = 65.0;


void Game::setInfoPlayerWall(){

	for(int i=1;i<PLAYERNUM;i++)
		for(int j=0;j<WALLMAX;j++){

		}
}

//初期化
void Game::Initialize(){

	SoundInit();
	gamecanvas.Initialize();
	mapobj.Initialize();

	player1.Initialize(vec3(30,10,-10),1);//(*get_argc()==2)?RedTeam:BlueTeam);

	//TODO
	//	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
	//		mober[i].Initialize(i,vec3(-10,2.5f,-5),1,100,1,30,10);

	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_player()->myid==i)
			continue;
		enemy[i].Initialize();
		enemy[i].myid=i;
	}

	//プレイヤーの壁情報初期化
	player1.wall = 0;
	get_chara().Initialize();
}

//描画初期化
void Game::DrawInitialize(){
	//mqoInitは1回だけでいい模様
	mqoInit();

	gamecanvas.DrawInitialize();
	mapobj.DrawInitialize();
	player1.DrawInitialize(Gatling);



	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
		mober[i].DrawInitialize((char*)"Data/charamodel/enemy1/enemy2_exp.mqo");


	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_player()->myid==i)
			continue;
		enemy[i].DrawInitialize(enemy[i].myrole);
	}
	get_chara().DrawInitialize();
	set_start(false);
}
//描画終了処理
void Game::DrawFinalize(){
	gamecanvas.DrawFinalize();
	mapobj.DrawFinalize();
	player1.DrawFinalize();
	//モデルの読み込みを最低限に抑えたため添字０の文だけでよい
	mober[0].DrawFinalize();
	chara.DrawFinalize();
	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_player()->myid==i)
			continue;
		enemy[i].DrawFinalize();
	}
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

//	printf("x = %lf y = %lf z = %lf \n",player1.position.x,player1.position.y,player1.position.z);
//	printf("wall = %d\n",player1.wall);



	player1.Update();
	gamecanvas.Update();
	//mapobj.Update();
	//	enemy.enemybullet.EnemyPlayerToPlayer();
	//TODO
	//	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++){
	//		mober[i].Update();
	//		setMobSound(i,mober[i].position);
	//	}
}


//四角形の描画
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

	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_player()->myid==i)
			continue;
		enemy[i].Draw();

	}

	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_player()->myid==i)
			continue;
		enemy[i].DrawName();
	}
//	mapobj.Draw();

	chara.Draw();
	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
		mober[i].Draw();


	glPushMatrix();


	glColor3f(0.5,0.5,0.5);



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

//プレイヤーのインスタンスを取得
player *get_player(){
	return &player1;
}

//mobのインスタンスを取得
mob *get_mober(){
	return mober;
}

//mobの数を取得
int get_mobernum(){
	return (int)(sizeof(mober)/sizeof(mober[0]));
}

//敵・味方のインスタンスを取得
enemyPlayer *get_enemy(){
	return enemy;
}

chara_animation get_chara(){
	return chara;
}
