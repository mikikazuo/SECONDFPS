/*
 * map.cpp
 *
 *  Created on: 2016/11/11
 *      Author: user
 */

#include "map.h"

#include "image.h"

object obj[]={
		object(vec3(0,-0.1,0),vec3(600,0.001f,600),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(0,0,0),vec3(8,100,8),vec3(0,10,80),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(0,18,2),vec3(3,7,4),vec3(0,0,45),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(18,3,2),vec3(8,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(24,3,0),vec3(2,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(24,5,-10),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(24,5,-5),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))


};
static int count;

map::map() {
	// TODO 自動生成されたコンストラクター・スタブ

}

map::~map() {
	// TODO Auto-generated destructor stub
}

object *map::get_obj(){
	return obj;
}
int map::get_objnum(){
	return (int)(sizeof obj/sizeof obj[0]);
}
void map::Initialize(){

}
void map::DrawInitialize(){
	handle[0]=image_Load("Data/image/capture2.png");
	handle[1]=image_Load("Data/image/2079.jpg");
	handle[2]=image_Load("Data/image/2079.jpg");
	handle[3]=image_Load("Data/image/2079.jpg");

	obj[0].set_imgno(handle[2],100);
	obj[1].set_imgno(handle[1],100);
	obj[2].set_imgno(handle[1],100);
	obj[3].set_imgno(handle[1],100);
	obj[4].set_imgno(handle[3],100);

	obj[6].set_imgno(handle[1],100);
}
void map::DrawFinalize(){

}

void map::Update(){
	count++;

	static int dir =1;
	if(count%240==0)
		dir*=-1;
	obj[4].move(2*dir,2*dir,0);

	obj[5].rotate(60*dir,20*dir,40*dir);

	obj[6].rotate(20*dir,20*dir,10*dir);
}
void map::Draw(){
	for(int i=0;get_objnum()>i;i++)
		obj[i].Draw();


	image_DrawExRota3D(handle[0],0,9,0,0.1);
}
