/*
 * player.cpp
 *
 *  Created on: 2016/09/12
 *      Author: user
 */

#include "player.h"
#include "GL/glut.h"
#include "SDL/SDL_opengl.h"

#include <math.h>
#include "key.h"
#include "mouse.h"
#include "fps.h"
#include "main.h"

#include "checkObjectHit.h"
#include "object.h"
#include "bullet.h"
#include "Game.h"
#include <SDL/SDL.h>
#include "image.h"
#include "sound.h"
#include "GLMetaseq.h"
#include "bullet.h"
#include "net_common.h"
#include "GL/glut.h"
#include "CanvasUI.h"

#define HP 100
#define BULLETNUM 10

static int count = 0;
static bool wrap = false;




SDL_Thread *thr;

int wallhandle;


bullet playerbullet;
object mywire;
bool drawmywire;    //Eキーを押してワイヤーの位置を表示するかどうか
static bool testcursol=false;  //カーソルの固定外し

static int modelcount;
static int shootedcount;
static int reloadcount;

float mousespeed = 0.1f;
///ここから//////
//#include <opencv/cv.h>
//#if defined(WIN32)
////#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"get_mainfps()CRTStartup\"")
//#  include "GL/glext.h"
//PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
//#elif defined(__APPLE__) || defined(MACOSX)
//#  include <GLUT/glut.h>
//#else
//#  define GL_GLEXT_PROTOTYPES
//#  include <GL/glut.h>
//#endif
///*
//** 光源
//*/
//static const GLfloat lightcol[] = { 1.0, 1.0, 1.0, 1.0 }; /* 直接光強度　　　　 */
//static const GLfloat lightdim[] = { 0.2, 0.2, 0.2, 1.0 }; /* 影内の拡散反射強度 */
//static const GLfloat lightblk[] = { 0.0, 0.0, 0.0, 1.0 }; /* 影内の鏡面反射強度 */
//static const GLfloat lightamb[] = { 0.1, 0.1, 0.1, 1.0 }; /* 環境光強度　　　　 */
//
///*
//** テクスチャ
//*/
//#define TEXWIDTH  512                                     /* テクスチャの幅　　 */
//#define TEXHEIGHT 512                                     /* テクスチャの高さ　 */
///*
//** 初期化
//*/
//static void init(void)
//{
//  /* テクスチャの割り当て */
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TEXWIDTH, TEXHEIGHT, 0,
//    GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
//
//  /* テクスチャを拡大・縮小する方法の指定 */
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//  /* テクスチャの繰り返し方法の指定 */
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//  /* 書き込むポリゴンのテクスチャ座標値のＲとテクスチャとの比較を行うようにする */
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//
//  /* もしＲの値がテクスチャの値以下なら真（つまり日向） */
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//
//  /* 比較の結果を輝度値として得る */
//  glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
//
//  /* テクスチャ座標に視点座標系における物体の座標値を用いる */
//  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//  glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//  glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//
//  /* 生成したテクスチャ座標をそのまま (S, T, R, Q) に使う */
//  static const GLdouble genfunc[][4] = {
//    { 1.0, 0.0, 0.0, 0.0 },
//    { 0.0, 1.0, 0.0, 0.0 },
//    { 0.0, 0.0, 1.0, 0.0 },
//    { 0.0, 0.0, 0.0, 1.0 },
//  };
//  glTexGendv(GL_S, GL_EYE_PLANE, genfunc[0]);
//  glTexGendv(GL_T, GL_EYE_PLANE, genfunc[1]);
//  glTexGendv(GL_R, GL_EYE_PLANE, genfunc[2]);
//  glTexGendv(GL_Q, GL_EYE_PLANE, genfunc[3]);
//
//  /* 初期設定 */
//  glClearColor(0.3, 0.3, 1.0, 1.0);
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_CULL_FACE);
//
//  /* 光源の初期設定 */
//  glEnable(GL_LIGHT0);
//  glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
//
//#if defined(WIN32)
//  glMultTransposeMatrixd =
//    (PFNGLMULTTRANSPOSEMATRIXDPROC)wglGetProcAddress("glMultTransposeMatrixd");
//#endif
//}

