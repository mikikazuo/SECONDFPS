//============================================================================
// Name        : server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "net_common.h"//クライアント側のやつと同一
#include <SDL/SDL.h>
#include "server_main.h"
#include "player.h"
#include "get_data.h"
using namespace std;

extern void setup_server(int, u_short);
extern int control_requests();
extern void terminate_server();

static SDL_Thread *update;  //ゲーム書利用スレッド
fps mainfps;
map mapobj;
mob mober[MOBNUM];
bullet playerbullets[MAX_CLIENTS];
player playerinfo[MAX_CLIENTS];
static bool ini;
static int count;

//カウントダウン
static int countdowntime;

int get_countdowntime(){
	return countdowntime;
}
//制限時間
void countdown(){
	for(int i=0;i<MAX_CLIENTS;i++){
		if(get_player()[i].start==false){
			countdowntime=0;
			break;
		}
		if(countdowntime==0&&i==MAX_CLIENTS-1)
			countdowntime++;
	}
	if(countdowntime>0)
		countdowntime++;
}
void Update(){
	//マップ・モブを全クライアントキャラ設定完了時の初期化
	if(ini==false&&get_initflag()==true){
		mapobj.Initialize();
		for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
			mober[i].Initialize(i,vec3(-10,2.5f,-5),1,100,5,30,10);
		ini=true;
	}

	if(get_initflag()==false)
		ini=false;

	count++;
	if(count<60*2)
		return;

	countdown();

	mapobj.Update();

	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
		mober[i].Update();
	for(int i=0;i<MOBNUM;i++)
		get_mober()[i].minushpfunc();

	get_mapobj()->minus_BaseHp();


}

int thread_Update(void *arg){
	mainfps.fps_Initialize();
	while(1){


		mainfps.UpdateUpDatefps();
		mainfps.fps_UpdateDeltaTime();
		Update();  //更新
		mainfps.wait_Update();

	}

	return 0;
}

int main() {
	int num_cl = MAX_CLIENTS;
	u_short port = PORT;

	fprintf(stderr, "Number of clients = %d\n", num_cl);
	fprintf(stderr, "Port number = %d\n", port);

	//fpsdeltatimeがバグるため絶対いる
	if(SDL_Init(SDL_INIT_EVERYTHING)<0){
		//printf("error");
		exit(-1);
	}

	setup_server(num_cl, port);

	update= SDL_CreateThread(thread_Update,NULL);
	int cond = 1;

	while(cond) {
		cond = control_requests();

	}

	terminate_server();

	return 0;

}

fps get_mainfps(){
	return mainfps;
}
map *get_mapobj(){
	return &mapobj;
}
mob *get_mober(){
	return mober;
}
bullet *get_playerbullets(){
	return playerbullets;
}
int get_mobernum(){
	return (int)(sizeof(mober)/sizeof(mober[0]));
}
player *get_player(){
	return playerinfo;
}
