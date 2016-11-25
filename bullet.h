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
#include "player.h"

#define MAXBULLET 300


typedef struct {
	int count;
	vec3 position;
	vec3 dir;
}Shot;


class bullet : public OBB{
private:
	Shot bullet_info[MAXBULLET];

public:
	bullet();
	void bullet_Initialize();
	void HitObj();
	void PlayerToMob();
	void MobToPlayer(int atk);
	void setInfo(vec3 playerposition,vec3 playerdir);
	void Update();
	void Draw();
	virtual ~bullet();
};

#endif /* BULLET_H_ */
