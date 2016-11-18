#include "OBB.h"
#include <math.h>
const float MTXLIB_PI = 3.14159265f;

void OBB::setOBB(vec3 position,vec3 size){
	this->m_Pos.x=position.x;
	this->m_Pos.y=position.y;
	this->m_Pos.z=position.z;

	m_NormaDirect[0] = vec3(1, 0, 0);
	m_NormaDirect[1] = vec3(0, 1, 0);
	m_NormaDirect[2]= vec3(0, 0, 1);

	this->Radius.x=size.x;
	this->Radius.y=size.y;
	this->Radius.z=size.z;
}

// OBB v.s. OBB

//内積
float OBB::Dot(vec3 *vec1,vec3 *vec2){
	return vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z;
}
//外積
void OBB::crossFunc(vec3 *cross,vec3 *vec1,vec3 *vec2){
	*cross = vec3(vec1->y*vec2->z-vec1->z*vec2->y, vec1->z*vec2->x-vec1->x*vec2->z, vec1->x*vec2->y-vec1->y*vec2->x);
}
//ベクトルの長さ（大きさ）
float OBB::Vec3Length(vec3 *vec){
	return  sqrt(vec->x*vec->x+vec->y*vec->y+vec->z*vec->z);
}
// 分離軸に投影された軸成分から投影線分長を算出
float OBB::LenSegOnSeparateAxis(vec3 *Sep, vec3 *e1, vec3 *e2, vec3 *e3 )
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(Dot( Sep, e1 ));
	float r2 = fabs(Dot( Sep, e2 ));
	float r3 = e3 ? (fabs(Dot( Sep, e3 ))) : 0;
	return r1 + r2 + r3;
}
//単位ベクトル  0 : X軸  1 : Y軸  2 : Z軸
vec3 OBB::GetDirect( int elem ){
	return m_NormaDirect[elem];
}

//ベクトルの長さ  0 : X軸  1 : Y軸  2 : Z軸
float OBB::GetLen_W( int elem ){

	switch(elem){
	case 0:
		return Radius.x/2;
		break;
	case 1:
		return Radius.y/2;
		break;
	case 2:
		return Radius.z/2;
		break;


	};

	return  0;
}

vec3 OBB::GetPos_W(){
	return m_Pos;
}

//合成
MATRIX2 OBB::Multiplication(MATRIX2 mat,MATRIX2 mat2)
{
	MATRIX2 ret;
	for(int y=0;y<4;y++){
		for(int x=0;x<4;x++){
			ret.mat_16[y*4+x]=mat.mat_16[y*4]*mat2.mat_16[x]+mat.mat_16[y*4+1]*mat2.mat_16[x+4]+mat.mat_16[y*4+2]*mat2.mat_16[x+8]+mat.mat_16[y*4+3]*mat2.mat_16[x+12];
		}
	}
	return ret;
}

MATRIX2  OBB::YawPitchRoll(float y, float x, float z)
{
	MATRIX2 ret;
	MATRIX2 mY = Rotate('y', y);
	MATRIX2 mX = Rotate('x', x);
	MATRIX2 mZ = Rotate('z', z);
	//表示の際回転がx,y,zの順なのでこのかけ順 mZ*mY*mX
	MATRIX2 a=Multiplication(mZ,mY);
	MATRIX2 b=Multiplication(a,mX);
	return b;
}

float OBB::DegToRad(float deg)
{
	return deg*MTXLIB_PI/180;
}
float OBB::RadToDeg(float Rad){
	return Rad*180/MTXLIB_PI;
}

vec3 OBB::operato (MATRIX2  *l,vec3 v){
	vec3 ret;
	ret.x = (v.x * l->_11) + (v.y * l->_21) + (v.z * l->_31) + (l->_41);
	ret.y = (v.x * l->_12) + (v.y *l->_22) + (v.z * l->_32) + (l->_42);
	ret.z = (v.x * l->_13) + (v.y * l->_23) + (v.z * l->_33) + (l->_43);
	return ret;
}

// 分離軸を更新
void OBB::UpdateAxisAll()
{
	MATRIX2 mRot = YawPitchRoll(DegToRad(m_Rota.y), DegToRad(m_Rota.x), DegToRad(m_Rota.z));
	m_NormaDirect[0] = operato(&mRot,vec3(1, 0, 0));
	m_NormaDirect[1] = operato(&mRot,vec3(0, 1, 0));
	m_NormaDirect[2]= operato(&mRot,vec3(0, 0, 1));
}


MATRIX2 OBB::Rotate(char axis, float rad){
	MATRIX2 ret;
	float sinA = sinf(rad);
	float cosA = cosf(rad);
	switch (axis){
	case 'x':
	case 'X':
		ret._11 =  1.0f; ret._21 =  0.0f; ret._31 =  0.0f;
		ret._12 =  0.0f; ret._22 =  cosA; ret._32 = -sinA;
		ret._13 =  0.0f; ret._23 =  sinA; ret._33 =  cosA;
		break;

	case 'y':
	case 'Y':
		ret._11 =  cosA; ret._21 =  0.0f; ret._31 =  sinA;
		ret._12 =  0.0f; ret._22 =  1.0f; ret._32 =  0.0f;
		ret._13 = -sinA; ret._23 =  0.0f; ret._33 =  cosA;
		break;

	case 'z':
	case 'Z':
		ret._11 =  cosA; ret._21 = -sinA; ret._31 =  0.0f;
		ret._12 =  sinA; ret._22 =  cosA; ret._32 =  0.0f;
		ret._13 =  0.0f; ret._23 =  0.0f; ret._33 =  1.0f;
		break;
	}

	ret._14 = 0.0f; ret._24 = 0.0f; ret._34 = 0.0f;
	ret._41 = 0.0f;
	ret._42 = 0.0f;
	ret._43 = 0.0f;
	ret._44 = 1.0f;

	return ret;
}
