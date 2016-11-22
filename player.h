/*
 * player.h
 *
 *  Created on: 2016/09/12
 *      Author: user
 */

#ifndef PLAYER_H_
#define PLAYER_H_


#include "glm.h"

#include "object.h"
#include "map.h"


#define WALLMAX 5

typedef struct {
	int count;
	object wall;
}Wall;


class player
{
private:

	int bulletnum;
public:
	int hp;
	vec3 position;
	vec3 angles;
	vec3 lookat;
	float dx,dy;
	int atk;
	int radi;

	//プレイヤーの頭のあたり判定
	vec3 playerhead_collider;
	//プレイヤーの身体のあたり判定
	vec3 player_collider;


	Wall *get_mywall();
	player();
	void Initialize(vec3 pos,float ra,int sethp,int setatk);
	void DrawInitialize();
	void DrawFinalize();
	void Draw();
	void Update();
	bool Move(object *mapobject,int mapn,Wall *playerwall);
	void set_wall();
	void remove_wall();
	void DrawMyWall();
	void MouseMove();
	void launchBullet();
	void Action();
	void MakeCamAndLightMatrix();
	virtual ~player();
};

#endif /* PLAYER_H_ */