/*
 * checkObjectHit.h
 *
 *  Created on: 2016/09/21
 *      Author: user
 */

#ifndef CHECKOBJECTHIT_H_
#define CHECKOBJECTHIT_H_

#include "glm.h"

#include "object.h"

class checkObjectHit: OBB{
public:
	checkObjectHit();
	virtual ~checkObjectHit();

	bool alphaOBBs( OBB &obb1,object &obb2 );
	bool ColOBBs( object &obb1,object &obb2 );
	float LenOBBToPoint( object &obb,vec3 pointpos);

};

#endif /* CHECKOBJECTHIT_H_ */
