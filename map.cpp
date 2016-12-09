/*
 * map.cpp
 *
 *  Created on: 2016/11/11
 *      Author: user
 */

#include "map.h"

#include "image.h"

object obj[]={
		//関数objectの引数:
		//座標・各座標におけるサイズ・回転・色(テクスチャを貼らない場合)
		//f...float型
		//地面
		object(vec3(0,-0.1,0),vec3(/*150*/150,0.001f,150/*150*/),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//坂
		object(vec3(10,0,0),vec3(1,10,5),vec3(0,0,60),vec4(0.5f,0.5f,0.5f,1)),
		//天空のテクスチャ物体
		object(vec3(0,180,2),vec3(3,7,4),vec3(0,0,45),vec4(0.5f,0.5f,0.5f,1)),
		//坂の上の足場
		object(vec3(18,3,2),vec3(8,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//動く足場
		object(vec3(24,3,0),vec3(2,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//回転する白色物体
		object(vec3(24,5,-10),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//回転するテクスチャ物体
		object(vec3(24,5,-5),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//追加
		//直方体 7,8
		object(vec3(-2.5,0.5,-10),vec3(1,1,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(-4,1,-10),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//壁 9〜12
		//中心は(0,0,0)
		//フィールドの大きさ，壁の厚みによる自動入力
		//四隅での被りをさせないために前後の壁を左右の壁をより少し(壁の厚みだけ)長くしている
		//前
		object(vec3((MAP_X_LENGTH + WALL_THICKNESS)/2,WALL_HEIGHT/2,0),vec3(WALL_THICKNESS,WALL_HEIGHT,(MAP_Z_LENGTH + WALL_THICKNESS*2)),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//後
		object(vec3(-(MAP_X_LENGTH + WALL_THICKNESS)/2,WALL_HEIGHT/2,0),vec3(WALL_THICKNESS,WALL_HEIGHT,(MAP_Z_LENGTH + WALL_THICKNESS*2)),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//右
		object(vec3(0,WALL_HEIGHT/2,(MAP_Z_LENGTH + WALL_THICKNESS)/2),vec3(MAP_X_LENGTH,WALL_HEIGHT,WALL_THICKNESS),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//左
		object(vec3(0,WALL_HEIGHT/2,-(MAP_Z_LENGTH + WALL_THICKNESS)/2),vec3(MAP_X_LENGTH,WALL_HEIGHT,WALL_THICKNESS),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//拠点1(前方) 13
		object(vec3((MAP_X_LENGTH - BASE_X_LENGTH)/2,BASE_Y_LENGTH/2,0),vec3(BASE_X_LENGTH,BASE_Y_LENGTH,BASE_Z_LENGTH),vec3(0,0,0),vec4(256,0,0,1)),
		//拠点2(後方) 14
		object(vec3(-(MAP_X_LENGTH - BASE_X_LENGTH)/2,BASE_Y_LENGTH/2,0),vec3(BASE_X_LENGTH,BASE_Y_LENGTH,BASE_Z_LENGTH),vec3(0,0,0),vec4(0,0,256,1)),

		//マップ分割
		//縦 15
		object(vec3(0,0,0),vec3(MAP_X_LENGTH,0.1,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//横 16
		object(vec3(0,0,0),vec3(0.1,0.1,MAP_Z_LENGTH),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//高台 前方(赤) 17
		object(vec3(49,10,-49),vec3(2,20,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//エレベーター
		object(vec3(49,-13,-45),vec3(2,30,4),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//object(vec3(48.5,1,-41.5),vec3(2,2,4),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//高台 後方(青) 19
		object(vec3(-49,10,49),vec3(2,20,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//エレベーター
		object(vec3(-49,-13,45),vec3(2,30,4),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//中央柱 21
		,object(vec3(0,10,0),vec3(2,20,2),vec3(0,45,0),vec4(0.5f,0.5f,0.5f,1))

		//天空足場 22
		,object(vec3(0,20.5,0),vec3(15,1,15),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//螺旋階段 23〜32
		,object(vec3(0,0.5,3),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(3,2.0,0),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(0,3.5,-3),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(-3,5.0,0),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		,object(vec3(0,6.5,3),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(3,8.0,0),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(0,9.5,-3),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(-3,11.0,0),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		,object(vec3(0,12.5,3),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(3,14.0,0),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//エレベーターへの足場 33
		,object(vec3(3,14,-7),vec3(2,0.1,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//天空足場へ登るエレベーター 34
		,object(vec3(3,11,-9.5),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//x軸方向の当たり判定用オブジェクト 35
		,object(vec3(15,1,15),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//z軸方向の当たり判定用オブジェクト 36
		,object(vec3(17,1,17),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//テンプレート
		//,object(vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
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

//オブジェクトの数を返す変数
int map::get_objnum(){
	return (int)(sizeof obj/sizeof obj[0]);
}

void map::Initialize(){

}

void map::DrawInitialize(){
//描画初期化関数
	handle[0]=image_Load("Data/image/capture2.png");
	handle[1]=image_Load("Data/image/2079.jpg");
	handle[2]=image_Load("Data/image/20791.jpg");

	obj[0].set_imgno(handle[1],100);
	obj[1].set_imgno(handle[1],100);
	obj[2].set_imgno(handle[1],100);
	obj[3].set_imgno(handle[1],100);
	obj[4].set_imgno(handle[1],100);

	obj[6].set_imgno(handle[1],100);

	//追加??
	obj[7].set_imgno(handle[1],100);

	//壁
	obj[9].set_imgno(handle[2],100);
	obj[10].set_imgno(handle[2],100);
	obj[11].set_imgno(handle[2],100);
	obj[12].set_imgno(handle[2],100);

	//拠点横の高台へ登るエレベーター
	obj[18].set_imgno(handle[1],100);
	obj[20].set_imgno(handle[1],100);

	//中央柱
	obj[21].set_imgno(handle[1],100);
	//天空足場
	obj[22].set_imgno(handle[1],100);

}
void map::DrawFinalize(){

}

void map::Update(){
//オブジェクトの移動・回転

	static int dir = 1;

	//移動・回転の周期を複数個生成する配列
	static int counts[] = {0,0,0,0,0,0};
	static int dirs[]   = {1,1,1,1,1,1};

	count++;
	counts[1]++;
	counts[2]++;

	//countが240毎に方向が逆転
	//つまり，どの移動・回転も周期は同じ
	if(count%240 == 0){
		dir *= -1;
	}

	//周期7秒
	if(counts[1] % 420 == 0){
			dirs[1] *= -1;
		}

	/*** 周期一覧 ***/
	//4秒 count
	//7秒 counts[1] dirs[1]

	//周期なし counts[0] dirs[0]

	/***回転***/
	obj[5].rotate(60*dir,20*dir,40*dir);
	obj[6].rotate(20*dir,20*dir,10*dir);

	/***移動***/
	obj[4].move(2*dir,2*dir,0);

	//動作確認
	//obj[7].move(0.5*dir,0.5*dir,0.5*dir);

	//高台へのエレベーター(特定座標間を上下)
	obj[18].y_ud_move(3.5,-3,23,-1);
	obj[20].y_ud_move(3.5,-3,23,-1);

	//天空足場へのエレベーター(特定座標間を上方向のみで移動)
	obj[34].y_one_way_move(2.0,14,23,1);

	//左右の当たり判定用オブジェクト
	obj[35].x_side_move(2.0,15,20,1);
	obj[36].z_side_move(2.0,13,15,1);

}

void map::Draw(){
	for(int i=0;get_objnum()>i;i++)
		obj[i].Draw();

	//フィールド内に3D画像表示
	//image_DrawExRota3D(handle[0],0,9,0,0.1);
}
