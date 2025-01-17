/*
 * object.cpp
 *
 *  Created on: 2016/09/13
 *      Author: user
 */

#include "object.h"
#include "fps.h"
#include "image.h"
#include "main.h"
#include "checkObjectHit.h"
#include "Game.h"


//ライトの位置
static GLfloat lightpos[] 		 = {10.0, 10.0, 50,0 ,0}; /* 光源の位置 */
static GLfloat lightDiffuse[3]  = { 1.0,  1.0, 1.0  }; //拡散光
static GLfloat lightAmbient[3]  = { 1.0,  1.0, 1.0  }; //環境光
static GLfloat lightSpecular[3] = { 1.0,  1.0, 1.0  }; //鏡面光

double const texture_repos=0;

object::object() {

	this->imgno=-1;
}

//注）壁用　imgnoを変更しないため
void object::setobject(vec3 position,vec3 size,vec3 rota,vec4 color){
	this->m_Pos.x=position.x;
	this->m_Pos.y=position.y;
	this->m_Pos.z=position.z;

	m_Rota.x=rota.x;
	m_Rota.y=rota.y;
	m_Rota.z=rota.z;

	UpdateAxisAll();

	this->Radius.x=size.x;
	this->Radius.y=size.y;
	this->Radius.z=size.z;

	this->color[0]=color.x;
	this->color[1]=color.y;
	this->color[2]=color.z;
	this->color[3]=color.w;


}
object::object(vec3 position,vec3 size,vec3 rota,vec4 color) {
	// TODO 自動生成されたコンストラクター・スタブ

	this->m_Pos.x=position.x;
	this->m_Pos.y=position.y;
	this->m_Pos.z=position.z;

	m_Rota.x=rota.x;
	m_Rota.y=rota.y;
	m_Rota.z=rota.z;

	UpdateAxisAll();

	this->Radius.x=size.x;
	this->Radius.y=size.y;
	this->Radius.z=size.z;

	this->color[0]=color.x;
	this->color[1]=color.y;
	this->color[2]=color.z;
	this->color[3]=color.w;


	this->imgno=-1;

}

void object::set_imgno(int no,int imgsize){
	this->imgno=no;
	this->imgresize=imgsize;
}

