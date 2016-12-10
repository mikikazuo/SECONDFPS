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
	v3 obj_pos;
	v3 obj_size;
	v3 obj_rot;
}wall2;//Wall互換

typedef struct{
	int count;
	int shooter;
	v3 pos;
	v3 dir;
}shot2;//Shot互換

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
	int num;
	shot2 bullet_info;
}BULLET_DATA;

//サーバーからクライアントに送信されるデータ
typedef struct{
	char command;//コマンド
	PLAYER_DATA players[MAX_CLIENTS];
	BULLET_DATA bullets[MAXBULLET];
}S_CONTAINER;

//クライアントからサーバーに送信されるデータ
typedef struct{
	char command;//コマンド
	PLAYER_DATA my_player;
	BULLET_DATA my_bullet;
}C_CONTAINER;

#endif /* NET_COMMON_H_ */
