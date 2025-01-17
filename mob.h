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
#define GETEXP 30
typedef enum{
	sidestep,
	sidestephard,
	runaway,
	noneaction
}attackmode;

typedef struct {
	bool findplayer;
	attackmode mobmode;
	int dircount;
	int dir;
}vsplayer;

int GetRandom(int min,int max);
class mob {
private:

	float radi;
	int myno;
	float dx;
	int movecount;
	int flag;       //起動後なぜか先に動くのでそのための停止フラグ
	float atkrange;
	bool hitmap;
	int atktime;
	vsplayer vsinfo;

public:
	int hitred;
	bullet mobbullet;
	vec3 position;
	vec3 angles;
	vec3 lookat;
	float hp;
	float maxhp;
	float atk;

	float serverminushp;          //sa-ba-


	mob();
	virtual ~mob();
	void Initialize(int no,vec3 pos,float ra,float sethp,float setatk,int setatktime,float setatkrange);
	void DrawInitialize(char *filename);
	void DrawFinalize();
	void Update();
	void move();
	void Draw();
	void launchBullet();
	void resetminushp();
};

#endif /* MOB_H_ */
