/*
 * Start.cpp
 *
 *  Created on: 2017/01/19
 *  Last edit: 2017/2/9
 *      Author: 横山・三木
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

static int s_flag = -1;
static int ro_flag = -1;
//static int nagasa = 300;//モデル間の長さ
static float angle = 0;
static vec3 position;
static int image[6]; //画像
static int Title;
//static char *str; //ジョブの名前に使用

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

static void CHG_role(Role name ,char *str);

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
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	start=false;
	teamnum[0]=teamnum[1]=0;
	get_teammemfaze()[0]=get_teammemfaze()[1]=0;
	startcount=0;
	get_player()->myteam=NoneTeam;
	for(int i=0;i<MAX_CLIENTS;i++)
		get_enemy()[i].myteam=NoneTeam;
	s_flag=-1;
	for(int i=0;i<MAX_CLIENTS;i++){
		teammemfaze[i]=0;
	}
}

void Start::DrawInitialize(){

	position.x = 0.0f;position.y = 0.0f ;position.z = 1200.0f;
	angle = 0;

	float aaa = 0.55;//aaa test
	char *name;
	handle[0]=image_Load("Data/image/スタート画面/button1.png");
	handle[1]=image_Load("Data/image/スタート画面/button3.png");
	handle[2]=image_Load("Data/image/スタート画面/button2.png");
	handle[3]=image_Load("Data/image/スタート画面/button4.png");
	handle[4]=image_Load("Data/image/スタート画面/button5.png");

	image[0]=image_Load("Data/image/スタート画面/stats_bow.png");//ボウガン
	image[1]=image_Load("Data/image/スタート画面/stats_gun.png");//ライフル
	image[2]=image_Load("Data/image/スタート画面/stats_gun2.png");//ガトリング
	image[3]=image_Load("Data/image/スタート画面/stats_ran.png");//槍
	image[4]=image_Load("Data/image/スタート画面/stats_mag.png");//魔法
	image[5]=image_Load("Data/image/スタート画面/stats_chg.png");//突撃

	Title=image_Load("Data/image/スタート画面/タイトル.png");//タイトル画面

	name=(char*)"Data/charamodel/char1/char1_exp_ver3.mqo";
	model[0] = mqoCreateModel( name, aaa );//モデル読み込み
	name=(char*)"Data/charamodel/char2/char2_exp_ver3.mqo";
	model[1] = mqoCreateModel( name, aaa );
	name=(char*)"Data/charamodel/char3/char3_exp_ver3.mqo";
	model[2] = mqoCreateModel( name, aaa );
	name=(char*)"Data/charamodel/char4/char4_exp_ver3.mqo";
	model[3] = mqoCreateModel( name, aaa );
	name=(char*)"Data/charamodel/char5/char5_exp_ver2.mqo";//ver3ありますが反応しません;;
	model[4] = mqoCreateModel( name, aaa );
	name=(char*)"Data/charamodel/char6/char6_exp_ver3.mqo";
	model[5] = mqoCreateModel( name, aaa );


}


void Start::DrawFinalize(){
	for(int i=0;i<(int)(sizeof handle/sizeof handle[0]);i++)
		image_free(handle[i]);
	for(int i=0;i<(int)(sizeof image/sizeof image[0]);i++)
		image_free(image[i]);
	for(int i=0;i<6;i++)
		mqoDeleteModel(model[i]);
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
		case -1:{
			if(get_mousebutton_count(LEFT_BUTTON)==2){
				s_flag = 0;
			}
			break;
		}
		case 1:{
			/*チーム選択*/
			/**/
			if(get_mousebutton_count(LEFT_BUTTON)==2){
				if(red.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<red.leftup.x+red.width&&
						red.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<red.leftup.y+red.height&&teamnum[0]<MAX_CLIENTS/2){
					get_player()->myteam=RedTeam;
					set_mousespeed(0.08+0.02*(smoothvalue-2));
					set_start(true);
					//s_flag = 0;
					/**/
				}else if(blue.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<blue.leftup.x+blue.width&&
						blue.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<blue.leftup.y+blue.height&&teamnum[1]<MAX_CLIENTS/2){

					get_player()->myteam=BlueTeam;
					set_mousespeed(0.08+0.02*(smoothvalue-2));
					set_start(true);
					//s_flag = 0;//キャラ選択へ
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
		case 0:{
			//キャラ選択
			if(150<get_mouseinfo().x&&get_mouseinfo().x<400&&
					50<get_mouseinfo().y&&get_mouseinfo().y<320 ){
				ro_flag = 0;
				if(get_mousebutton_count(LEFT_BUTTON)==2){

					get_player()->myrole=Crossbow;
					//set_start(true);

					s_flag = 1;
					//set_start(true);

					break;
				}
			}
			else if(150<get_mouseinfo().x&&get_mouseinfo().x<400&&
					350<get_mouseinfo().y&&get_mouseinfo().y<650 ){
				ro_flag = 1;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Rifle;
					s_flag = 1;
					//set_start(true);
					break;
				}
			}
			else if(500<get_mouseinfo().x&&get_mouseinfo().x<740&&
					50<get_mouseinfo().y&&get_mouseinfo().y<320 ){
				ro_flag = 2;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Gatling;
					s_flag = 1;
					//set_start(true);
					break;
				}
			}
			else if(500<get_mouseinfo().x&&get_mouseinfo().x<740&&
					350<get_mouseinfo().y&&get_mouseinfo().y<650 ){
				ro_flag = 3;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Spear;
					s_flag = 1;
					//set_start(true);
					break;
				}
			}
			else if(800<get_mouseinfo().x&&get_mouseinfo().x<1100&&
					50<get_mouseinfo().y&&get_mouseinfo().y<320 ){
				ro_flag = 4;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Magicstick;
					s_flag = 1;
					//set_start(true);
					break;
				}
			}
			else if(800<get_mouseinfo().x&&get_mouseinfo().x<1100&&
					350<get_mouseinfo().y&&get_mouseinfo().y<650 ){
				ro_flag = 5;
				if(get_mousebutton_count(LEFT_BUTTON)==2){
					get_player()->myrole=Magic;
					s_flag = 1;
					//set_start(true);
					break;
				}
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
		if(startcount>60*2){
			get_SceneMgr().ChangeScene(eScene_Game);/**/
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		//s_flag++;消してみた
	}
}