//////////////////////////////////
#define LOOK_DISTANT 1200           //見える距離


checkObjectHit movechecker;

//static GLfloat ground[][4] = {
//		{ 0.6, 0.6, 0.6, 1.0 },
//		{ 0.3, 0.3, 0.3, 1.0 }
//};


GLuint m_iFBODepth;        //!< 光源から見たときのデプスを格納するFramebuffer object
GLuint m_iTexDepth;        //!< m_iFBODepthにattachするテクスチャ
double m_fDepthSize[2];    //!< デプスを格納するテクスチャのサイズ

MQO_MODEL handmodel[nonemodel];

Wall *player::get_mywall(){
	return mywall;
}


player::player() {
	// TODO 自動生成されたコンストラクター・スタブ
	dx=0;
	dy=0;

}

void player::Initialize(vec3 pos,float ra){

	level=0;
	exp=0;
	playerbullet.bullet_Initialize();
	atktime=60;
	switch(myrole){
	case Crossbow:
		break;
	case Rifle:
		break;
	case Gatling:
		atktime=5;
		break;
	case Spear:
		break;
	case Magicstick:
		break;
	case Magic:
		break;
	default:
		break;
	}
	respawntime=0;
	position=pos;
	speed=7;
	hp=maxhp=100;
	atk=10;

	atkok=true;


	radi=ra;

	pers=60.0;
	for(int i=0;i<(int)(sizeof mywall/sizeof mywall[0]);i++)
		mywall[i].count=0;

	reset_Scroll();
	reset_ScrollLimit();
	set_ScrollMax(18);
	set_ScrollMin(0);

}
void player::DrawInitialize(Role setrole){
	playerbullet.bullet_DrawInitialize(setrole);

	wallhandle=image_Load("Data/image/2079.jpg");
	for(int i=0;i<(int)(sizeof mywall/sizeof mywall[0]);i++)
		mywall[i].wall.set_imgno(wallhandle,100);
	char *flname[nonemodel];
	myrole=setrole;
	switch(myrole){
	case Crossbow:
		flname[0]=(char*)"Data/charamodel/char1/char1_firstside_defalt.mqo";
		flname[1]=(char*)"Data/charamodel/char1/char1_firstside_shoot.mqo";
		flname[2]=(char*)"Data/charamodel/char1/char1_firstside_shooted.mqo";
		flname[3]=(char*)"Data/charamodel/char1/char1_firstside_reload.mqo";
		break;
	case Rifle:
		flname[0]=(char*)"Data/charamodel/char2/char2_firstside_defalt.mqo";
		flname[1]=(char*)"Data/charamodel/char2/char2_firstside_shoot.mqo";
		flname[2]=(char*)"Data/charamodel/char2/char2_firstside_shooted.mqo";
		flname[3]=(char*)"Data/charamodel/char2/char2_firstside_reload.mqo";
		break;
	case Gatling:
		flname[0]=(char*)"Data/charamodel/char3/char3_firstside_shoot.mqo";
		flname[1]=(char*)"Data/charamodel/char3/char3_firstside_shoot.mqo";
		flname[2]=(char*)"Data/charamodel/char3/char3_firstside_shoot.mqo";
		flname[3]=(char*)"Data/charamodel/char3/char3_firstside_shoot.mqo";
		break;
	case Spear:
		flname[0]=(char*)"Data/charamodel/char4/char4_firstside_defalt.mqo";
		flname[1]=(char*)"Data/charamodel/char4/char4_firstside_shoot.mqo";
		flname[2]=(char*)"Data/charamodel/char4/char4_firstside_shooted.mqo";
		flname[3]=(char*)"Data/charamodel/char4/char4_firstside_reload.mqo";
		break;
	case Magicstick:
		flname[0]=(char*)"Data/charamodel/char5/char5_firstside_defalt.mqo";
		flname[1]=(char*)"Data/charamodel/char5/char5_firstside_defalt.mqo";
		flname[2]=(char*)"Data/charamodel/char5/char5_firstside_shoot.mqo";
		flname[3]=(char*)"Data/charamodel/char5/char5_firstside_shoot.mqo";
		break;
	case Magic:
		flname[0]=(char*)"Data/charamodel/char6/char6_firstside_defalt.mqo";
		flname[1]=(char*)"Data/charamodel/char6/char6_firstside_shoot.mqo";
		flname[2]=(char*)"Data/charamodel/char6/char6_firstside_shooted.mqo";
		flname[3]=(char*)"Data/charamodel/char6/char6_ene_shooted.mqo";
		break;
	default:
		break;
	}
	for(int i=0;i<nonemodel;i++)
		handmodel[i]=mqoCreateModel(flname[i],0.0035);
	//	char *flname=(char*)"Data/charamodel/char2/char2_firstside_shooted.mqo";
	//char *flname=(char*)"Data/charamodel/char3/char3_firstside_shoot.mqo"
	//char *flname=(char*)"Data/charamodel/char4/char4_firstside_shooted.mqo";;

	//	handmodel=mqoCreateModel(flname,0.0010);
}

