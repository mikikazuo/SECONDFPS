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
//#include <X11/Xlib.h>
#include "Game.h"
#include <SDL/SDL.h>
#include "image.h"
#include "sound.h"

#define HP 100
#define BULLETNUM 10

static int count = 0;
static bool wrap = false;


Wall mywall[WALLMAX];

SDL_Thread *thr;

int wallhandle;

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

#define LOOK_DISTANT 150           //見える距離

checkObjectHit movechecker;

//static GLfloat ground[][4] = {
//		{ 0.6, 0.6, 0.6, 1.0 },
//		{ 0.3, 0.3, 0.3, 1.0 }
//};

bullet playerbullet;
GLuint m_iFBODepth;        //!< 光源から見たときのデプスを格納するFramebuffer object
GLuint m_iTexDepth;        //!< m_iFBODepthにattachするテクスチャ
double m_fDepthSize[2];   //!< デプスを格納するテクスチャのサイズ



Wall *player::get_mywall(){
	return mywall;
}


player::player() {
	// TODO 自動生成されたコンストラクター・スタブ
	dx = 0;
	dy = 0;

}
void player::Initialize(vec3 pos,float ra,int sethp,int setatk){

	playerbullet.bullet_Initialize();
	position=pos;
	hp=sethp;
	atk=setatk;
	bulletnum=BULLETNUM;
	radi=ra;
	//	for(int i=0;i<(int)(sizeof mywall/sizeof mywall[0]);i++)
	//		mywall[i].count=0;
}
void player::DrawInitialize(){
	wallhandle=image_Load("Data/image/2079.jpg");
	for(int i=0;i<(int)(sizeof mywall/sizeof mywall[0]);i++)
		mywall[i].wall.set_imgno(wallhandle,100);

}

void player::DrawFinalize(){
	image_free(wallhandle);
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

	gluPerspective(60.0, (double)w / (double)h,0.1,LOOK_DISTANT);/*view volume 注意*/
	gluLookAt( position.x,position.y,position.z, // 視点の位置x,y,z;
			position.x+lookat.x, position.y+lookat.y,position.z+lookat.z,   // 視界の中心位置の参照点座標x,y,z
			0,1,0);



	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);


	glMatrixMode(GL_MODELVIEW);
	playerbullet.Draw();
	DrawMyWall();

}

void player::Update(){
	setPlayerListen(position,vec3(sinf(angles.x), 0, cosf(angles.x)));
	launchBullet();
	playerbullet.HitObj();
	playerbullet.PlayerToMob();
	MouseMove();
	Move(get_mapobj()->get_obj(),get_mapobj()->get_objnum(),get_allplayerwall()[0]);
	set_wall();
	remove_wall();
}

