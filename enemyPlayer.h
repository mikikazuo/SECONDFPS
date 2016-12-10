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


class enemyPlayer {
private:
	MQO_MODEL enemymodel;


public:
	vec3 position;	//座標
	vec3 angles;	//角度
	vec3 lookat;	//視点

	enemyPlayer();
	void DrawInitialize(MQO_MODEL setmodel);
	void set_enemyposition();
    void Draw();

	virtual ~enemyPlayer();
};

#endif /* ENEMYPLAYER_H_ */