void player::DrawFinalize(){
	image_free(wallhandle);
}

void player::set_Pers(double next){
	pers=next;
}

void player::Draw(){


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	gluPerspective(pers, (double)w / (double)h,0.1,LOOK_DISTANT);/*view volume 注意*/
	gluLookAt( position.x,position.y+0.5f,position.z, // 視点の位置x,y,z;
			position.x+lookat.x, position.y+0.5f+lookat.y,position.z+lookat.z,   // 視界の中心位置の参照点座標x,y,z
			0,1,0);


	//	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	//	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	//	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	//	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);


	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	//glTranslatef(position.x-0.1,position.y+0.48f,position.z+0.3);
	glTranslatef(position.x,position.y+0.5f,position.z);
	glRotated(angles.x* 180 /M_PI ,0,1,0);
	glRotated(-angles.y* 180 /M_PI ,1,0,0);
	mqoCallModel(handmodel[nowpoze]);
	glPopMatrix();
	DrawMyWallWire();
	DrawMyWall();


	get_mapobj()->Draw();



	playerbullet.Draw();

}

void player::Update(){

	dead();

	if(modelcount>0)
		modelcount--;
	if(shootedcount>0)
		shootedcount--;
	if(reloadcount>0)
		reloadcount--;


	if(shootedcount>0&&playerbullet.launchbulletcount<=playerbullet.reloadmax)
		nowpoze=shootedmodel;
	else if(reloadcount>0)
		nowpoze=reloadmodel;
	else if(modelcount>0)
		nowpoze=shootmodel;
	else
		nowpoze=defaultmodel;

	if(key_getmove(Reload)==2&&playerbullet.launchbulletcount!=0)
		reloadcount=60*3;

	atk=level*10+10;
	setPlayerListen(position,vec3(sinf(angles.x), 0, cosf(angles.x)));
	playerbullet.Update();
	playerbullet.PlayerToEnemy();

	launchBullet();
	if(myteam==RedTeam)
		playerbullet.HitObj(BlueTeam,atk);
	else
		playerbullet.HitObj(RedTeam,atk);
	playerbullet.PlayerToMob();

	MouseMove();
	Move(get_mapobj()->get_obj(),get_mapobj()->get_objnum(),get_mywall());
	set_wall();
	remove_wall();
	static vec3 nowdel;
	nowdel=get_player()->delmove;
	get_player()->position+=nowdel;
	get_player()->delmove=vec3(0,0,0);

	if(key_getmove(Test)==3)
		testcursol=!testcursol;

	set_Pers(60-3*get_mousebutton_count(MIDDLE_BUTTON_SCROLL));
}
//プレイヤーとあたり判定
bool player::Move(object *mapobject,int mapn,Wall *playerwall){





	const float movespeed = speed;


	// Calculate movement vectors
	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
	vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);

	static bool jumpflag=false;
	static bool hitheadflag=false;


	static float gravity;

	vec3 sampposition;
	sampposition=position;
	if(progress_time==0){
		if(key_getmove(Left))
			sampposition -= right_dir * movespeed * get_mainfps().fps_getDeltaTime();
		if(key_getmove(Right) )
			sampposition += right_dir * movespeed * get_mainfps().fps_getDeltaTime();
		if(key_getmove(Forward))
			sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
		if(key_getmove(Backward))
			sampposition -= forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
		if(key_getmove(Left)||key_getmove(Right)||key_getmove(Forward)||key_getmove(Backward)){
			modelcount=60*2;
		}
	}else if(progress_time>0)
		modelcount=0;

	playerfoot_collider=position;
	playerfoot_collider.y-=0.7;

	bool foothit;
	foothit=movechecker.sethitcheck(mapn, mapobject,playerfoot_collider,0.5f);

	if((key_getmove(Jump))&&!jumpflag&&!hitheadflag){
		jumpflag=true;
		gravity=0;

	}


	//ジャンプ
	if(jumpflag&&!hitheadflag)
		sampposition.y += (8 * get_mainfps().fps_getDeltaTime());

	playerhead_collider=position;
	playerhead_collider.y+=1;



	//x座標における補正
	player_collider=position;
	player_collider.x=sampposition.x;

	//坂道登るフラグ
	bool upflag=false;
	bool upwall=false;
	bool hitmap=false;
	bool hitwall=false;

	int hitnum=0;
	//オブジェクトとの当たり判定
	for(int i=0;i<mapn;i++){
		if(movechecker.LenOBBToPoint(mapobject[i],  player_collider) <= radi){
			//if(movechecker.LenOBBToPoint(mapobject[i],  player_collider) <= radi || movechecker.LenOBBToPoint_move(mapobject[i],  player_collider) <= radi){
			upflag = true;
			hitmap = true;
			hitnum = i;			//衝突したオブジェクトを判定
			goto brex;
		}


		//else
		//hitnum = 0;
	}

	//hitnum = 0;
	for(int k=0;k<MAX_CLIENTS;k++)
		//プレイヤーが生成した壁との当たり判定
		for(int j=0;j<WALLMAX;j++){

			if(k==myid){
				if(playerwall[j].count>0)
					if(	movechecker.LenOBBToPoint( playerwall[j].wall, player_collider)<=radi){
						hitwall=true;
						upwall=true;
						goto brex;
					}
			}else{
				if(get_enemy()[k].mywall[j].count>0)
					if(	movechecker.LenOBBToPoint( get_enemy()[k].mywall[j].wall, player_collider)<=radi){
						hitwall=true;
						upwall=true;
						goto brex;

					}
			}

		}
	brex:


	//動作確認??
	//printf("upflag = %d hitmap = %d upwall = %d hitwall = %d\n",upflag,hitmap,upwall,hitwall);

	//オブジェクトにも壁にも当たっていないとき
	if(!hitmap && !hitwall){
		//何の処理??
		position.x = player_collider.x;
	}
	else{
		hitmap  = false;
		hitwall = false;
	}

	//動作確認??
	//printf("player_collider.z = %lf\n",player_collider.z);


	//z座標における補正

	player_collider=position;
	player_collider.z=sampposition.z;

	for(int i=0;i<mapn;i++)
		if(	movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=radi){
			upflag=true;
			hitmap=true;
			goto brez;
		}



	for(int k=0;k<MAX_CLIENTS;k++)
		for(int j=0;j<WALLMAX;j++){

			if(k==myid){
				if(playerwall[j].count>0)
					if(	movechecker.LenOBBToPoint( playerwall[j].wall, player_collider)<=radi){
						hitwall=true;
						upwall=true;
						goto brez;
					}
			}else
				if(get_enemy()[k].mywall[j].count>0)
					if(	movechecker.LenOBBToPoint( get_enemy()[k].mywall[j].wall, player_collider)<=radi){
						hitwall=true;
						upwall=true;
						goto brez;
					}
		}

	brez:

	if(!hitmap&&!hitwall)
		position.z=player_collider.z;
	else{
		hitmap=false;
		hitwall=false;
	}


	//if(!hitmap)
	//hitnum = -1;

	//動作確認




	//動作確認



	//	//頭衝突時
	//	for(int i=0;i<mapn;i++){
	//		if(	movechecker.LenOBBToPoint( mapobject[i],  playerhead_collider)<=1    ){
	//			upflag=false;
	//			break;
	//		}
	//	}


	int i;
	if(foothit){
		if(upflag&&!upwall)
			for(int j=0;j<100;j++){
				player_collider=position;
				player_collider.x=sampposition.x;
				player_collider.z=sampposition.z;
				//object 斜面約40°まで
				player_collider.y=sampposition.y+0.001f*j;//0.01f;
				for(i=0;i<mapn;i++){
					if(	movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=radi){
						break;
					}
					if(i==mapn-1)
						position=player_collider;
				}
				//for文の最後で++されてしまうため==
				if(i==mapn)
					break;
			}

		//	}else if(upflag){
		//		for(int i=0;i<500;i++)
		//			for(int j=0;j<8;j++){
		//				player_collider=position;
		//
		//				switch(i){
		//				case 0:
		//					player_collider.x+=0.001f*i;
		//					break;
		//				case 1:
		//					player_collider.x-=0.001f*i;
		//					break;
		//				case 2:
		//					player_collider.z+=0.001f*i;
		//					break;
		//				case 3:
		//					player_collider.z-=0.001f*i;
		//					break;
		//				case 4:
		//					player_collider.x+=0.001f*i;
		//					player_collider.z+=0.001f*i;
		//					break;
		//				case 5:
		//					player_collider.x-=0.001f*i;
		//					player_collider.z+=0.001f*i;
		//					break;
		//				case 6:
		//					player_collider.x-=0.001f*i;
		//					player_collider.z-=0.001f*i;
		//					break;
		//				case 7:
		//					player_collider.x+=0.001f*i;
		//					player_collider.z-=0.001f*i;
		//					break;
		//
		//				}
		//				if(!movechecker.sethitcheck(mapn,mapobject,player_collider,radi)){
		//					position=player_collider;
		//					break;
		//				}
		//			}
		//	}else if(upwall){
		//		for(int i=0;i<500;i++)
		//			for(int j=0;j<8;j++){
		//				player_collider=position;
		//
		//				switch(i){
		//				case 0:
		//					player_collider.x+=0.001f*i;
		//					break;
		//				case 1:
		//					player_collider.x-=0.001f*i;
		//					break;
		//				case 2:
		//					player_collider.z+=0.001f*i;
		//					break;
		//				case 3:
		//					player_collider.z-=0.001f*i;
		//					break;
		//				case 4:
		//					player_collider.x+=0.001f*i;
		//					player_collider.z+=0.001f*i;
		//					break;
		//				case 5:
		//					player_collider.x-=0.001f*i;
		//					player_collider.z+=0.001f*i;
		//					break;
		//				case 6:
		//					player_collider.x-=0.001f*i;
		//					player_collider.z-=0.001f*i;
		//					break;
		//				case 7:
		//					player_collider.x+=0.001f*i;
		//					player_collider.z-=0.001f*i;
		//					break;
		//
		//				}
		//				if(!movechecker.sethitcheck(WALLMAX,playerwall,player_collider,radi)){
		//					position=player_collider;
		//					break;
		//				}
		//			}
	}


	gravity+=0.3f;
	sampposition.y-=(gravity*get_mainfps().fps_getDeltaTime());

	//重力による下降処理
	//if(mapobject[hitnum].type != MOVE && mapobject[hitnum].speed.y >= 0 && movechecker.LenOBBToPoint(mapobject[hitnum],player_collider) >= radi){
	//if(down == 0){
	//printf("重力\n");
	//}



	//y座標の補正
	player_collider=position;
	player_collider.y=sampposition.y;

	//頭部分
	for(int i=0;i<mapn;i++){
		if(	movechecker.LenOBBToPoint( mapobject[i],  playerhead_collider)<=radi    ){
			hitheadflag=true;
		}

		if(	movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=radi){
			jumpflag=false;
			hitheadflag=false;
			hitmap=true;
			gravity=0;
			break;
		}
		if(i==mapn-1){

			for(int j=0;j<WALLMAX;j++){
				if(playerwall[j].count>0){

					if(	movechecker.LenOBBToPoint( playerwall[j].wall,  playerhead_collider)<=radi){
						hitheadflag=true;
					}

					if(	movechecker.LenOBBToPoint( playerwall[j].wall,  player_collider)<=radi){
						jumpflag=false;
						hitheadflag=false;
						hitmap=true;
						gravity=0;
						break;
					}

				}

				for(int k=0;k<MAX_CLIENTS;k++){
					if(k==myid)
						continue;
					if(get_enemy()[k].mywall[j].count>0){
						if(	movechecker.LenOBBToPoint( get_enemy()[k].mywall[j].wall,  playerhead_collider)<=radi){
							hitheadflag=true;
						}

						if(	movechecker.LenOBBToPoint( get_enemy()[k].mywall[j].wall,  player_collider)<=radi){
							jumpflag=false;
							hitheadflag=false;
							hitmap=true;
							gravity=0;
							goto label;
						}
					}

				}

				if(j==WALLMAX-1)
					hitmap=false;
			}
			label: ;
		}



	}





	if(hitmap==false)
		position.y=player_collider.y;
	else
		hitmap=true;

	if(position.y<radi){
		position.y=1;
		jumpflag=false;
	}


	return false;

}

