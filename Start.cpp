/*
 * Start.cpp
 *
 *  Created on: 2017/01/19
 *      Author: c501506022
 */

#include "Start.h"
#include "image.h"
#include "CanvasUI.h"
#include "mouse.h"
#include "SceneMgr.h"
#include "GL/glut.h"
#include "main.h"
#include "Game.h"
#include "player.h"
#include "net_common.h"
#include "Letter.h"
#include "net_client.h"

CanvasUI startcanvas;
bool clickrole;
static float smoothvalue;

static int s_flag = 0;
static int ro_flag = -1;
//static int nagasa = 300;//モデル間の長さ
static float angle = 0;
static vec3 position;
static int image[6]; //画像

static bool start=true;
static int teammemfaze[MAX_CLIENTS];
static int startcount;

typedef struct{
	float x;
	float y;
}posi2;

typedef struct{
	posi2 leftup;
	float width,height;
}Buttonposi;

#define SMOOTHRANGEHALF 200

Buttonposi red={{200,500},200,100};
Buttonposi blue={{800,500},200,100};
Buttonposi smooth={{600-25,200},50,50};

MQO_MODEL model[6];

Start::Start(ISceneChanger* changer) : BaseScene(changer) {

}

Start::~Start() {
	// TODO Auto-generated destructor stub
}

bool get_start(){
	return start;
}
void set_start(bool set){
	start=set;
}
int *get_teammemfaze(){
	return teammemfaze;
}

void Start::Initialize(){
	//	ShowCursor( TRUE );
	start=false;
	teamnum[0]=teamnum[1]=0;
	get_teammemfaze()[0]=get_teammemfaze()[1]=0;
	startcount=0;
	get_player()->myteam=NoneTeam;
	for(int i=0;i<MAX_CLIENTS;i++)
		get_enemy()[i].myteam=NoneTeam;

}

void Start::DrawInitialize(){

	position.x = 0.0f;position.y = 0.0f ;position.z = 1200.0f;
	angle = 0;

	float aaa = 0.55;//aaa test
	char *name;
	handle[0]=image_Load("Data/image/スタート画面/button1.png");
	handle[1]=image_Load("Data/image/スタート画面/button2.png");
	handle[2]=image_Load("Data/image/スタート画面/button3.png");
	handle[3]=image_Load("Data/image/スタート画面/button4.png");
	handle[4]=image_Load("Data/image/スタート画面/button5.png");

	image[0]=image_Load("Data/image/スタート画面/stats_bow.png");//ボウガン
	image[1]=image_Load("Data/image/スタート画面/stats_gun.png");//ライフル
	image[2]=image_Load("Data/image/スタート画面/stats_gun2.png");//ガトリング
	image[3]=image_Load("Data/image/スタート画面/stats_ran.png");//槍
	image[4]=image_Load("Data/image/スタート画面/stats_mag.png");//魔法
	image[5]=image_Load("Data/image/スタート画面/stats_chg.png");//突撃

	name=(char*)"Data/charamodel/char1/char1_exp_ver2.mqo";
	model[0] = mqoCreateModel( name, aaa );//モデル読み込み
	//name=(char*)"Data/charamodel/enemy1/enemy2_exp.mqo";
	model[1] = mqoCreateModel( name, aaa );
	model[2] = mqoCreateModel( name, aaa );
	model[3] = mqoCreateModel( name, aaa );
	model[4] = mqoCreateModel( name, aaa );
	model[5] = mqoCreateModel( name, aaa );
}


void Start::DrawFinalize(){
	for(int i=0;i<(int)(sizeof handle/sizeof handle[0]);i++)
		image_free(handle[i]);

}
void Start::Finalize(){

}

