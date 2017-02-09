#ifndef GLMNO_H_
#define GLMNO_H_


class vec3{
public:
    float x;
    float y;
    float z;
public:
    vec3();
    vec3(float x,float y,float z);
    //  =演算子のオーバーロード
    vec3& operator=(const vec3& v);
    //  +=演算子のオーバーロード
    vec3& operator+=(const vec3& v);
    //  -=演算子のオーバーロード
    vec3& operator-=(const vec3& v);
};

//  +演算子のオーバーロード
vec3 operator+(const vec3&, const vec3&);
//  -演算子のオーバーロード
vec3 operator-(const vec3&, const vec3&);
//  *演算子のオーバーロード
//vec3 operator*(const double,const vec3& v);

vec3 operator*(const vec3& v,const double);
class vec4{
public:
    float x;
    float y;
    float z;
    int w;
public:
//    vec4(){};
   vec4(float x,float y,float z,int w);
//    //  =演算子のオーバーロード
//    vec4& operator=(const vec4& v);
//    //  +=演算子のオーバーロード
//    vec4& operator+=(const vec4& v);
//    //  -=演算子のオーバーロード
//    vec4& operator-=(const vec4& v);
};

////  +演算子のオーバーロード
//vec4 operator+(const vec4&, const vec4&);
////  -演算子のオーバーロード
//vec4 operator-(const vec4&, const vec4&);
////  *演算子のオーバーロード
////vec4 operator*(const double,const vec4& v);



#endif /* GLMNO_H_ */