//プレイヤーとあたり判定
//obj:オブジェクト
//mapn:オブジェクトの個数
//playerwall:プレイヤーが生成した壁
bool player::Move(object *mapobject,int mapn,Wall *playerwall){

	//キャラクターの移動速度
	const float movespeed = 7;

	//動作確認?
	//printf("mapn = %d\n",mapn);

	//printf("ABCDE\n");

	//Calculate movement vectors
	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
	vec3 right_dir   = vec3(-forward_dir.z, 0, forward_dir.x);

	static bool jumpflag    = false;
	static bool hitheadflag = false;

	//坂道登るフラグ
	bool upflag  = false;
	//キャラクターが生成した壁に上るフラグ
	bool upwall  = false;
	//オブジェクトとの当たり判定フラグ
	bool hitmap  = false;
	//プレイヤーが生成した壁との当たり判定フラグ
	bool hitwall = false;

	static float gravity;		//重力

	static int hitnum;			//プレイヤーと接触しているオブジェクトの番号

	//キャラクターの座標を格納
	vec3 sampposition;
	sampposition = position;

	//移動
	if(key_getmove(Left))
		sampposition -= right_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if(key_getmove(Right) )
		sampposition += right_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if(key_getmove(Forward))
		sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if(key_getmove(Backward))
		sampposition -= forward_dir * movespeed * get_mainfps().fps_getDeltaTime();

	//ジャンプ許可判定
	if((key_getmove(Jump)) && !jumpflag && !hitheadflag){
		jumpflag = true;
		gravity  = 0;
	}

	//ジャンプ実行(初期値8)
	if(jumpflag && !hitheadflag)
		sampposition.y += (8 * get_mainfps().fps_getDeltaTime());

	//頭部の当たり判定(y座標は+1)
	playerhead_collider	   = position;
	playerhead_collider.y += 1;


	//x座標における補正
	player_collider   = position;
	player_collider.x = sampposition.x;

	//オブジェクトとの当たり判定
	for(int i=0;i<mapn;i++)
		if(	movechecker.LenOBBToPoint(mapobject[i],  player_collider) <= radi){
			upflag = true;
			hitmap = true;
			hitnum = i;
			break;
		}

	//プレイヤーが生成した壁との当たり判定
	for(int j=0;j<WALLMAX;j++){
		if(playerwall[j].count > 0){
			if(	movechecker.LenOBBToPoint(playerwall[j].wall,player_collider) <= radi){
				upwall  = true;
				hitwall = true;
				break;
			}
		}
	}

	//動作確認??
	printf("upflag = %d hitmap = %d upwall = %d hitwall = %d\n",upflag,hitmap,upwall,hitwall);

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
	printf("player_collider.z = %lf\n",player_collider.z);

	//z座標における補正
	player_collider	  = position;
	player_collider.z = sampposition.z;

	//動作確認??
	printf("player_collider.z = %lf\n",player_collider.z);

	//オブジェクトとの当たり判定
	for(int i=0;i<mapn;i++)
		if(	movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=radi){
			upflag = true;
			hitmap = true;
			hitnum = i;
			break;
		}

	//プレイヤーが生成した壁との当たり判定
	for(int j=0;j<WALLMAX;j++)
		if(playerwall[j].count>0)
			if(	movechecker.LenOBBToPoint( playerwall[j].wall, player_collider)<=radi){
				hitwall = true;
				upwall  = true;
				break;
			}

	//オブジェクトにも壁にも当たっていなとき
	if(!hitmap && !hitwall)
		position.z = player_collider.z;
	else{
		hitmap  = false;
		hitwall = false;
	}

	if(!hitmap)
		hitnum = 0;

	printf("hitnum = %d\n",hitnum);


	//	//頭衝突時
	//	for(int i=0;i<mapn;i++){
	//		if(	movechecker.LenOBBToPoint( mapobject[i],  playerhead_collider)<=1    ){
	//			upflag=false;
	//			break;
	//		}
	//	}


	int i;
	if(upflag && !upwall){
		//なぜ700回ループ??
		for(int j=0;j<700;j++){
			player_collider	  = position;
			player_collider.x = sampposition.x;
			player_collider.z = sampposition.z;
			//object 斜面約60°まで
			player_collider.y = sampposition.y + 0.001f*j;//0.01f;
			for(i=0;i<mapn;i++){
				if(	movechecker.LenOBBToPoint(mapobject[i],  player_collider) <= radi){
					break;
				}
				if(i == mapn-1)
					position=player_collider;
			}
			//for文の最後で++(インクリメント)されてしまうため条件式に"=="を使用
			if(i == mapn)
				break;
		}
	}

	gravity += 0.3f;
	sampposition.y -= (gravity*get_mainfps().fps_getDeltaTime());


	//y座標の補正
	player_collider	  = position;
	player_collider.y = sampposition.y;

	//頭部
	for(int i=0;i<mapn;i++){
		//キャラクターの頭部とオブジェクトとの当たり判定
		if(movechecker.LenOBBToPoint(mapobject[i],playerhead_collider) <= radi){
			hitheadflag = true;
		}

		//キャラクターの頭部と生成された壁との当たり判定
		if(movechecker.LenOBBToPoint(mapobject[i],player_collider) <= radi){
			jumpflag 	= false;
			hitheadflag = false;
			hitmap 		= true;
			gravity 	= 0;
			break;
		}
		//最後のループ時
		if(i == mapn-1){
			for(int j=0;j<WALLMAX;j++){
				if(playerwall[j].count == 0)
					continue;

				//生成された壁と頭部との当たり判定
				if(	movechecker.LenOBBToPoint(playerwall[j].wall,playerhead_collider) <= radi){
					hitheadflag = true;
				}

				//生成された壁との当たり判定
				if(	movechecker.LenOBBToPoint(playerwall[j].wall,player_collider) <= radi){
					jumpflag	= false;
					hitheadflag	= false;
					hitmap		= true;
					gravity		= 0;
					break;
				}

				//最後のループ時
				if(j == WALLMAX-1){
					hitmap = false;
				}
			}
		}
	}

	//オブジェクトに当たっていないとき
	if(hitmap == false)
		position.y = player_collider.y;
	else
		hitmap = true;

	//何の処理??
	if(position.y < radi){
		position.y = 1;
		jumpflag   = false;
	}

	//動作確認??
	printf("upflag = %d hitmap = %d upwall = %d hitwall = %d\n",upflag,hitmap,upwall,hitwall);

	return false;

}

