/*
 * bullet.h
 *
 *  Created on: 2016/09/23
 *      Author: user
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "glm.h"



#include "fps.h"
#include "OBB.h"
#include "map.h"
#include "GLMetaseq.h"


class player;
#include "player.h"

#define MAXBULLET 50
#define MOBMAXBULLET 3

typedef struct {
	int count;
	vec3 position;
	vec3 dir;
	vec3 angles;
}Shot;




class player;
#include "player.h"

class bullet : public OBB{
private:


	int lifetime;


	int speed;
	Role mode;

	float bulletradi;
	MQO_MODEL bulletmodel;
public:
	int reloadtime;
	Shot bullet_info[MAXBULLET];

	bullet();
	void bullet_Initialize();
	void bullet_DrawInitialize(Role setbulletmode);
	void HitObj();
	void HitObj(Team enemyteam,float atk);
	void EnemyPlayerToPlayer();
	void PlayerToEnemy();
	void PlayerToMob();
	void MobToPlayer(int atk);
	void reload();
	void setInfo(vec3 playerposition,vec3 playerdir);
	void Update();
	void Draw();

	int reloadmax;
	int launchbulletcount;

	virtual ~bullet();
};

#endif /* BULLET_H_ */
