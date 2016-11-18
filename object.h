/*
 * object.h
 *
 *  Created on: 2016/09/13
 *      Author: user
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "GL/glut.h"

#include "glm.h"
#include "OBB.h"


class object: public OBB {
private:

public:
	object();
	void setobject(vec3 position,vec3 size,vec3 rota,vec4 color);
	object(vec3 position,vec3 size,vec3 rota,vec4 color);

	void make_cuboid(float width,float height,float depth);
	void move(float x,float y,float z);
	void rotate(float x,float y,float z);
	void Draw();
	virtual ~object();
	void Line3D(float x1,float y1,float z1,float x2,float y2,float z2);
	void set_imgno(int no,int imgsize);



};

#endif /* OBJECT_H_ */