//直方体
void object::make_cuboid(float width,float height,float depth)
{


	if(this->imgno!=-1){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,get_sa(imgno).no);
		glBegin(GL_QUADS);
		//前

		glNormal3f(0,0,1);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2],0);
		glVertex3f(width/2,height/2,depth/2+ texture_repos);
		glTexCoord2d(0,0);
		glVertex3f(-width/2,height/2,depth/2+ texture_repos);
		glTexCoord2d(0,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3]);
		glVertex3f(-width/2,-height/2,depth/2+ texture_repos);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2] ,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3] );
		glVertex3f(width/2,-height/2,depth/2+ texture_repos);

		//右
		glNormal3f(1,0,0);
		glTexCoord2d(depth*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2],0);
		glVertex3f(width/2+ texture_repos,height/2,-depth/2);
		glTexCoord2d(0,0);
		glVertex3f(width/2+ texture_repos,height/2,depth/2);
		glTexCoord2d(0,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3]);
		glVertex3f(width/2+ texture_repos,-height/2,depth/2);
		glTexCoord2d(depth*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2] ,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3] );
		glVertex3f(width/2+ texture_repos,-height/2,-depth/2);

		//左
		glNormal3f(-1,0,0);
		glTexCoord2d(depth*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2],0);
		glVertex3f(-width/2- texture_repos,height/2,depth/2);
		glTexCoord2d(0,0);
		glVertex3f(-width/2- texture_repos,height/2,-depth/2);
		glTexCoord2d(0,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3]);
		glVertex3f(-width/2- texture_repos,-height/2,-depth/2);
		glTexCoord2d(depth*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2] ,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3] );
		glVertex3f(-width/2- texture_repos,-height/2,depth/2);

		//後
		glNormal3f(0,0,-1);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2],0);
		glVertex3f(-width/2,height/2,-depth/2- texture_repos);
		glTexCoord2d(0,0);
		glVertex3f(width/2,height/2,-depth/2- texture_repos);
		glTexCoord2d(0,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3]);
		glVertex3f(width/2,-height/2,-depth/2- texture_repos);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2] ,height*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3] );
		glVertex3f(-width/2,-height/2,-depth/2- texture_repos);


		//上
		glNormal3f(0,1,0);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2],0);
		glVertex3f(width/2,height/2+ texture_repos,-depth/2);
		glTexCoord2d(0,0);
		glVertex3f(-width/2,height/2+ texture_repos,-depth/2);
		glTexCoord2d(0,depth*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3]);
		glVertex3f(-width/2,height/2+ texture_repos,depth/2);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2] ,depth*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3] );
		glVertex3f(width/2,height/2+ texture_repos,depth/2);


		//下
		glNormal3f(0,-1,0);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2],0);
		glVertex3f(width/2,-height/2- texture_repos,depth/2);
		glTexCoord2d(0,0);
		glVertex3f(-width/2,-height/2- texture_repos,depth/2);
		glTexCoord2d(0,depth*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3]);
		glVertex3f(-width/2,-height/2- texture_repos,-depth/2);
		glTexCoord2d(width*imgresize/(GLfloat)get_sa(imgno).oriX / get_sa(imgno).color[2] ,depth*imgresize/(GLfloat)get_sa(imgno).oriY / get_sa(imgno).color[3] );
		glVertex3f(width/2,-height/2- texture_repos,-depth/2);

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}else{

		// glColor3d(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
		//前
		//法線も回転してる
		glNormal3f(0,0,1);

		glVertex3f(width/2,height/2,depth/2);
		glVertex3f(-width/2,height/2,depth/2);
		glVertex3f(-width/2,-height/2,depth/2);
		glVertex3f(width/2,-height/2,depth/2);

		//右
		glNormal3f(1,0,0);
		glVertex3f(width/2,height/2,-depth/2);
		glVertex3f(width/2,height/2,depth/2);
		glVertex3f(width/2,-height/2,depth/2);
		glVertex3f(width/2,-height/2,-depth/2);




		//左
		glNormal3f(-1,0,0);
		glVertex3f(-width/2,height/2,depth/2);
		glVertex3f(-width/2,height/2,-depth/2);
		glVertex3f(-width/2,-height/2,-depth/2);
		glVertex3f(-width/2,-height/2,depth/2);




		//後
		glNormal3f(0,0,-1);
		glVertex3f(-width/2,height/2,-depth/2);
		glVertex3f(width/2,height/2,-depth/2);
		glVertex3f(width/2,-height/2,-depth/2);
		glVertex3f(-width/2,-height/2,-depth/2);




		//上
		glNormal3f(0,1,0);
		glVertex3f(width/2,height/2,-depth/2);
		glVertex3f(-width/2,height/2,-depth/2);
		glVertex3f(-width/2,height/2,depth/2);
		glVertex3f(width/2,height/2,depth/2);




		//下
		glNormal3f(0,-1,0);
		glVertex3f(width/2,-height/2,depth/2);
		glVertex3f(-width/2,-height/2,depth/2);
		glVertex3f(-width/2,-height/2,-depth/2);
		glVertex3f(width/2,-height/2,-depth/2);
		glEnd();

	}

}

void object::Draw(){
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glPopMatrix();

	glPushMatrix();
	/* 図形の色 (赤)  */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);

	glTranslatef(this->m_Pos.x,this->m_Pos.y,this->m_Pos.z);



	glRotated(m_Rota.x,1,0,0);
	glRotated(m_Rota.y,0,1,0);
	glRotated(m_Rota.z,0,0,1);



	make_cuboid(this->Radius.x,this->Radius.y,this->Radius.z);

	glPopMatrix();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	int rate;

	for(int i=0;i<3;i++){
		switch(i){
		case 0:
			glColor3d(1.0, 0.0, 0.0);
			rate=this->Radius.x;
			break;
		case 1:
			glColor3d(0.0, 0.0, 1.0);
			rate=this->Radius.y;
			break;
		case 2:
			glColor3d(0.0, 1.0, 0.0);
			rate=this->Radius.z;
			break;
		}

	//	Line3D(this->m_Pos.x,this->m_Pos.y,this->m_Pos.z,
		//		this->m_Pos.x+rate*this->m_NormaDirect[i].x,this->m_Pos.y+rate*this->m_NormaDirect[i].y,this->m_Pos.z+rate*this->m_NormaDirect[i].z);

	}
	glColor3d(1.0, 1.0, 1.0);
}

