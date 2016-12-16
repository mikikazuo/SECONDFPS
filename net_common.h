/*
 * server_client.h
 *
 *  Created on: 2016/11/25
 *      Author: c501506026
 */
//***********************************/
//サーバーとクライアントで使用する定数の宣言
//***********************************/
#ifndef NET_COMMON_H_
#define NET_COMMON_H_

#include <netinet/in.h>
#include "player.h"
#include "bullet.h"

#define PORT	(u_short)65531	/* ポート番号 */
#define MAX_CLIENTS	2	/* クライアント数の最大値 */
#define MAX_LEN_NAME 20




//コマンド
#define QUIT_GAME 'Q'//終了コマンド
#define DATA 'D' //データ全般ですよコマンド

#define BROADCAST -1//全送信

typedef struct{
	float x;
	float y;
	float z;
}v3;//vec3互換

typedef struct{
	int count;
	vec3 obj_pos;
	vec3 obj_size;
	vec3 obj_rot;
}wall2;//Wall互換

typedef struct{
	int count;
	//int shooter;
	vec3 pos;
	//v3 dir;
	vec3 angles;
}shot2;//Shot互換

typedef struct{
	shot2 mobbullet;
	vec3 position;//位置
	vec3 angles;//向き
	int myno;//３次元定位オーディオ用の番付
	float hp;
	float maxhp;
	float atk;
}mob2;//Mob互換

typedef struct{
	int objno;  //動かすまたは回転させているオブジェクトの添字
	vec3 position;//位置
	vec3 rotation;//回転
}Mapobj;
typedef struct{
	int basehp;
}Basehp;
typedef struct{
	int cid;//ID
	char name[MAX_LEN_NAME];//名前
	int sock;
	struct sockaddr_in addr;
}CLIENT;



typedef struct{
	int hp;//HP
	int atk;//攻撃力
	v3 position;//位置
	v3 angles;//向き
	v3 lookat;//視点
	v3 playerhead_collider;//プレイヤー頭当たり判定？
	v3 player_colider;//プレイヤー当たり判定？
	wall2 mywall[WALLMAX];
}PLAYER_DATA;

typedef struct{
	int shooter;
	//int num;
	shot2 bullet_info[300];
	float minusmobhp[10];
	float minusbasehp[2];
}BULLET_DATA;

//サーバーからクライアントに送信されるデータ
typedef struct{
	char command;//コマンド
	PLAYER_DATA players[MAX_CLIENTS];
	BULLET_DATA bullets[MAX_CLIENTS];
	Mapobj movablemapobj[50];
	mob2 mob[10];
	Basehp hp[2];
}S_CONTAINER;

//クライアントからサーバーに送信されるデータ
typedef struct{
	char command;//コマンド
	PLAYER_DATA my_player;
	BULLET_DATA my_bullet;
	Basehp minusbasehp[2];
}C_CONTAINER;

#endif /* NET_COMMON_H_ */