void player::set_wall(){
	if(key_getmove(Setwall)==2)
		for(int i=0;i<WALLMAX;i++)
			if(mywall[i].count==0){

				mywall[i].wall.setobject(position+vec3(lookat.x, lookat.y, lookat.z)*4,vec3(4,4,0.5f),vec3(0, atan2(lookat.x,lookat.z)*180/M_PI, 0),vec4(0.5f,0.5f,0.5f,1));
				mywall[i].count++;
				break;
			}



}
void player::remove_wall(){
	if(key_getmove(Removewall)==2)
		for(int i=0;i<WALLMAX;i++)
			if(mywall[i].count!=0)
				if(	movechecker.LenOBBToPoint(mywall[i].wall,  position+vec3(lookat.x, lookat.y, lookat.z)*4)<=1){
					mywall[i].count=0;
				}

}
void player::DrawMyWall(){
	for(int i=0;i<WALLMAX;i++)
		if(mywall[i].count>0)
			mywall[i].wall.Draw();
}

int thread(void *data){


	player *info=(player*)data;
	while(1){
		if(!wrap) {
			float ww = 1200;//glutGet(GLUT_WINDOW_WIDTH);
			float wh = 700;//glutGet(GLUT_WINDOW_HEIGHT);



			info->dx=get_mouseinfo().x - ww /2;
			info->dy=get_mouseinfo().y- wh / 2;

			// Do something with dx and dy here

			// move mouse pointer back to the center of the window
			wrap = true;


			//このあたいで初期視野に影響あり
			const float mousespeed = 0.1f;

			info->angles.x -= info->dx * mousespeed*get_mainfps().fps_getDeltaTime();
			info->angles.y -= info->dy * mousespeed*get_mainfps().fps_getDeltaTime();

			if(info->angles.x < -M_PI)
				info->angles.x += M_PI * 2;
			else if(info->angles.x > M_PI)
				info->angles.x -= M_PI * 2;

			if(info->angles.y < -M_PI / 2)
				info->angles.y = -M_PI / 2;
			if(info->angles.y > M_PI / 2)
				info->angles.y = M_PI / 2;

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
	if(get_mousebutton_count(LEFT_BUTTON)%10==1){
		playerbullet.setInfo(position+vec3(lookat.x, lookat.y, lookat.z),vec3(cosf(angles.y)*sinf(angles.x), sinf(angles.y), cosf(angles.y)*cosf(angles.x)));
		ChangeSE(1);
	}
		playerbullet.Update();
}

player::~player() {
	// TODO Auto-generated destructor stub
}

