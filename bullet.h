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

typedef enum{
	Crossbow,
	Rifle,
	Gatling,
	Spear,
	Magicstick,
	Magic,
	Mob,
	nonemode
}bulletmode;

class bullet : public OBB{
private:
	Shot bullet_info[MAXBULLET];
	int reloadmax;
	int lifetime;
	int launchbulletcount;
	int reloadtime;
	int speed;
	bulletmode mode;
	int modemovecount;
public:
	bullet();
	void bullet_Initialize(int setspeed,int setlifetime,int setreloadmax,bulletmode setbulletmode);
	void HitObj();
	void HitObj(Team enemyteam,float atk);
	void PlayerToMob();
	void MobToPlayer(int atk);
	void reload();
	void setInfo(vec3 playerposition,vec3 playerdir);
	void Update();
	void Draw();
	virtual ~bullet();
};

#endif /* BULLET_H_ */
