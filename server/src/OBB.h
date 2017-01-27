/*
 * OBB.h
 *
 *  Created on: 2016/09/14
 *      Author: user
 */

#ifndef OBB_H_
#define OBB_H_
#include "GL/glut.h"

#include "glm.h"


//マトリクス構造体
struct MATRIX2 {
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float mat_4x4[4][4];
		float mat_16[16];
	};
	MATRIX2(){//単位行列に初期化
		for(int i=0;i<16;i++){
			this->mat_16[i]=0;
		}
		this->_11=this->_22=this->_33=this->_44=1;
	}
};

class OBB
{
protected:

	vec3 m_Pos;             //位置
	vec3 m_NormaDirect[3];  //方向ベクトル
	vec3 m_Rota;   			//回転
	vec3 Radius;       		//各軸方向の長さ
	GLfloat color[4];
	int imgno;
	double imgresize;
public:

	void setOBB(vec3 position,vec3 size);
	float Dot(vec3 *vec1,vec3 *vec2);					 //内積
	void crossFunc(vec3 *cross,vec3 *vec1,vec3 *vec2); //外積
	float LenSegOnSeparateAxis( vec3 *Sep, vec3 *e1, vec3 *e2, vec3 *e3=0);
	vec3 GetPos_W();    //位置の取得
	vec3 GetRot_W();
	float  Vec3Length(vec3 *vec);		//ベクトルの長さ（大きさ）
	vec3 GetDirect( int elem );  		//指定軸番号の方向ベクトルを取得
	float GetLen_W( int elem );       //指定軸方向の長さを取得

	MATRIX2  YawPitchRoll(float y, float x, float z);
	MATRIX2 Multiplication(MATRIX2 mat,MATRIX2 mat2);
	void UpdateAxisAll();
	vec3 operato(MATRIX2  *l,vec3 v);
	float DegToRad(float deg);
	float RadToDeg(float Rad);
	MATRIX2 Rotate(char axis, float rad);
};

#endif /* OBB_H_ */
