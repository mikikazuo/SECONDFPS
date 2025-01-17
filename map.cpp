/*
 * map.cpp
 *
 *  Created on: 2016/11/11
 *      Author: user
 */

#include "map.h"

#include "image.h"
#include "GLMetaseq.h"

MQO_MODEL basemodel[2];
//多人数戦用obj
int img[6];
object obj[]={
		//関数objectの引数:
		//座標・各座標におけるサイズ・回転・色(テクスチャを貼らない場合)
		//f...float型
		//地面
		object(vec3(0,-0.1,0),vec3(100,0.001f,100),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//坂
		object(vec3(10,9990,0),vec3(1,10,5),vec3(0,0,60),vec4(0.5f,0.5f,0.5f,1)),
		//天空のテクスチャ物体
		object(vec3(0,180,2),vec3(3,7,4),vec3(0,0,45),vec4(0.5f,0.5f,0.5f,1)),
		//坂の上の足場
		object(vec3(18,99993,2),vec3(8,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//動く足場
		object(vec3(24,9993,0),vec3(2,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//回転する白色物体
		object(vec3(24,9995,-10),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//回転するテクスチャ物体
		object(vec3(24,9995,-5),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//追加
		//直方体 7,8
		object(vec3(-2.5,9990.5,-10),vec3(1,1,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(-4,99991,-10),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//壁 9〜12
		//中心は(0,0,0)
		//フィールドの大きさ，壁の厚みによる自動入力
		//四隅での被りをさせないために前後の壁を左右の壁をより少し(壁の厚みだけ)長くしている
		//前
		object(vec3((MAP_X_LENGTH + WALL_THICKNESS)/2,WALL_HEIGHT/2,0),vec3(WALL_THICKNESS,WALL_HEIGHT,(MAP_Z_LENGTH + WALL_THICKNESS*2)),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,0)),
		//後
		object(vec3(-(MAP_X_LENGTH + WALL_THICKNESS)/2,WALL_HEIGHT/2,0),vec3(WALL_THICKNESS,WALL_HEIGHT,(MAP_Z_LENGTH + WALL_THICKNESS*2)),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,0)),
		//右
		object(vec3(0,WALL_HEIGHT/2,(MAP_Z_LENGTH + WALL_THICKNESS)/2),vec3(MAP_X_LENGTH,WALL_HEIGHT,WALL_THICKNESS),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,0)),
		//左
		object(vec3(0,WALL_HEIGHT/2,-(MAP_Z_LENGTH + WALL_THICKNESS)/2),vec3(MAP_X_LENGTH,WALL_HEIGHT,WALL_THICKNESS),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,0)),

		//拠点1(前方:赤) 13
		object(vec3((MAP_X_LENGTH - BASE_X_LENGTH)/2,BASE_Y_LENGTH/2,0),vec3(BASE_X_LENGTH,BASE_Y_LENGTH,BASE_Z_LENGTH),vec3(0,0,0),vec4(256,0,0,0)),
		//拠点2(後方:青) 14
		object(vec3(-(MAP_X_LENGTH - BASE_X_LENGTH)/2,BASE_Y_LENGTH/2,0),vec3(BASE_X_LENGTH,BASE_Y_LENGTH,BASE_Z_LENGTH),vec3(0,0,0),vec4(0,0,256,0)),

		//マップ分割
		//縦 15
		object(vec3(0,9999999990,0),vec3(MAP_X_LENGTH,0.1,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//横 16
		object(vec3(0,9999999990,0),vec3(0.1,0.1,MAP_Z_LENGTH),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//高台 前方(赤) 17
		object(vec3(49,10,-49),vec3(2,20,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//エレベーター
		object(vec3(49,-13,-45),vec3(2,30,4),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

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
		,object(vec3(3,14,-6.25),vec3(2,0.1,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//天空足場へ登るエレベーター 34

		,object(vec3(3,11,-9.5),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//x軸方向の当たり判定用オブジェクト 35
		,object(vec3(15,99999991,15),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//z軸方向の当たり判定用オブジェクト 36
		,object(vec3(17,99999991,17),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//天空足場へのエレベーターと通路を囲む壁
		//側面1(赤側) 37
		,object(vec3(4.30,99917,-6.25),vec3(0.1,6,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(4.30,99921.5,-9.0),vec3(0.1,3,3),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//側面2(青側) 39
		,object(vec3(1.80,999917,-6.25),vec3(0.1,6,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(1.80,999921.5,-9.0),vec3(0.1,3,3),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//中央柱と各陣地を横に分割する壁
		//前(赤側) 41
		,object(vec3( 19.75,7.5,0),vec3(0.5,15,40),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//後(青側)
		,object(vec3(-19.75,7.5,0),vec3(0.5,15,40),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右前
		,object(vec3( 12.5,7.5, 19.75),vec3(15,15,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右後
		,object(vec3(-12.5,7.5, 19.75),vec3(15,15,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左前
		,object(vec3( 12.5,7.5,-19.75),vec3(15,15,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左後 46
		,object(vec3(-12.5,7.5,-19.75),vec3(15,15,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//建物1(中央右) 47
		,object(vec3(0,2,40),vec3(20,4,20),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//建物2(中央左) 48
		,object(vec3(0,2,-40),vec3(20,4,20),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//赤拠点を囲む壁
		//右側面 49
		,object(vec3(40,1,-10.05),vec3(20,2,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左側面
		,object(vec3(40,1,10.05),vec3(20,2,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右前方
		,object(vec3(30.05,1,-7.5),vec3(0.1,2,5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左前方 52
		,object(vec3(30.05,1,7.5),vec3(0.1,2,5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//拠点前壁
		,object(vec3(45.05,1,0),vec3(0.1,2,10),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//柱群 54〜61
		,object(vec3(-15,3,15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(-15,3,-15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(15,3,15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(15,3,-15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		,object(vec3(0,3999,10),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(0,3999,-10),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(10,3,0),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(-10,3,0),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//天井 62 (とりあえずは2人対戦用)
		,object(vec3(0,9999999999931,0),vec3(50,2,50),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//赤拠点右側通路
		//縦壁 63
		,object(vec3(30,2,-20.5),vec3(20,4,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁
		,object(vec3(39.5,2,-30.25),vec3(1,4,19.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//仕切り壁(手前)
		,object(vec3(30.5,2,-40),vec3(1,4,20),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//仕切り壁(奥) 66
		,object(vec3(20.5,2,-30.25),vec3(1,4,19.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//赤拠点左側広場
		//***広場外側***
		//縦壁 67
		,object(vec3(32.5,2,20.5),vec3(25,4,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁
		,object(vec3(20.5,2,32.25),vec3(1,4,24.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//***広場内***
		//柱
		,object(vec3(35,5,35),vec3(1,10,1),vec3(0,45,0),vec4(0.5f,0.5f,0.5f,1))
		//---手前---
		//縦壁
		,object(vec3(42.5,9999999992,29.5),vec3(5,4,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁
		,object(vec3(40.5,99999992,27.25),vec3(0.1,4,4.95),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//---奥---
		//縦壁
		,object(vec3(27.5,9999992,40.5),vec3(5,4,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁 73
		,object(vec3(29.5,99999992,42.75),vec3(0.1,4,4.95),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//青拠点を囲む壁
		//右側面 74
		,object(vec3(-40,1,10.05),vec3(20,2,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左側面
		,object(vec3(-40,1,-10.05),vec3(20,2,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右前方
		,object(vec3(-30.05,1,7.5),vec3(0.1,2,5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左前方
		,object(vec3(-30.05,1,-7.5),vec3(0.1,2,5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//拠点前壁 78
		,object(vec3(-45.05,1,0),vec3(0.1,2,10),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//青拠点右側通路
		//縦壁 79
		,object(vec3(-30,2,20.5),vec3(20,4,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁
		,object(vec3(-39.5,2,30.25),vec3(1,4,19.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//仕切り壁(手前)
		,object(vec3(-30.5,2,40),vec3(1,4,20),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//仕切り壁(奥) 82
		,object(vec3(-20.5,2,30.25),vec3(1,4,19.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//青拠点左側広場
		//***広場外側***
		//縦壁 83
		,object(vec3(-32.5,2,-20.5),vec3(25,4,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁
		,object(vec3(-20.5,2,-32.25),vec3(1,4,24.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//***広場内***
		//柱
		,object(vec3(-35,5,-35),vec3(1,10,1),vec3(0,45,0),vec4(0.5f,0.5f,0.5f,1))
		//---手前---
		//縦壁
		,object(vec3(-42.5,9999999992,-29.5),vec3(5,4,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁
		,object(vec3(-40.5,99999992,-27.25),vec3(0.1,4,4.95),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//---奥---
		//縦壁
		,object(vec3(-27.5,9999992,-40.5),vec3(5,4,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//横壁 89
		,object(vec3(-29.5,99999992,-42.75),vec3(0.1,4,4.95),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//真ん中床 90
		,object(vec3(0,0.005,0),vec3(39,0.005,39),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//天空足場の壁
		//前
		//,object(vec3(7,23.5,0),vec3(1,5,15),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//後
		//右
		//左


		//テンプレート
		//,object(vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
};

//1対1用obj
/*object obj[]={
		//関数objectの引数:
		//座標・各座標におけるサイズ・回転・色(テクスチャを貼らない場合)
		//f...float型
		//地面
		object(vec3(0,-0.1,0),vec3(150,0.001f,150),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//坂
		object(vec3(10,100000000000000,0),vec3(1,10,5),vec3(0,0,60),vec4(0.5f,0.5f,0.5f,1)),
		//天空のテクスチャ物体
		object(vec3(0,180,2),vec3(3,7,4),vec3(0,0,45),vec4(0.5f,0.5f,0.5f,1)),
		//坂の上の足場
		object(vec3(18,300,2),vec3(8,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//動く足場
		object(vec3(24,3000000,0),vec3(2,1,8),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//回転する白色物体
		object(vec3(24,50000000,-10),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//回転するテクスチャ物体
		object(vec3(24,5000000,-5),vec3(2,3,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//追加
		//直方体 7,8
		object(vec3(-2.5,999999999999990.5,-10),vec3(1,1,1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		object(vec3(-4,199999999999999999,-10),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//壁 9〜12
		//中心は(0,0,0)
		//フィールドの大きさ，壁の厚みによる自動入力
		//四隅での被りをさせないために前後の壁を左右の壁をより少し(壁の厚みだけ)長くしている
		//前
		object(vec3((50 + WALL_THICKNESS)/2,15,0),vec3(WALL_THICKNESS,30,(50 + WALL_THICKNESS*2)),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//後
		object(vec3(-(50 + WALL_THICKNESS)/2,15,0),vec3(WALL_THICKNESS,30,(50 + WALL_THICKNESS*2)),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//右
		object(vec3(0,15,(50 + WALL_THICKNESS)/2),vec3(50,30,WALL_THICKNESS),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//左
		object(vec3(0,15,-(50 + WALL_THICKNESS)/2),vec3(50,30,WALL_THICKNESS),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//拠点1(前方:赤) 13
		object(vec3((50 - BASE_X_LENGTH)/2,BASE_Y_LENGTH/2,0),vec3(BASE_X_LENGTH,BASE_Y_LENGTH,BASE_Z_LENGTH),vec3(0,0,0),vec4(256,0,0,1)),
		//拠点2(後方:青) 14
		object(vec3(-(50 - BASE_X_LENGTH)/2,BASE_Y_LENGTH/2,0),vec3(BASE_X_LENGTH,BASE_Y_LENGTH,BASE_Z_LENGTH),vec3(0,0,0),vec4(0,0,256,1)),

		//マップ分割
		//縦 15
		object(vec3(0,999999999999990,0),vec3(50,0.1,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//横 16
		object(vec3(0,9999999999999990,0),vec3(0.1,0.1,50),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//高台 前方(赤) 17
		object(vec3(24,10,-24),vec3(2,20,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//エレベーター
		object(vec3(24,-13,-21),vec3(2,30,4),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),

		//高台 後方(青) 19
		object(vec3(-24,10,24),vec3(2,20,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1)),
		//エレベーター
		object(vec3(-24,-13,21),vec3(2,30,4),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

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
		,object(vec3(3,14,-6.25),vec3(2,0.1,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//天空足場へ登るエレベーター 34
		,object(vec3(3,14,-9.5),vec3(2,0.1,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//x軸方向の当たり判定用オブジェクト 35
		,object(vec3(15,1999999999999999,15),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//z軸方向の当たり判定用オブジェクト 36
		,object(vec3(17,19999999999,17),vec3(2,2,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//天空足場へのエレベーターと通路を囲む壁
		//側面1(赤側) 37
		,object(vec3(4.30,17999999999999,-6.25),vec3(0.1,6,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(4.30,21999999999999.5,-9.0),vec3(0.1,3,3),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//側面2(青側) 39
		,object(vec3(1.80,17999999999999,-6.25),vec3(0.1,6,8.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(1.80,21999999999999.5,-9.0),vec3(0.1,3,3),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//中央柱と各陣地を横に分割する壁
		//前(赤側) 41
		,object(vec3( 9999999999999999919.75,7.5,0),vec3(0.5,15,40),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//後(青側)
		,object(vec3(-9999999999999999999919.75,7.5,0),vec3(0.5,15,40),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右前
		,object(vec3( 99999999999999999912.5,1, 19.75),vec3(15,2,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右後
		,object(vec3(-999999999999999912.5,1, 19.75),vec3(15,2,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左前
		,object(vec3( 99999999999999999999912.5,1,-19.75),vec3(15,2,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左後 46
		,object(vec3(-9999999999999999999912.5,1,-19.75),vec3(15,2,0.5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//建物1(中央右) 47
		,object(vec3(0,9999999992,40),vec3(20,4,20),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//建物2(中央左) 48
		,object(vec3(0,9999999992,-40),vec3(20,4,20),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//赤拠点を囲む壁
		//右側面 49
		,object(vec3(40,99999999999991,-10.05),vec3(20,2,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左側面
		,object(vec3(40,999999999999991,10.05),vec3(20,2,0.1),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//右前方
		,object(vec3(30.05,9999999999999991,-7.5),vec3(0.1,2,5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//左前方 52
		,object(vec3(30.05,999999999999991,7.5),vec3(0.1,2,5),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		//拠点前壁
		,object(vec3(45.05,999999999991,0),vec3(0.1,2,10),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//柱群 54〜61
		,object(vec3(-15,3,15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(-15,3,-15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(15,3,15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(15,3,-15),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(0,3,10),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(0,3,-10),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(10,3,0),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
		,object(vec3(-10,3,0),vec3(2,6,2),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))

		//天井 62
		,object(vec3(0,31,0),vec3(50,2,50),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))


		//テンプレート
		//,object(vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),vec4(0.5f,0.5f,0.5f,1))
};*/

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

//拠点にするobjectの添字を設定
void map::set_Base(Team team,int objectno){
	for(int j=0;j<BASENUM;j++){
		if(baseno[team][j]==-1)
			baseno[team][j]=objectno;
	}
}

//拠点のhpminusリセット
void map::resetminushp(){
	serverminushp[0]=0;          //sa-ba-=0;
	serverminushp[1]=0;          //sa-ba-=0;
}


int *map::get_Base(Team enemyteam){
	return baseno[enemyteam];
}

void map::minus_BaseHp(Team attacedteam,float atk){
	basehp[attacedteam]-=atk;
}

void map::Initialize(){
	for(int i=0;i<NoneTeam;i++)
		basehp[i]=basemaxhp[i]=BASEHP;

	for(int i=0;i<NoneTeam;i++)
		for(int j=0;j<BASENUM;j++)
			baseno[i][j]=-1;

	set_Base(RedTeam,13);
	set_Base(BlueTeam,14);
}

void map::DrawInitialize(){
	char *flname=(char*)"Data/charamodel/拠点/castle3_RED.mqo";
	basemodel[0]=mqoCreateModel(flname,0.015);
	flname=(char*)"Data/charamodel/拠点/castle3_exp.mqo";
	basemodel[1]=mqoCreateModel(flname,0.015);

	//描画初期化関数
	handle[0] = image_Load("Data/image/capture2.png");
	handle[1] = image_Load("Data/image/tile.jpg");
	handle[2] = image_Load("Data/image/wall_stone.jpg");
	handle[3] = image_Load("Data/image/gradation_blue.jpg");
	handle[4] = image_Load("Data/image/check_blue.jpg");
	handle[5] = image_Load("Data/image/bricks.jpg");
	handle[6] = image_Load("Data/image/13.jpg");
	//<<<<<<< HEAD
	//	handle[7] = image_Load("Data/image/14.jpg");

	img[0]=image_Load("Data/skybox/skyX53+x.png");
	img[1]=image_Load("Data/skybox/skyX53-x.png");
	img[2]=image_Load("Data/skybox/skyX53+y.png");
	img[3]=image_Load("Data/skybox/skyX53-y.png");
	img[4]=image_Load("Data/skybox/skyX53+z.png");
	img[5]=image_Load("Data/skybox/skyX53-z.png");
	//=======
	handle[7] = image_Load("Data/image/bricks_red.jpg");
	handle[8] = image_Load("Data/image/tile.jpg");
	handle[9] = image_Load("Data/image/bricks_blue.jpg");
	handle[10] = image_Load("Data/image/bricks_purple.jpg");
	//>>>>>>> refs/heads/map_develop

	//床
	obj[0].set_imgno(handle[8],50);

	obj[1].set_imgno(handle[1],100);
	obj[2].set_imgno(handle[1],100);
	obj[3].set_imgno(handle[1],100);
	obj[4].set_imgno(handle[1],100);

	obj[6].set_imgno(handle[1],100);

	//追加??
	obj[7].set_imgno(handle[1],100);

	//壁
	obj[9].set_imgno(handle[2],50);
	obj[10].set_imgno(handle[2],50);
	obj[11].set_imgno(handle[2],50);
	obj[12].set_imgno(handle[2],50);

	//拠点横の高台
	obj[17].set_imgno(handle[5],100);
	obj[19].set_imgno(handle[5],100);

	//拠点横の高台へ登るエレベーター
	obj[18].set_imgno(handle[1],100);
	obj[20].set_imgno(handle[1],100);

	//中央柱
	obj[21].set_imgno(handle[4],100);
	//天空足場
	obj[22].set_imgno(handle[4],100);
	//螺旋階段
	obj[23].set_imgno(handle[3],100);
	obj[24].set_imgno(handle[3],100);
	obj[25].set_imgno(handle[3],100);
	obj[26].set_imgno(handle[3],100);
	obj[27].set_imgno(handle[3],100);
	obj[28].set_imgno(handle[3],100);
	obj[29].set_imgno(handle[3],100);
	obj[30].set_imgno(handle[3],100);
	obj[31].set_imgno(handle[3],100);
	obj[32].set_imgno(handle[3],100);

	obj[33].set_imgno(handle[4],100);

	//天空足場へのエレベーター
	obj[34].set_imgno(handle[3],100);

	//赤拠点を囲む壁
	obj[49].set_imgno(handle[7],100);
	obj[50].set_imgno(handle[7],100);
	obj[51].set_imgno(handle[7],100);
	obj[52].set_imgno(handle[7],100);
	obj[53].set_imgno(handle[7],100);

	//赤拠点側壁
	obj[63].set_imgno(handle[7],100);
	obj[64].set_imgno(handle[7],100);
	obj[65].set_imgno(handle[7],100);
	obj[66].set_imgno(handle[7],100);
	obj[67].set_imgno(handle[7],100);
	obj[68].set_imgno(handle[7],100);
	obj[69].set_imgno(handle[7],100);
	obj[70].set_imgno(handle[7],100);
	obj[71].set_imgno(handle[7],100);
	obj[72].set_imgno(handle[7],100);
	obj[73].set_imgno(handle[7],100);

	//青拠点を囲む壁
	obj[74].set_imgno(handle[9],100);
	obj[75].set_imgno(handle[9],100);
	obj[76].set_imgno(handle[9],100);
	obj[77].set_imgno(handle[9],100);
	obj[78].set_imgno(handle[9],100);

	//青拠点側壁
	obj[79].set_imgno(handle[9],100);
	obj[80].set_imgno(handle[9],100);
	obj[81].set_imgno(handle[9],100);
	obj[82].set_imgno(handle[9],100);
	obj[83].set_imgno(handle[9],100);
	obj[84].set_imgno(handle[9],100);
	obj[85].set_imgno(handle[9],100);
	obj[86].set_imgno(handle[9],100);
	obj[87].set_imgno(handle[9],100);
	obj[88].set_imgno(handle[9],100);
	obj[89].set_imgno(handle[9],100);

	//中央広場の壁
	obj[41].set_imgno(handle[4],100);
	obj[42].set_imgno(handle[4],100);
	obj[43].set_imgno(handle[4],100);
	obj[44].set_imgno(handle[4],100);
	obj[45].set_imgno(handle[4],100);
	obj[46].set_imgno(handle[4],100);


	//柱群
	obj[54].set_imgno(handle[4],100);
	obj[55].set_imgno(handle[4],100);
	obj[56].set_imgno(handle[4],100);
	obj[57].set_imgno(handle[4],100);
	obj[58].set_imgno(handle[4],100);
	obj[59].set_imgno(handle[4],100);
	obj[60].set_imgno(handle[4],100);
	obj[61].set_imgno(handle[4],100);

	//中央広場の床
	obj[90].set_imgno(handle[4],100);

	//左右壁
	obj[47].set_imgno(handle[5],100);
	obj[48].set_imgno(handle[5],100);

	//天井
	obj[62].set_imgno(handle[6],10);

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
	//obj[4].move(2*dir,0,0);
	//obj[4].move(0,2*dir,0);


	obj[35].move(3.5*dirs[1],0,0);

	//天空足場へのエレベーター
	obj[34].move(0,2.0*dirs[1],0);

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

void map:: DrawBase(){
	glPushMatrix();
	glTranslated(obj[13].get_m_Pos().x,obj[13].get_m_Pos().y,obj[13].get_m_Pos().z);
	mqoCallModel(basemodel[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslated(obj[14].get_m_Pos().x,obj[14].get_m_Pos().y,obj[14].get_m_Pos().z);
	mqoCallModel(basemodel[1]);
	glPopMatrix();

}

void map::Draw(){

	image_DrawExRota3D(img[0],vec3(-512,0,0),90,vec3(0,1,0),1);
	image_DrawExRota3D(img[1],vec3(512,0,0),-90,vec3(0,1,0),1);

	image_DrawExRota3D(img[2],vec3(0,512,0),90,vec3(1,0,0),1);
	image_DrawExRota3D(img[3],vec3(0,-512,0),-90,vec3(1,0,0),1);

	image_DrawExRota3D(img[4],vec3(0,0,512),180,vec3(0,1,0),1);
	image_DrawExRota3D(img[5],vec3(0,0,-512),0,vec3(0,1,0),1);

	DrawBase();

	for(int i=0;get_objnum()>i;i++)
		obj[i].Draw();


	//フィールド内に3D画像表示
	//image_DrawExRota3D(handle[0],0,9,0,0.1);
}
