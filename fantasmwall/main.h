/*
 * main.h
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "fps.h"
#include "SceneMgr.h"



 fps get_mainfps();
int *get_argc();
char** get_argv();
SceneMgr get_SceneMgr();

#endif /* MAIN_H_ */