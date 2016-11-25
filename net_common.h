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
#include <player.h>
#include <bullet.h>

#define PORT	(u_short)8888	/* ポート番号 */
#define MAX_CLIENTS	8	/* クライアント数の最大値 */

//コマンド
#define QUIT_GAME 'Q'//終了コマンド
#define DATA 'D' //データ全般ですよコマンド

typedef struct{
	int cid;
	int sock;
	struct sockaddr_in addr;
}CLIENT;

typedef struct{
	int hp;//HP
	int atk;//攻撃力
	vec3 position;//位置
	vec3 angles;//向き
	vec3 lookat;//視点
	vec3 playerhead_collider;//プレイヤー頭当たり判定？
	vec3 player_colider;//プレイヤー当たり判定？
	Wall mywall[WALLMAX];
}PLAYER_DATA;

typedef struct{
	Shot bullet_info;
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
