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


#include <SDL/SDL.h>

#define WALLMAX 5

static int count=0;
static bool wrap = false;

typedef struct {
	int count;
	object wall;
}Wall;

Wall mywall[WALLMAX];
SDL_Thread *thr;

///ここから//////
//#include <opencv/cv.h>
//#if defined(WIN32)
//#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"get_mainfps()CRTStartup\"")
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
OBB playercollider;

//ライトの位置
//z軸だけなぜか符号が逆
static GLfloat lightpos[] 		 = {20.0, 10.0, 0,1};	//光源の位置
static GLfloat lightDiffuse[3]  = {1.0,  1.0, 1.0}; 	//拡散光
static GLfloat lightAmbient[3]  = {1.0,  1.0, 1.0};		//環境光
static GLfloat lightSpecular[3] = {1.0,  1.0, 1.0}; 	//鏡面光

//static GLfloat ground[][4] = {
//		{ 0.6, 0.6, 0.6, 1.0 },
//		{ 0.3, 0.3, 0.3, 1.0 }
//};

bullet playerbullet;
GLuint m_iFBODepth;        //!< 光源から見たときのデプスを格納するFramebuffer object
GLuint m_iTexDepth;        //!< m_iFBODepthにattachするテクスチャ
double m_fDepthSize[2];   //!< デプスを格納するテクスチャのサイズ

player::player() {
	// TODO 自動生成されたコンストラクター・スタブ
	move  	   =   0;
	dx 		   =   0;
	dy		   =   0;
	theta 	   =   0;
	position.x =   0;
	position.y =  10;
	position.z = -10;

	playercollider.setOBB(vec3(position.x,position.y,position.z),vec3(0.3f,3,0.3f));
	length = 0;


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

	gluPerspective(60.0, (double)w / (double)h,0.1,LOOK_DISTANT);			/*view volume 注意*/
	gluLookAt( position.x,position.y,position.z, 								//視点の位置x,y,z;
				position.x+lookat.x,position.y+lookat.y,position.z+lookat.z,	//視界の中心位置の参照点座標x,y,z
				0,1,0);

	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glMatrixMode(GL_MODELVIEW);
	playerbullet.Draw();
	DrawMyWall();
}

void player::Update(map mapobj){
	//ショット
	launchBullet();
	MouseMove();
	Move(mapobj.get_obj(),mapobj.get_objnum());
	set_wall();
	remove_wall();
}

//プレイヤーとあたり判定
bool player::Move(object *mapobject,int mapn){

	//移動速度定義(初期値7)
	const float movespeed = 7;


	//Calculate movement vectors
	//移動力ベクトルの計算?
	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
	vec3 right_dir   = vec3(-forward_dir.z, 0, forward_dir.x);

	static bool jumpflag    = false;
	static bool hitheadflag = false;
			bool upflag      = false;

	static float gravity;

	vec3 sampposition;
	//キャラクターの座標を格納
	sampposition = position;

	if(key_getmove(Left))
		sampposition -= right_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if(key_getmove(Right) )
		sampposition += right_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if(key_getmove(Forward))
		sampposition += forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if(key_getmove(Backward))
		sampposition -= forward_dir * movespeed * get_mainfps().fps_getDeltaTime();
	if((key_getmove(Jump)) && !jumpflag && !hitheadflag){
		jumpflag = true;
		gravity	 = 0;

	}

	if(jumpflag && !hitheadflag)
		sampposition.y += (8 * get_mainfps().fps_getDeltaTime());

	playerhead_collider    = position;
	playerhead_collider.y += 1;

	player_collider   = position;
	player_collider.x = sampposition.x;

	for(int i=0;i<mapn;i++){
		if(	movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=1    ){
			upflag=true;
			break;
		}
		if(i == mapn-1)
			position.x=player_collider.x;
	}

	player_collider 	= position;
	player_collider.z 	= sampposition.z;

	for(int i=0;i<mapn;i++){
		if(movechecker.LenOBBToPoint(mapobject[i],  player_collider)<=1){
			upflag = true;
			break;
		}
		if(i == mapn-1)
			position.z=player_collider.z;
	}

	for(int i=0;i<mapn;i++){
		if(movechecker.LenOBBToPoint(mapobject[i], playerhead_collider)<=1){
			upflag = false;
			break;
		}
	}

	for(int i=0;i<mapn;i++){
		if(movechecker.LenOBBToPoint(mapobject[i],  playerhead_collider)<=1){
			upflag = false;
			break;
		}
	}

	int i;
	if(upflag){
		for(int j=0;j<70;j++){
			player_collider		= position;
			player_collider.x 	= sampposition.x;
			player_collider.z 	= sampposition.z;
			//object 斜面約60°まで
			player_collider.y 	= sampposition.y + 0.001f*j;//0.01f;
			for(i=0;i<mapn;i++){
				if(	movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=1){
					break;
				}
				if(i == mapn-1)
					position=player_collider;
			}
			if(i == mapn)
				break;
		}
	}

	gravity += 0.3f;
	sampposition.y -= (gravity * get_mainfps().fps_getDeltaTime());

	player_collider 	= position;
	player_collider.y 	= sampposition.y;
	for(int i=0;i<mapn;i++){
		if(movechecker.LenOBBToPoint( mapobject[i],  playerhead_collider)<=1    ){
			hitheadflag = true;
		}

		if(movechecker.LenOBBToPoint( mapobject[i],  player_collider)<=1){
			jumpflag 	= false;
			hitheadflag = false;
			gravity 	= 0;
			break;
		}
		if(i==mapn-1)
			position.y=player_collider.y;
	}

	if(position.y<1){
		position.y=1;
		jumpflag = false;
	}

	return false;

}

void player::set_wall(){
	if(key_getmove(Setwall) == 2)
		for(int i=0;i<WALLMAX;i++)
			if(mywall[i].count == 0){
				mywall[i].wall.setobject(position+vec3(lookat.x, lookat.y, lookat.z),vec3(4,4,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1));
				mywall[i].count++;
				break;
			}
}

void player::remove_wall(){

}

void player::DrawMyWall(){
	for(int i=0;i<WALLMAX;i++)
		if(mywall[i].count)
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


			//この値で初期視野に影響あり
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
	if(falag == 0){
		thr = SDL_CreateThread(thread, this);
		falag = 1;
	}
}

void player::Action()
{

}

//ショット
void player::launchBullet(){
	playerbullet.setInfo(position + vec3(lookat.x, lookat.y, lookat.z),vec3(cosf(angles.y)*sinf(angles.x), sinf(angles.y), cosf(angles.y)*cosf(angles.x)));
	playerbullet.Update();
}

player::~player() {
	// TODO Auto-generated destructor stub
}

