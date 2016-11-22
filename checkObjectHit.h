/*
 * checkObjectHit.h
 *
 *  Created on: 2016/09/21
 *      Author: user
 */

#ifndef CHECKOBJECTHIT_H_
#define CHECKOBJECTHIT_H_

#include "glm.h"
#include "player.h"
#include "object.h"

class checkObjectHit: OBB{
public:
	checkObjectHit();
	virtual ~checkObjectHit();
	bool sethitcheck(int num,object *obb,vec3 pointpos,float radi);
	bool sethitcheck(int num,Wall *obb,vec3 pointpos,float radi);
	bool pointVsPoint(vec3 pointpos1,vec3 pointpos2,float radi);
	bool alphaOBBs( OBB &obb1,object &obb2 );
	bool ColOBBs( object &obb1,object &obb2 );
	float LenOBBToPoint( object &obb,vec3 pointpos);

};

#endif /* CHECKOBJECTHIT_H_ */
