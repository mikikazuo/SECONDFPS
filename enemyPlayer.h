/*
 * enemyPlayer.h
 *
 *  Created on: 2016/12/09
 *      Author: c501506022
 */

#ifndef ENEMYPLAYER_H_
#define ENEMYPLAYER_H_

#include "glm.h"
#include "GLMetaseq.h"
#include "bullet.h"
#include "charaanimation.h"
class enemyPlayer {
private:
	MQO_MODEL enemymodel;
	int wallhandle;
	chara_animation mymodel;
public:
	int myid;
	bullet enemybullet;
	vec3 position;	//座標
	vec3 angles;	//角度
	vec3 lookat;	//視点
	Team myteam;
	Role myrole;
	float serverminushp;          //sa-ba-
	Wall mywall[WALLMAX];

	enemyPlayer();
	void Initialize();
	void DrawInitialize(Role setrole);
	void DrawFinalize();
	void set_enemyposition();
	void Draw();
	void resetminushp();
	void DrawMyWall();
	virtual ~enemyPlayer();
};

#endif /* ENEMYPLAYER_H_ */
