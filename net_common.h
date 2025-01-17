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
#define MOBNUM 10



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
	vec3 pos;
	vec3 angles;
}wall2;//Wall互換

typedef struct{
	int count;
	//int shooter;
	vec3 pos;
	//v3 dir;
	vec3 angles;
}shot2;//Shot互換

typedef struct{
	shot2 mobbullet[MOBMAXBULLET];
	vec3 position;//位置
	vec3 angles;//向き
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
	int cid;//ID
	char name[MAX_LEN_NAME];//名前
	int sock;
	struct sockaddr_in addr;
}CLIENT;



typedef struct{
	float hp;//HP
	int atk;//攻撃力
	vec3 position;//位置
	vec3 angles;//向き
	vec3 lookat;//視点
	wall2 mywall[WALLMAX];
	Team myteam;
	Role myrole;
	vec3 delmove;//慣性による移動
}PLAYER_DATA;

typedef struct{
	int shooter;
	//int num;
	shot2 bullet_info[MAXBULLET];
	//TODO   要素数の設定
	//弾によるhpマイナス値
	float minusmobhp[MOBNUM];
	float minusbasehp[2];
	float minusplayerhp[MAX_CLIENTS];		//クライアント数-1の配列予定
}BULLET_DATA;

//サーバーからクライアントに送信されるデータ
typedef struct{
	char command;//コマンド
	PLAYER_DATA players[MAX_CLIENTS];
	BULLET_DATA bullets[MAX_CLIENTS];
	wall2 walls[MAX_CLIENTS][WALLMAX];
	Mapobj movablemapobj[MOVABLE];
	mob2 mob[MOBNUM];
	float basehp[2];
	bool start[MAX_CLIENTS];
	int countdowntime;   //制限時間
}S_CONTAINER;

//クライアントからサーバーに送信されるデータ
typedef struct{
	char command;//コマンド
	bool start;  //decide team
	PLAYER_DATA my_player;
	BULLET_DATA my_bullet;
}C_CONTAINER;

#endif /* NET_COMMON_H_ */
