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

static bool start=true;
static int teammemfaze[MAX_CLIENTS];
static int startcount;

#define SMOOTHRANGEHALF 200
typedef struct{
	float x;
	float y;
}posi2;

typedef struct{
	posi2 leftup;
	float width,height;
}Buttonposi;

Buttonposi red={{200,500},200,100};
Buttonposi blue={{800,500},200,100};
Buttonposi smooth={{600-25,200},50,50};

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
	handle[0]=image_Load("Data/image/スタート画面/button1.png");
	handle[1]=image_Load("Data/image/スタート画面/button2.png");
	handle[2]=image_Load("Data/image/スタート画面/button3.png");
	handle[3]=image_Load("Data/image/スタート画面/button4.png");
	handle[4]=image_Load("Data/image/スタート画面/button5.png");
}

void Start::DrawFinalize(){
	for(int i=0;i<(int)(sizeof handle/sizeof handle[0]);i++)
		image_free(handle[i]);

}
void Start::Finalize(){

}

void Start::Update() {
	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_teammemfaze()[i]==1){
			teamnum[(i==get_player()->myid)?get_player()->myteam:get_enemy()[i].myteam]++;
			get_teammemfaze()[i]=2;

		}

	}
	if(get_start()==false){
		if(get_mousebutton_count(LEFT_BUTTON)==2){
			if(red.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<red.leftup.x+red.width&&
					red.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<red.leftup.y+red.height){//&&teamnum[0]<MAX_CLIENTS/2	){
				get_player()->myteam=RedTeam;
				set_mousespeed(0.08+0.02*(smoothvalue-2));
				get_player()->myrole=Gatling;
				set_start(true);
			}else if(blue.leftup.x<get_mouseinfo().x&&get_mouseinfo().x<blue.leftup.x+blue.width&&
					blue.leftup.y<get_mouseinfo().y&&get_mouseinfo().y<blue.leftup.y+blue.height){//&&teamnum[1]<MAX_CLIENTS/2){

				get_player()->myteam=BlueTeam;
				set_mousespeed(0.08+0.02*(smoothvalue-2));
				get_player()->myrole=Gatling;
				set_start(true);
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
	}else{
		if(teamnum[0]+teamnum[1]==MAX_CLIENTS)
			startcount++;
		if(startcount>60*2)
			get_SceneMgr().ChangeScene(eScene_Game);

	}

}

void Start::Draw() {
	if(get_start()==false){
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