void Start::Update() {
	/*新しい方*/
	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_teammemfaze()[i]==1){
			teamnum[(i==get_player()->myid)?get_player()->myteam:get_enemy()[i].myteam]++;
			get_teammemfaze()[i]=2;

		}

	}
	if(get_start()==false){
		switch(s_flag){
		case 0:{
			if(get_mousebutton_count(LEFT_BUTTON)==2){
				if(red.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<red.leftup.x+red.width&&
						red.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<red.leftup.y+red.height&&teamnum[0]<MAX_CLIENTS/2	){
					get_player()->myteam=RedTeam;
					set_mousespeed(0.08+0.02*(smoothvalue-2));
					//get_player()->myrole=Gatling;
					s_flag = 1;
					//set_start(true);
				}else if(blue.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<blue.leftup.x+blue.width&&
						blue.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<blue.leftup.y+blue.height&&teamnum[1]<MAX_CLIENTS/2){

					get_player()->myteam=BlueTeam;
					set_mousespeed(0.08+0.02*(smoothvalue-2));
					//get_player()->myrole=Gatling;
					s_flag = 1;//キャラ選択へ
					//set_start(true);//チーム待ち画面にジャンプ
				}
			}

			//mouse smooth
			if(get_mousebutton_count(LEFT_BUTTON)>=2){
				if(smooth.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<smooth.leftup.x+smooth.width&&
						smooth.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<smooth.leftup.y+smooth.height)
					clickrole=true;


			}
			else
				clickrole=false;

			float middle=smooth.leftup.x+smooth.width/2;
			if(clickrole)
				middle=(get_mouseinfo().x>600+SMOOTHRANGEHALF)?600+SMOOTHRANGEHALF:
						(get_mouseinfo().x<600-SMOOTHRANGEHALF)?600-SMOOTHRANGEHALF:get_mouseinfo().x;
			smooth.leftup.x=middle-smooth.width/2;
			smoothvalue=(middle-(600-SMOOTHRANGEHALF))/SMOOTHRANGEHALF*2;
			break;
		}
		case 1:{
			//キャラ選択
			//あとはプログラム的にキャラ選択するだけ
			//int sikaku_w = 100;int sikaku_h = 100;

			if(150<get_mouseinfo().x&&get_mouseinfo().x<400&&
					50<get_mouseinfo().y&&get_mouseinfo().y<320 ){
				ro_flag = 0;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole= Crossbow;
					set_start(true);
				}
				//puts("範囲");
			}
			else if(150<get_mouseinfo().x&&get_mouseinfo().x<400&&
					350<get_mouseinfo().y&&get_mouseinfo().y<650 ){
				ro_flag = 1;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Rifle;
					set_start(true);
				}
				//puts("範囲1");
			}
			else if(500<get_mouseinfo().x&&get_mouseinfo().x<740&&
					50<get_mouseinfo().y&&get_mouseinfo().y<320 ){
				ro_flag = 2;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Gatling;
					set_start(true);
				}
				//puts("範囲2");
			}
			else if(500<get_mouseinfo().x&&get_mouseinfo().x<740&&
					350<get_mouseinfo().y&&get_mouseinfo().y<650 ){
				ro_flag = 3;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Spear;
					set_start(true);
				}
				//puts("範囲3");
			}
			else if(800<get_mouseinfo().x&&get_mouseinfo().x<1100&&
					50<get_mouseinfo().y&&get_mouseinfo().y<320 ){
				ro_flag = 4;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Magicstick;
					set_start(true);
				}
				//puts("範囲4");
			}
			else if(800<get_mouseinfo().x&&get_mouseinfo().x<1100&&
					350<get_mouseinfo().y&&get_mouseinfo().y<650 ){
				ro_flag = 5;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Magic;
					set_start(true);
				}
				//puts("範囲5");
			}
			else{//非選択時
				angle = 0;
				ro_flag = -1;
			}

			break;
		}
		}
	}else{
		if(teamnum[0]+teamnum[1]==MAX_CLIENTS)
			startcount++;
		if(startcount>60*2)
			get_SceneMgr().ChangeScene(eScene_Game);/**/
		s_flag++;
	}
	//break;


}