void player::dead(){
	if(respawntime>RESPAWN_TIME){
		hp=maxhp;
		respawntime=0;
	}
	if(hp<=0)
		respawntime++;
}
void player::set_wall(){
	if(drawmywire&&get_mousebutton_count(RIGHT_BUTTON)==2){
		for(int i=0;i<WALLMAX;i++)
			if(mywall[i].count==0){
				progress_time++;
				break;
			}
	}
	if(progress_time>0)
		progress_time++;

	if(progress_time>WALL_SET){
		progress_time=0;
		for(int i=0;i<WALLMAX;i++)
			if(mywall[i].count==0){

				mywall[i].wall.setobject(position+vec3(lookat.x, lookat.y+0.1f, lookat.z)*4,vec3(4,4,0.5f),vec3(0, atan2(lookat.x,lookat.z)*180/M_PI, 0),vec4(0.5f,0.5f,0.5f,1));
				mywall[i].count++;
				break;
			}
	}


}

void player::remove_wall(){
	if(key_getmove(Removewall)==2)
		for(int i=0;i<WALLMAX;i++)
			if(mywall[i].count!=0)
				if(	movechecker.LenOBBToPoint( mywall[i].wall,  position+vec3(lookat.x, lookat.y, lookat.z)*4)<=1){
					progress_time--;
					break;
				}
	if(progress_time<0)
		progress_time--;


	for(int i=0;i<WALLMAX;i++)
		if(progress_time<-WALL_DELETE){
			progress_time=0;
			for(int i=0;i<WALLMAX;i++)
				if(mywall[i].count!=0)
					if(	movechecker.LenOBBToPoint( mywall[i].wall,  position+vec3(lookat.x, lookat.y, lookat.z)*4)<=1){
						mywall[i].count=0;
						break;
					}
		}

}
void player::DrawMyWall(){
	for(int i=0;i<WALLMAX;i++)
		if(mywall[i].count>0)
			mywall[i].wall.Draw();
}

