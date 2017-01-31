/*
 * enemyPlayer.cpp
 *
 *  Created on: 2016/12/09
 *      Author: c501506022
 */

#include "enemyPlayer.h"
#include "image.h"
#include "Letter.h"
#include "net_client.h"
#include "Game.h"


enemyPlayer::enemyPlayer() {
	// TODO 自動生成されたコンストラクター・スタブ

}

void enemyPlayer::Initialize(){
	enemybullet.bullet_Initialize();
	for(int i=0;i<(int)(sizeof mywall/sizeof mywall[0]);i++){
		mywall[i].wall.setobject(position+vec3(lookat.x, lookat.y, lookat.z)*4,vec3(4,4,0.5f),vec3(0, atan2(lookat.x,lookat.z)*180/M_PI, 0),vec4(0.5f,0.5f,0.5f,1));
		mywall[i].count=0;

	}
}
void enemyPlayer::DrawInitialize(Role setrole){

	wallhandle=image_Load("Data/image/2079.jpg");
	for(int i=0;i<(int)(sizeof mywall/sizeof mywall[0]);i++)
		mywall[i].wall.set_imgno(wallhandle,100);

	char *flname=(char*)"Data/charamodel/char1/char1_exp_ver2.mqo";
	enemymodel=mqoCreateModel(flname,0.0035);

	enemybullet.bullet_DrawInitialize(setrole);
}
void enemyPlayer::DrawFinalize(){
	image_free(wallhandle);
	mqoDeleteModel(enemymodel);
}

void enemyPlayer::Draw() {
	//	vec3 forward_dir = vec3(sinf(angles.x), 0, cosf(angles.x));
	//vec3 right_dir = vec3(-forward_dir.z, 0, forward_dir.x);

	glPushMatrix();

	glColor3f(0.5,0.5,0.5);
	glTranslated(position.x,position.y,position.z);
	glRotated(angles.x * 180 /M_PI ,0,1,0);
	//glRotated(-angles.y * 180 /M_PI ,1,0,0);

	mqoCallModel(enemymodel);

	glPopMatrix();

	glColor3f(1,1,1);
	if(myteam==get_player()->myteam)
		Mozi_DrawM2_3D(vec3(position.x,position.y+1.3f,position.z),30,vec3(0,1,0),0.005,MOZI_HGMINTYOE,get_clients()[myid].name);

	enemybullet.Draw();
	DrawMyWall();
}

void enemyPlayer::DrawMyWall(){
	for(int i=0;i<WALLMAX;i++)
		if(mywall[i].count>0){
			mywall[i].wall.Draw();
		}

}

void enemyPlayer::resetminushp(){
	serverminushp=0;
}


enemyPlayer::~enemyPlayer() {
	// TODO Auto-generated destructor stub
}

