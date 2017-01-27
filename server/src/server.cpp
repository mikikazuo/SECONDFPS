#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "net_common.h"
#include "server.h"
#include "get_data.h"

#define MAX_LEN_ADDR 256

static CLIENT clients[MAX_CLIENTS];
static int num_clients;
static int num_socks;
static fd_set mask;
static C_CONTAINER cdata;
static S_CONTAINER sdata;
static int readData[MAX_CLIENTS];
static int teamnum[2];
void setup_server(int, u_short);
int control_requests();
void terminate_server();

static void send_data(int, void *, int);
static int receive_data(int, void *, int);
static void handle_error();

void setup_server(int num_cl, u_short port) {
	int rsock, sock = 0;
	struct sockaddr_in sv_addr, cl_addr;

	fprintf(stderr, "Server setup is started.\n");

	num_clients = num_cl;

	rsock = socket(AF_INET, SOCK_STREAM, 0);
	if (rsock < 0) handle_error();
	fprintf(stderr, "sock() for request socket is done successfully.\n");

	sv_addr.sin_family = AF_INET;
	sv_addr.sin_port = htons(port);
	sv_addr.sin_addr.s_addr = INADDR_ANY;

	int opt = 1;
	setsockopt(rsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if (bind(rsock, (struct sockaddr *)&sv_addr, sizeof(sv_addr)) != 0) handle_error();
	fprintf(stderr, "bind() is done successfully.\n");

	if (listen(rsock, num_clients) != 0) handle_error();
	fprintf(stderr, "listen() is started.\n");

	int i, max_sock = 0;
	socklen_t len;
	teamnum[0]=teamnum[1]=0;
	char src[MAX_LEN_ADDR];
	for (i = 0; i < num_clients; i++) {
		len = sizeof(cl_addr);
		sock = accept(rsock, (struct sockaddr *)&cl_addr, &len);
		if (sock < 0) handle_error();

		if (max_sock < sock) max_sock = sock;

		if(read(sock, clients[i].name, MAX_LEN_NAME) == -1) handle_error();
		clients[i].cid = i;
		clients[i].sock = sock;
		clients[i].addr = cl_addr;
		memset(src, 0, sizeof(src));
		inet_ntop(AF_INET, (struct sockaddr *)&cl_addr.sin_addr, src, sizeof(src));
		fprintf(stderr, "Client %d is accepted (name=%s, address=%s, port=%d).\n", i, clients[i].name, src, ntohs(cl_addr.sin_port));
	}

	close(rsock);

	int j;
	for (i = 0; i < num_clients; i++) {
		send_data(i, &num_clients, sizeof(int));
		send_data(i, &i, sizeof(int));
		for (j = 0; j < num_clients; j++) {
			send_data(i, &clients[j], sizeof(CLIENT));
		}
	}

	num_socks = max_sock + 1;
	FD_ZERO(&mask);
	FD_SET(0, &mask);

	for(i = 0; i < num_clients; i++) {
		FD_SET(clients[i].sock, &mask);
	}
	fprintf(stderr, "Server setup is done.\n");

	memset(&sdata,0,sizeof(sdata));
}

int control_requests() {
	fd_set read_flag = mask;
	memset(&cdata, 0, sizeof(C_CONTAINER));

	struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 30;
	//fprintf(stderr, "select() is started.\n");
	if(select(num_socks, (fd_set *)&read_flag, NULL, NULL,&timeout) == -1) {
		handle_error();
		printf("select erro\n");
	}

	int i, result = 1;
	for (i = 0; i < num_clients; i++) {
		if(readData[i]==0)
			if(FD_ISSET(clients[i].sock, &read_flag)) {
				receive_data(i, &cdata, sizeof(cdata));
				//cdata.command = DATA;
				switch(cdata.command) {
				case QUIT_GAME:
					result = 0;
					break;
				case DATA://データを受け取った時
					//*************ここでデータを受け取る.
					get_teamnum(i,cdata,&sdata);
					get_playerdata(i,cdata,&sdata);
					set_MapData(i,&sdata);
					set_MobData(i,&sdata);
					break;
				default:
					fprintf(stderr, "control_requests(): %c is not a valid command.\n", cdata.command);
					exit(1);
				}
				sdata.command = DATA;
				//	int j;
				//	for(j=0;j<40;j++){
				//		sdata.bullets[j].bullet_info.count = 20;
				//	}
				send_data(i,&sdata,sizeof(sdata));

			}

	}

	for(int i=0;i<num_clients;i++){
		if(readData[i]==0)
			break;
		if(i==num_clients-1)
			for(int j=0;j<num_clients;j++)
				readData[j]=0;
	}


	return result;
}



static void send_data(int cid, void *data, int size) {
	if ((cid != BROADCAST) && (0 > cid || cid >= num_clients)) {
		fprintf(stderr, "send_data(): client id is illeagal.\n");
		exit(1);
	}
	if ((data == NULL) || (size <= 0)) {
		fprintf(stderr, "send_data(): data is illeagal.\n");
		exit(1);
	}

	if (cid == BROADCAST) {
		int i;
		for (i = 0; i < num_clients; i++) {
			if (write(clients[i].sock, data, size) < 0) handle_error();
		}
	} else {
	    int len;
	    int n = 0;
	    do{
		if((len = write(clients[cid].sock, data, size-n)) <= 0){
		    /* the opposite side closed the connection */
		  //  close(fd);
			 handle_error();
			 printf("write error:%d\n",n);
		    return ;
		}
		else
		    n += len;
		 printf("write :%d\n",n);
	    } while(n < size);
		//if (write(clients[cid].sock, data, size) < 0) handle_error();
	}
}

static int receive_data(int cid, void *data, int size) {
	if ((cid != BROADCAST) && (0 > cid || cid >= num_clients)) {
		fprintf(stderr, "receive_data(): client id is illeagal.\n");
		exit(1);
	}
	if ((data == NULL) || (size <= 0)) {
		fprintf(stderr, "receive_data(): data is illeagal.\n");
		exit(1);
	}
//
//    int len;
//    int n = 0;
//    do{
//	if((len = read(clients[cid].sock, data, size-n)) <= 0){
//	    /* the opposite side closed the connection */
//	  //  close(fd);
//		 handle_error();
//		 printf("read error:%d\n",n);
//	    return n;
//	}
//	else
//	    n += len;
//	 printf("read:%d\n",n);
//    } while(n < size);
//    return n;

	//return read(clients[cid].sock, data, size);
	return(recv(clients[cid].sock, data, size,MSG_WAITALL));
}

static void handle_error() {
	printf("エラー...\n");
	exit(1);
}

void terminate_server(void) {
	int i;
	for (i = 0; i < num_clients; i++) {
		close(clients[i].sock);
	}
	fprintf(stderr, "All connections are closed.\n");
	exit(0);
}