void Start::Draw() {

	if(get_start()==false){
		switch(s_flag){
		case -1:{
			startcanvas.view2D();
			//img_DrawXY(Title,0,0,1200,700);
			image_DrawExRota(Title,600,350,0,2);
			break;
		}
		case 0:{
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
			gluLookAt( position.x, position.y, position.z,
					0, 0.0f, 0,
					0.0f, 1.0f, 0.0f);

			/*移動関連これより下 移動関係関数,描画 の順番*/

			glPushMatrix();//保存
			glTranslatef(-600,300,10);//移動
			if(ro_flag == 0) {
				glRotatef(angle,0, 1, 0);
			}
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

			startcanvas.view2D();
			if(ro_flag >= 0) {

				int img_w = 300;
				int img_h = 300;

				/*ステータス表示*/
				if(ro_flag < 4)
					img_DrawXY(image[ro_flag],get_mouseinfo().x+100,get_mouseinfo().y-80,img_w,img_h);
				else
					img_DrawXY(image[ro_flag],get_mouseinfo().x-350,get_mouseinfo().y-80,img_w,img_h);
			}
			/*外枠*/

			glMatrixMode(GL_PROJECTION);//投影変換行列
			glPushMatrix();//保存
			//if(get_player()->myteam == BlueTeam)
			//	glColor3d(0,0,0.65);
			//else
			//	glColor3d(0.65,0.05,0);
			glColor3d(0,0.45,0);//緑色のハズ
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
		case 1:{
			startcanvas.view2D();

			glColor3d(0,0,0);

			img_DrawXY(handle[0],0,0,1200,700);
			img_DrawXY(handle[4],600-200,200,400,100);
			glPushMatrix();
			glColor3d(1,1,1);

			Mozi_DrawM2(280,90,0.7,MOZI_HGMINTYOE,"マウス感度調整バー");
			Mozi_DrawM2(120,400,0.65,MOZI_HGMINTYOE,"赤チーム(%d/4)",teamnum[0]);
			Mozi_DrawM2(720,400,0.65,MOZI_HGMINTYOE,"青チーム(%d/4)",teamnum[1]);
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);

			//glColor3d(1,0,0);
			image_DrawExRota(handle[1],red.leftup.x+red.width/2,red.leftup.y+red.height/2,0,0.5);
			//glColor3d(0,0,1);
			image_DrawExRota(handle[2],blue.leftup.x+blue.width/2,blue.leftup.y+blue.height/2,0,0.5);
			//glColor3d(0,0,0);
			image_DrawExRota(handle[4],600,250,0,1);
			image_DrawExRota(handle[3],smooth.leftup.x+smooth.width/2,smooth.leftup.y+smooth.height/2,0,1);


			break;
		}
		}
	}else{
		startcanvas.view2D();

		//glPushMatrix();

		glColor3d(0,0,0);
		Mozi_DrawM2(100,100,0.7,MOZI_HGMINTYOE,"赤：%d人/4人 ",teamnum[0]);
		Mozi_DrawM2(600,100,0.7,MOZI_HGMINTYOE,"青：%d人/4人 ",teamnum[1]);
		//Mozi_DrawM2(300,500,0.8,MOZI_HGMINTYOE,"LOL");
		glColor3d(0,0,0);
		//		for(int i=0;i<MAX_CLIENTS;i++){
		//
		//
		//			if(i==get_player()->myid){
		//
		//			}
		//			else{
		//				CHG_role(get_enemy()[i].myrole,sss);
		//				Mozi_DrawM2(600,200+100*teamnum[1],0.5,MOZI_HGMINTYOE,"%s %s %s",get_clients()[i].name,get_enemy()[i].myteam==RedTeam?"赤":get_enemy()[i].myteam==BlueTeam?"青":"未決定",sss);
		//			}
		//			//printf("%s\n",sss);
		//		}
		char sss[80];
		int nowrednum=0,nowbluenum=0;
		for(int i=0;i<MAX_CLIENTS;i++){
			if(i==get_player()->myid){

				if(get_player()->myteam==RedTeam){
					CHG_role(get_player()->myrole,sss);
					Mozi_DrawM2(100,200+100*nowrednum,0.5,MOZI_HGMINTYOE,"%s %s %s",get_clients()[i].name,get_player()->myteam==RedTeam?"赤":get_player()->myteam==BlueTeam?"青":"未決定",sss);
					nowrednum++;
				}
				else if(get_player()->myteam==BlueTeam){
					CHG_role(get_player()->myrole,sss);
					Mozi_DrawM2(600,200+100*nowbluenum,0.5,MOZI_HGMINTYOE,"%s %s %s",get_clients()[i].name,get_player()->myteam==RedTeam?"赤":get_player()->myteam==BlueTeam?"青":"未決定",sss);
					nowbluenum++;
				}

			}
			if(get_enemy()[i].myteam==RedTeam){
				CHG_role(get_player()->myrole,sss);
				Mozi_DrawM2(100,200+100*nowrednum,0.5,MOZI_HGMINTYOE,"%s %s %s",get_clients()[i].name,get_enemy()[i].myteam==RedTeam?"赤":get_enemy()[i].myteam==BlueTeam?"青":"未決定",sss);
				nowrednum++;
			}
			else if(get_enemy()[i].myteam==BlueTeam){
				CHG_role(get_enemy()[i].myrole,sss);
				Mozi_DrawM2(600,200+100*nowbluenum,0.5,MOZI_HGMINTYOE,"%s %s %s",get_clients()[i].name,get_enemy()[i].myteam==RedTeam?"赤":get_enemy()[i].myteam==BlueTeam?"青":"未決定",sss);
				nowbluenum++;
			}
			//glPopMatrix();
			//glDisable(GL_DEPTH_TEST);


		}
	}
}
void CHG_role(Role name ,char *str){

	switch(name){
	case Crossbow:{
		strcpy(str,"弩兵");
		break;
	}
	case Rifle:{
		strcpy(str,"狙撃兵");
		break;
	}
	case Gatling:{
		strcpy(str,"銃火器兵");
		break;
	}
	case Spear:{
		strcpy(str,"槍兵");
		break;
	}
	case Magicstick:{
		strcpy(str,"魔法使い");
		break;
	}
	case Magic:{
		strcpy(str,"獣人兵");
		break;
	}
	default:{
		puts("人数待ち画面:ジョブがおかしいです");
		break;
	}
	}

}

