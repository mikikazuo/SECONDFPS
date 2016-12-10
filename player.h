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
	int hp;			//体力
	vec3 position;	//座標
	vec3 angles;	//角度
	vec3 lookat;	//視点
	float dx,dy;	//??
	int atk;		//攻撃力
	int radi;		//当たり判定の半径

	//プレイヤーの頭のあたり判定で使用
	vec3 playerhead_collider;
	//プレイヤーの身体のあたり判定で使用
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
