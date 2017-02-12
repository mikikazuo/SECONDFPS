/*
 * glm.cpp
 *
 *  Created on: 2016/10/24
 *      Author: c501506022
 */
#include "glm.h"

vec3::vec3(){
	this->x=0;
	this->y=0;
	this->z=0;
}

vec3::vec3(float x,float y,float z){
	this->x=x;
	this->y=y;
	this->z=z;
}
//  +演算子のオーバーロード
vec3 operator+(const vec3& v1,const vec3& v2)
{
    vec3 v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}
//  -演算子のオーバーロード
vec3 operator-(const vec3& v1,const vec3& v2)
{
    vec3 v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}
//  スカラー倍
vec3 operator*(const double d, const vec3& v)
{
    vec3 r;
    r.x = d * v.x;
    r.y = d * v.y;
    r.z = d * v.z;
    return r;
}
//  スカラー倍
vec3 operator*(const vec3& v,const double d)
{
    vec3 r;
    r.x = d * v.x;
    r.y = d * v.y;
    r.z = d * v.z;
    return r;
}



//  =演算子のオーバーロード
vec3& vec3::operator=(const vec3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
//  +=演算子のオーバーロード
vec3& vec3::operator+=(const vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
//  -=演算子のオーバーロード
vec3& vec3::operator-=(const vec3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec4::vec4(float x,float y,float z,int w){
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}
////  +演算子のオーバーロード
//vec4 operator+(const vec4& v1,const vec4& v2)
//{
//    vec4 v;
//    v.x = v1.x + v2.x;
//    v.y = v1.y + v2.y;
//    v.z = v1.z + v2.z;
//    return v;
//}
////  -演算子のオーバーロード
//vec4 operator-(const vec4& v1,const vec4& v2)
//{
//    vec4 v;
//    v.x = v1.x - v2.x;
//    v.y = v1.y - v2.y;
//    v.z = v1.z - v2.z;
//    return v;
//}
////  スカラー倍
//vec4 operator*(const double d, const vec4& v)
//{
//    vec4 r;
//    r.x = d * v.x;
//    r.y = d * v.y;
//    r.z = d * v.z;
//    return r;
//}
////  =演算子のオーバーロード
//vec4& vec4::operator=(const vec4& v)
//{
//    x = v.x;
//    y = v.y;
//    z = v.z;
//    return *this;
//}
////  +=演算子のオーバーロード
//vec4& vec4::operator+=(const vec4& v)
//{
//    x += v.x;
//    y += v.y;
//    z += v.z;
//    return *this;
//}
////  -=演算子のオーバーロード
//vec4& vec4::operator-=(const vec4& v)
//{
//    x -= v.x;
//    y -= v.y;
//    z -= v.z;
//    return *this;
//}

