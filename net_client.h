/*
 * net_client.h
 *
 *  Created on: 2016/12/02
 *      Author: c501506026
 */

#ifndef NET_CLIENT_H_
#define NET_CLIENT_H_

#include "net_common.h"

extern player player1;

extern void client_start(void);
extern int control_requests ();


extern int get_bulletdata(S_CONTAINER);
extern int get_playerdata(S_CONTAINER);


#endif /* NET_CLIENT_H_ */
