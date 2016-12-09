/*
 * mob.h
 *
 *  Created on: 2016/11/15
 *      Author: c501506022
 */

#ifndef MOB_H_
#define MOB_H_
#include "glm.h"

#include "player.h"
#include "bullet.h"

class mob {
private:
	bullet mobbullet;
	float radi;
	int myno;

	int dir;
	float dx;
	int movecount;
	int flag;       //起動後なぜか先に動くのでそのための停止フラグ
	float atkrange;
public:
	vec3 position;
	vec3 angles;
	vec3 lookat;
	int hp;
	int atk;


	mob();
	virtual ~mob();
	void Initialize(int no,vec3 pos,float ra,int sethp,int setatk,float setatkrange);
	void DrawInitialize();
	void Update();
	void move();
	void Draw();
	void launchBullet();
};

#endif /* MOB_H_ */
