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

	float dx;
	int movecount;
	int flag;       //起動後なぜか先に動くのでそのための停止フラグ
	float atkrange;
	bool hitmap;
	bool hitwall;
public:
	vec3 position;
	vec3 angles;
	vec3 lookat;
	float hp;
	float maxhp;
	float atk;


	mob();
	virtual ~mob();
	void Initialize(int no,vec3 pos,float ra,float sethp,float setatk,float setatkrange);
	void DrawInitialize(char *filename);
	void DrawFinalize();
	void Update();
	void move();
	void Draw();
	void launchBullet();
};

#endif /* MOB_H_ */
