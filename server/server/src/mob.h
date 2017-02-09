/*
 * mob.h
 *
 *  Created on: 2016/11/15
 *      Author: c501506022
 */

#ifndef MOB_H_
#define MOB_H_
#include "glm.h"

#include "bullet.h"

typedef enum{
	sidestep,
	sidestephard,
	runaway,
	noneaction
}attackmode;

typedef struct {
	bool findplayer;
	int playerid;
	attackmode mobmode;

}vsplayer;

int GetRandom(int min,int max);
class mob {
private:

	float radi;
	int myno;
	float dx;
	int movecount;

	float atkrange;
	bool hitmap;
	int atktime;
	vsplayer vsinfo;
	int dir;
	int alivecount;

public:
	bullet mobbullet;
	vec3 position;
	vec3 angles;
	vec3 lookat;
	float hp;
	float maxhp;
	float atk;
	float minushp;          //sa-ba-

	bool get_movablecount();
	mob();
	virtual ~mob();
	void Initialize(int no,vec3 pos,float ra,float sethp,float setatk,int setatktime,float setatkrange);
	void DrawInitialize(char *filename);
	void DrawFinalize();
	void Update();
	void move();
	void Draw();
	void launchBullet();
	void minushpfunc();
};

#endif /* MOB_H_ */