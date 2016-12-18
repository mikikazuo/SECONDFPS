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

using namespace std;

extern void setup_server(int, u_short);
extern int control_requests();
extern void terminate_server();

static SDL_Thread *update;  //ゲーム書利用スレッド
fps mainfps;
map mapobj;
mob mober[10];
bullet playerbullets[MAX_CLIENTS];

static int count;
void Update(){
	count++;
	if(count<60*2)
		return;

	mapobj.Update();

	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++){
		mober[i].Update();
	}
	for(int i=0;i<10;i++){
		get_mober()[i].minushpfunc();
	}

		get_mapobj()->minus_BaseHp();


}

int thread_Update(void *arg){
	mapobj.Initialize();
	mainfps.fps_Initialize();
	for(int i=0;i<(int)(sizeof(mober)/sizeof(mober[0]));i++)
		mober[i].Initialize(i,vec3(-10,2.5f,-5),1,100,1,30,10);

	for(int i=0;i<(int)(sizeof(playerbullets)/sizeof(playerbullets[0]));i++)
		playerbullets[i].bullet_Initialize(Crossbow);
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