void player::DrawMyWallWire(){
	if(key_getmove(Setwall)==2)
		drawmywire=!drawmywire;
	if(drawmywire)
		mywire.DrawWire(position+vec3(lookat.x, lookat.y+0.1f, lookat.z)*4,vec3(4,4,0.5f),vec3(0, atan2(lookat.x,lookat.z)*180/M_PI, 0));
}

int thread(void *data){

	player *info=(player*)data;
	while(1){

		if(testcursol){

		}

		if(get_player()->progress_time>0)
			glutWarpPointer(1200 / 2, 700 / 2);

		else if(!wrap) {
			float ww = 1200;//glutGet(GLUT_WINDOW_WIDTH);
			float wh = 700;//glutGet(GLUT_WINDOW_HEIGHT);



			info->dx=get_mouseinfo().x - ww /2;
			info->dy=get_mouseinfo().y- wh / 2;

			// Do something with dx and dy here

			// move mouse pointer back to the center of the window
			wrap = true;


			//このあたいで初期視野に影響あり


			info->angles.x -= info->dx * mousespeed*get_mainfps().fps_getDeltaTime();
			info->angles.y -= info->dy * mousespeed*get_mainfps().fps_getDeltaTime();

			if(info->angles.x < -M_PI)
				info->angles.x += M_PI * 2;
			else if(info->angles.x > M_PI)
				info->angles.x -= M_PI * 2;

			if(info->angles.y < -M_PI / 2+0.01f)
				info->angles.y = -M_PI / 2+0.01f;
			if(info->angles.y > M_PI / 2-0.01f)
				info->angles.y = M_PI / 2-0.01f;

			info->lookat.x = sinf(info->angles.x) * cosf(info->angles.y);
			info->lookat.y = sinf(info->angles.y);
			info->lookat.z = cosf(info->angles.x) * cosf(info->angles.y);

			count++;


			if(count%5==0)
				glutWarpPointer(1200 / 2, 700 / 2);
		}

		else
			wrap = false;

		SDL_Delay(10);
	}
	return 0;
}
void player::MouseMove()
{

	static int falag;
	if(falag==0){
		thr = SDL_CreateThread(thread, this);
		falag=1;
	}
}

void player::Action()
{

}

void player::launchBullet(){
	if(!atkok)
		atkcount++;
	//最後の弾だけ音がならないため
	static bool lastbullet=false;

	if(get_mousebutton_count(LEFT_BUTTON)>=2&&atkok&&playerbullet.reloadtime==0){

		playerbullet.setInfo(position+vec3(lookat.x, lookat.y+0.5f, lookat.z),vec3(cosf(angles.y)*sinf(angles.x), sinf(angles.y), cosf(angles.y)*cosf(angles.x)));


		if(playerbullet.launchbulletcount<playerbullet.reloadmax){
			shootedcount=20;
			playerbullet.launchbulletcount++;
			ChangeSE(1);
		}
		atkok=false;
	}
	//攻撃間隔
	if(atkcount>atktime){
		atkok=true;
		atkcount=0;
	}

	//	playerbullet.Update();
}

////死亡から復活まで
//void player::dead(){
//	static int deadcount;
//	deadcount++;
//
//}

//TODO
//ポインタなし？
bullet get_playerbullet(){
	return playerbullet;
}

player::~player() {
	// TODO Auto-generated destructor stub
}

void set_mousespeed(float set){
	mousespeed=set;
}