void object::DrawWire(vec3 position,vec3 size,vec3 rota){

	float width=size.x;
	float height=size.y;
	float depth=size.z;

	glPushMatrix();
	glTranslatef(position.x,position.y,position.z);
	glRotated(rota.x,1,0,0);
	glRotated(rota.y,0,1,0);
	glRotated(rota.z,0,0,1);

	glLineWidth(10);
    glColor3d(1.0, 1.0, 1.0);

	//前
	//法線も回転してる
	glBegin(GL_LINE_LOOP);
	glNormal3f(0,0,1);
	glVertex3f(width/2,height/2,depth/2);
	glVertex3f(-width/2,height/2,depth/2);
	glVertex3f(-width/2,-height/2,depth/2);
	glVertex3f(width/2,-height/2,depth/2);
	glEnd();

	//右
	glBegin(GL_LINE_LOOP);
	glNormal3f(1,0,0);
	glVertex3f(width/2,height/2,-depth/2);
	glVertex3f(width/2,height/2,depth/2);
	glVertex3f(width/2,-height/2,depth/2);
	glVertex3f(width/2,-height/2,-depth/2);
	glEnd();

	//左
	glBegin(GL_LINE_LOOP);
	glNormal3f(-1,0,0);
	glVertex3f(-width/2,height/2,depth/2);
	glVertex3f(-width/2,height/2,-depth/2);
	glVertex3f(-width/2,-height/2,-depth/2);
	glVertex3f(-width/2,-height/2,depth/2);
	glEnd();

	//後
	glBegin(GL_LINE_LOOP);
	glNormal3f(0,0,-1);
	glVertex3f(-width/2,height/2,-depth/2);
	glVertex3f(width/2,height/2,-depth/2);
	glVertex3f(width/2,-height/2,-depth/2);
	glVertex3f(-width/2,-height/2,-depth/2);
	glEnd();

	//上
	glBegin(GL_LINE_LOOP);
	glNormal3f(0,1,0);
	glVertex3f(width/2,height/2,-depth/2);
	glVertex3f(-width/2,height/2,-depth/2);
	glVertex3f(-width/2,height/2,depth/2);
	glVertex3f(width/2,height/2,depth/2);
	glEnd();
	//下
	glBegin(GL_LINE_LOOP);
	glNormal3f(0,-1,0);
	glVertex3f(width/2,-height/2,depth/2);
	glVertex3f(-width/2,-height/2,depth/2);
	glVertex3f(-width/2,-height/2,-depth/2);
	glVertex3f(width/2,-height/2,-depth/2);
	glEnd();
	glPopMatrix();
}

//移動
void object::move(float x,float y,float z){

	checkObjectHit player;

	static int flag;
	vec3 uppos=this->m_Pos;
	uppos.y+=1;
	object ownup(uppos,this->Radius,this->m_Rota,vec4(0.5f,0.5f,0.5f,0));

	//	vec3 underpos=this->m_Pos;
	//	underpos.y-=1;
	//	object ownunder(underpos,this->Radius,this->m_Rota,vec4(0.5f,0.5f,0.5f,0));
	//
	//	vec3 rightpos=this->m_Pos;
	//	rightpos.x+=1;
	//	object ownright(rightpos,this->Radius,this->m_Rota,vec4(0.5f,0.5f,0.5f,0));
	//
	//	vec3 leftpos=this->m_Pos;
	//	leftpos.x-=1;
	//	object ownleft(leftpos,this->Radius,this->m_Rota,vec4(0.5f,0.5f,0.5f,0));
	//
	//	vec3 forwardpos=this->m_Pos;
	//	forwardpos.z+=1;
	//	object ownforward(forwardpos,this->Radius,this->m_Rota,vec4(0.5f,0.5f,0.5f,0));
	//
	//	vec3 backpos=this->m_Pos;
	//	forwardpos.z-=1;
	//	object ownback(backpos,this->Radius,this->m_Rota,vec4(0.5f,0.5f,0.5f,0));



	if(player.LenOBBToPoint(ownup,get_player()->playerfoot_collider)<=1){
		get_player()->position.x+=x*get_mainfps().fps_getDeltaTime();
		get_player()->position.y+=y*get_mainfps().fps_getDeltaTime();
		get_player()->position.z+=z*get_mainfps().fps_getDeltaTime();
	}



}


//回転
void object::rotate(float x,float y,float z){

	this->m_Rota.x+=x*get_mainfps().fps_getDeltaTime();
	this->m_Rota.y+=y*get_mainfps().fps_getDeltaTime();
	this->m_Rota.z+=z*get_mainfps().fps_getDeltaTime();

	UpdateAxisAll();

}
object::~object() {
	// TODO Auto-generated destructor stub
}


