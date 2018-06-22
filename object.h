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

//オブジェクトのタイプ
enum {NORMAL,		//通常
	  MOVE,			//移動
	  };

class object: public OBB {
private:

public:
	int myno; //配列時の添字をあらわす
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
	//オブジェクトの回転を取得する関数
	vec3 get_m_Rot();
	//オブジェクトの回転を変更する関数
	void set_m_Rot(vec3 Rot);
	//オブジェクトの各軸方向の長さを取得する関数
	vec3 get_Radius();
	//特定の高さまでオブジェクトを上下させる関数
	void y_ud_move(float speed,float down,float up,int dir);
	//オブジェクトを特定の座標間で移動させる関数(x軸方向)
	void x_side_move(float speed,float left,float right,int dir);
	//オブジェクトを特定の座標間で移動させる関数(z軸方向)
	void z_side_move(float speed,float left,float right,int dir);
	//オブジェクトを特定の空間で単一方向に移動させる関数(y軸方向)
	void y_one_way_move(float speed,float down,float up,int dir);

	//各軸方向へ移動しているオブジェクトの進行方向,進行速度
	//(負の値:負の方向 0:停S止 正の値:正の方向 数値の絶対値:進行速度)
	vec3 speed;

	//移動後のオブジェクトの座標
	vec3 Pos_move;

	//オブジェクトのタイプ
	int type;
};

#endif /* OBJECT_H_ */
