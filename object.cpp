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



//ライトの位置
static GLfloat lightpos[] 		 = {10.0, 10.0, 50,0}; 	//光源の位置
static GLfloat lightDiffuse[3]  = {1.0,	 1.0, 1.0}; 	//拡散光
static GLfloat lightAmbient[3]  = {1.0, 1.0, 1.0}; 		//環境光
static GLfloat lightSpecular[3] = {1.0, 1.0, 1.0}; 		//鏡面光

double const texture_repos = 0;

object::object() {

}
void object::setobject(vec3 position,vec3 size,vec3 rota,vec4 color){
	this->m_Pos.x = position.x;
	this->m_Pos.y = position.y;
	this->m_Pos.z = position.z;

	m_Rota.x = rota.x;
	m_Rota.y = rota.y;
	m_Rota.z = rota.z;

	UpdateAxisAll();

	this->Radius.x = size.x;
	this->Radius.y = size.y;
	this->Radius.z = size.z;

	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
	this->color[3] = color.w;


	this->imgno = -1;
}
object::object(vec3 position,vec3 size,vec3 rota,vec4 color) {
	// TODO 自動生成されたコンストラクター・スタブ
	//座標，大きさ，回転，色

	this->m_Pos.x = position.x;
	this->m_Pos.y = position.y;
	this->m_Pos.z = position.z;

	m_Rota.x = rota.x;
	m_Rota.y = rota.y;
	m_Rota.z = rota.z;

	UpdateAxisAll();

	this->Radius.x = size.x;
	this->Radius.y = size.y;
	this->Radius.z = size.z;

	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
	this->color[3] = color.w;


	this->imgno = -1;

}

void object::set_imgno(int no,int imgsize){
	this->imgno = no;
	this->imgresize = imgsize;
}

//直方体生成
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

		Line3D(this->m_Pos.x,this->m_Pos.y,this->m_Pos.z,
				this->m_Pos.x+rate*this->m_NormaDirect[i].x,this->m_Pos.y+rate*this->m_NormaDirect[i].y,this->m_Pos.z+rate*this->m_NormaDirect[i].z);

	}
	glColor3d(1.0, 1.0, 1.0);
}

//移動
void object::move(float x,float y,float z){
	static int flag;
	if(flag){
		this->m_Pos.x += x*get_mainfps().fps_getDeltaTime();
		this->m_Pos.y += y*get_mainfps().fps_getDeltaTime();
		this->m_Pos.z += z*get_mainfps().fps_getDeltaTime();
	}else
		flag = 1;
}

//回転
void object::rotate(float x,float y,float z){

	this->m_Rota.x += x*get_mainfps().fps_getDeltaTime();
	this->m_Rota.y += y*get_mainfps().fps_getDeltaTime();
	this->m_Rota.z += z*get_mainfps().fps_getDeltaTime();

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

