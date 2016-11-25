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

	//オブジェクトの座標を取得する関数
	vec3 get_m_Pos();
	//オブジェクトの座標を変更する関数
	void set_m_Pos(vec3 Pos);
	//オブジェクトの各軸方向の長さを取得する関数
	vec3 get_Radius();
	//特定の高さまでオブジェクトを上下させる関数
	void ud_move(float speed,float down,float up,int dir);
	//オブジェクトを特定の空間で単一方向に移動させる関数(y軸方向)
	void one_way_move(float speed,float down,float up,int dir);
};

#endif /* OBJECT_H_ */
