/*
 * server_main.h
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */

#ifndef SERVER_MAIN_H_
#define SERVER_MAIN_H_

#include "mob.h"

extern void Update();
extern fps get_mainfps();
map *get_mapobj();
mob *get_mober();
bullet *get_playerbullets();
int get_mobernum();
player *get_player();
int get_countdowntime();
#endif /* SERVER_MAIN_H_ */