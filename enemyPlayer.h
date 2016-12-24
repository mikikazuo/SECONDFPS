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

class enemyPlayer {
private:
	MQO_MODEL enemymodel;


public:
	bullet enemybullet;
	vec3 position;	//座標
	vec3 angles;	//角度
	vec3 lookat;	//視点
	Team myteam;
	float serverminushp;          //sa-ba-
	Wall mywall[WALLMAX];

	enemyPlayer();
	void Initialize();
	void DrawInitialize(MQO_MODEL setmodel);
	void set_enemyposition();
	void Draw();
	void resetminushp();
	void DrawMyWall();
	virtual ~enemyPlayer();
};

#endif /* ENEMYPLAYER_H_ */