void Start::Draw() {

	if(get_start()==false){
		switch(s_flag){
		case 0:{
			startcanvas.view2D();
			img_DrawXY(handle[0],0,0,1200,700);
			glColor3d(1,0,0);
			//rect_Draw2D(red.leftup.x,red.leftup.y,red.width,red.height);
			image_DrawExRota(handle[1],red.leftup.x+red.width/2,red.leftup.y+red.height/2,0,0.5);
			glColor3d(0,0,1);
			//rect_Draw2D(blue.leftup.x,blue.leftup.y,blue.width,blue.height);
			image_DrawExRota(handle[2],blue.leftup.x+blue.width/2,blue.leftup.y+blue.height/2,0,0.5);

			glColor3d(0,0,0);
			img_DrawXY(handle[4],600-200,200,400,100);
			//rect_Draw2D(smooth.leftup.x,smooth.leftup.y,smooth.width,smooth.height);
			image_DrawExRota(handle[3],smooth.leftup.x+smooth.width/2,smooth.leftup.y+smooth.height/2,0,1);
			//printf("%d\n",teamnum[0])
			break;
		}
		case 1:{
			angle++;
			if(angle > 360.0f){
				angle = 0.0f;
			}

			glMatrixMode(GL_PROJECTION);//投影変換行列

			glPushMatrix();//保存
			glLoadIdentity();//初期化
			float w = glutGet(GLUT_WINDOW_WIDTH);
			float h = glutGet(GLUT_WINDOW_HEIGHT);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			gluPerspective(60, (double)w / (double)h,0.1,1200);/*view volume 注意*/
			/*gluLookAt( position.x,position.y+0.5f,position.z, // 視点の位置x,y,z;
					position.x+lookat.x, position.y+0.5f+lookat.y,position.z+lookat.z,   // 視界の中心位置の参照点座標x,y,z
					0,1,0);*/
			gluLookAt( position.x, position.y, position.z,
					0, 0.0f, 0,
					0.0f, 1.0f, 0.0f);

			//glMatrixMode(GL_MODELVIEW);//モデルビュー変換行列
			/*移動関連これより下 移動関係関数,描画 の順番*/

			glPushMatrix();//保存
			glTranslatef(-600,300,10);//移動
			if(ro_flag == 0) {
				glRotatef(angle,0, 1, 0);
			}
			//else glMatrixMode(GL_PROJECTION);
			mqoCallModel( model[0] );

			glPushMatrix();//保存
			glTranslatef(-600,-300,10);
			if(ro_flag == 1) {glRotatef(angle,0, 1, 0);}
			mqoCallModel( model[1] );

			glPushMatrix();//保存
			glTranslatef(0,300,10);
			if(ro_flag == 2) {glRotatef(angle,0, 1, 0);}
			mqoCallModel( model[2] );

			glPushMatrix();//保存
			glTranslatef(0,-300,10);
			if(ro_flag == 3) {glRotatef(angle,0, 1, 0);}
			mqoCallModel( model[3] );

			glPushMatrix();//保存
			glTranslatef(600,300,10);
			if(ro_flag == 4) {glRotatef(angle,0, 1, 0);}
			mqoCallModel( model[4] );

			glPushMatrix();//保存
			glTranslatef(600,-300,10);
			if(ro_flag == 5) {glRotatef(angle,0, 1, 0);}
			mqoCallModel( model[5] );

			//printf("x:%d  y:%d\n",get_mouseinfo().x,get_mouseinfo().y);
			if(ro_flag >= 0) {
				startcanvas.view2D();
				int img_w = 300;
				int img_h = 300;

				/*
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();
				glLoadIdentity();
				glOrtho(0,w,h,0,-1,1);
				glMatrixMode(GL_MODELVIEW);
				 */

				/*ステータス表示*/
				if(ro_flag < 4)
					img_DrawXY(image[ro_flag],get_mouseinfo().x+100,get_mouseinfo().y-80,img_w,img_h);
				else
					img_DrawXY(image[ro_flag],get_mouseinfo().x-350,get_mouseinfo().y-80,img_w,img_h);
			}
			/*外枠*/
			startcanvas.view2D();
			glMatrixMode(GL_PROJECTION);//投影変換行列
			glPushMatrix();//保存
			if(get_player()->myteam == BlueTeam)
				glColor3d(0.65,0.05,0);
			else
				glColor3d(0,0,0.65);
			rect_Draw2D(0,0,170,700);
			rect_Draw2D(170,0,860,50);
			rect_Draw2D(400,50,100,270);
			rect_Draw2D(700,50,100,270);
			rect_Draw2D(170,320,860,30);
			rect_Draw2D(400,350,100,300);
			rect_Draw2D(700,350,100,300);
			rect_Draw2D(170,650,860,50);
			rect_Draw2D(1030,0,170,700);
			glPopMatrix();

			glPopMatrix();//取り出し
			break;
		}

		}
	}else{
		glColor3d(0,0,0);
		Mozi_DrawM2(100,100,0.8,MOZI_HGMINTYOE,"赤：%d人/4人 ",teamnum[0]);
		Mozi_DrawM2(100,300,0.8,MOZI_HGMINTYOE,"青：%d人/4人 ",teamnum[1]);
		for(int i=0;i<MAX_CLIENTS;i++){
			if(i==get_player()->myid)
				Mozi_DrawM2(700,100+100*i,0.5,MOZI_HGMINTYOE,"%s %s",get_clients()[i].name,get_player()->myteam==RedTeam?"赤":get_player()->myteam==BlueTeam?"青":"未決定");
			else
				Mozi_DrawM2(700,100+100*i,0.5,MOZI_HGMINTYOE,"%s %s",get_clients()[i].name,get_enemy()[i].myteam==RedTeam?"赤":get_enemy()[i].myteam==BlueTeam?"青":"未決定");
		}


	}


}


