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

#define MAXBULLET 300


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

	int reloadtime;
	int speed;
	Role mode;

	float bulletradi;
	MQO_MODEL bulletmodel;
public:
	Shot bullet_info[MAXBULLET];

	bullet();
	void bullet_Initialize(Role setbulletmode);
	void bullet_DrawInitialize();
	void HitObj();
	void HitObj(Team enemyteam,float atk);
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