void object::Line3D(float x1,float y1,float z1,float x2,float y2,float z2){
	//線幅
	glLineWidth(5.0);
	//線
	glBegin(GL_LINES);


	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glEnd();
	glLineWidth(1.0);
}

//オブジェクトの座標を取得する関数
vec3 object::get_m_Pos(){
	return this->m_Pos;
}

//オブジェクトの座標を書き換える関数
void object::set_m_Pos(vec3 Pos){
	this->m_Pos = Pos;
}

//オブジェクトの回転を取得する関数
vec3 object::get_m_Rot(){
	return this->m_Rota;
}
//オブジェクトの回転を変更する関数
void object::set_m_Rot(vec3 Rot){
	this->m_Rota=Rot;
	UpdateAxisAll();
}

//オブジェクトの各軸方向の長さを取得する関数
vec3 object::get_Radius(){
	return this->Radius;
}

//オブジェクトを特定の座標間で移動させる関数(x軸方向)
void object::x_side_move(float speed,float left,float right,int dir){
	static int x_dir = dir;

	vec3 temp = get_m_Pos();	//オブジェクトの座標
	vec3 rad  = get_Radius();	//オブジェクトの各軸方向の長さ

	//オブジェクトのタイプを設定
	type = MOVE;

	//進行方向方向を管理
	if((x_dir == 1 && temp.x + rad.x/2 >= right) || (x_dir == -1 && temp.x + rad.x/2 <= left)){
		//if((x_dir == 1 && rad.x/2 >= right) || (x_dir == -1 && rad.x/2 <= left)){
		x_dir *= -1;
	}

	//進行方向を格納
	this->speed.x = speed * x_dir;

	//移動
	move(speed * x_dir,0,0);
}

//オブジェクトを特定の座標間で移動させる関数(z軸方向)
void object::z_side_move(float speed,float left,float right,int dir){
	static int z_dir = dir;

	vec3 temp = get_m_Pos();	//オブジェクトの座標
	vec3 rad  = get_Radius();	//オブジェクトの各軸方向の長さ

	//オブジェクトのタイプを設定
	type = MOVE;

	//進行方向方向を管理
	if((z_dir == 1 && temp.z + rad.z/2 >= right) || (z_dir == -1 && temp.z + rad.z/2 <= left)){
		//if((z_dir == 1 && rad.z/2 >= right) || (z_dir == -1 && rad.z/2 <= left)){
		z_dir *= -1;
	}

	//進行方向を格納
	this->speed.z = speed * z_dir;

	//移動
	move(0,0,speed * z_dir);
}

//オブジェクトを特定の座標まで上下させる関数(y軸方向)
//dir : 1(正方向) -1(負方向)
void object::y_ud_move(float speed,float down,float up,int dir){
	static int y_dir = dir;

	vec3 temp = get_m_Pos();	//オブジェクトの座標
	vec3 rad  = get_Radius();	//オブジェクトの各軸方向の長さ

	//オブジェクトのタイプを設定
	type = MOVE;

	//オブジェクトの上面で方向を管理
	if((y_dir == 1 && temp.y + rad.y/2 >= up) || (y_dir == -1 && temp.y + rad.y/2 <= down)){
		y_dir *= -1;
	}

	//オブジェクトの中心で方向を管理(不要)
	/*if((y_dir == 1 && temp.y >= up) || (y_dir == -1 && temp.y <= down)){
		y_dir *= -1;
	}*/

	//進行方向を格納
	this->speed.y = speed * y_dir;

	//移動
	move(0,speed*y_dir,0);

	//動作確認
	//printf("y_dir = %d temp.y = %lf up = %lf\n",y_dir,temp.y,up);
}

//オブジェクトを特定の空間で単一方向に移動させる関数(y軸方向)
//dir : 1(正方向) -1(負方向)
void object::y_one_way_move(float speed,float down,float up,int dir){
	vec3 temp = get_m_Pos();	//オブジェクトの座標
	vec3 rad  = get_Radius();	//オブジェクトの各軸方向の長さ

	//オブジェクトの上面基準で座標書き換え
	if(dir == 1 && temp.y + rad.y/2 >= up){
		temp.y = down;
		set_m_Pos(temp);
	}

	//オブジェクトの上面で進行方向を管理
	if(dir == -1 && temp.y + rad.y/2 <= down){
		temp.y = up;
		set_m_Pos(temp);
	}

	//進行方向を格納
	this->speed.y = speed * dir;

	//移動
	move(0,speed*dir,0);
}

