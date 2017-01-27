/*
 * get_data.h
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */

#ifndef GET_DATA_H_
#define GET_DATA_H_

#include "net_common.h"

void get_teamnum(int id,C_CONTAINER cdata,S_CONTAINER *sdata);
void get_walldata(int id,C_CONTAINER cdata,S_CONTAINER *sdata);
int get_playerdata(int id,C_CONTAINER cdata,S_CONTAINER *sdata);
void set_MapData(int id,S_CONTAINER* sdata);
void set_MobData(int id,S_CONTAINER* sdata);

#endif /* GET_DATA_H_ */
