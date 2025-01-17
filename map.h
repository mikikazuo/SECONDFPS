/*
 * map.h
 *
 *  Created on: 2016/11/11
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#define BASENUM 6			//拠点の当たり判定の数
#define BASEHP 100
#include "object.h"

//追加??
//マップ(正方形状の移動可能範囲)の1辺の長さ
#define MAP_ONESIDE 100
//マップのx座標の長さ(縦)
#define MAP_X_LENGTH 100
//マップz座標の長さ(横)
#define MAP_Z_LENGTH 100

//壁の厚み
#define WALL_THICKNESS 2
//壁の高さ
#define WALL_HEIGHT 30

//拠点のx座標の長さ(縦)
#define BASE_X_LENGTH 3
//拠点のy座標の長さ(高さ)
#define BASE_Y_LENGTH 4
//拠点のz座標の長さ(横)
#define BASE_Z_LENGTH 3

#define MOVABLE 20
typedef enum{
	RedTeam,
	BlueTeam,
	NoneTeam
}Team;

class map {
private:
	int handle[20];
public:

	float basehp[NoneTeam];
	float basemaxhp[NoneTeam];
	int baseno[NoneTeam][BASENUM];			//object配列の何番目が拠点かどうかを保存

	float serverminushp[2];          //sa-ba- red adn blue
	map();
	virtual ~map();
	object *get_obj();
	int get_objnum();

	void set_Base(Team team,int objectno);
	int *get_Base(Team enemyteam);
	void minus_BaseHp(Team attacedteam,float atk);
	void resetminushp();
	void Initialize();
	void DrawInitialize();
	void DrawFinalize();
	void Update();
	void Draw();
	void DrawBase();





};

#endif /* MAP_H_ */
