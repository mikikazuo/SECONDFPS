/**********************
クライアント
ネットワーク設定と送受信
***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#include "net_common.h"
#include "net_client.h"

#include "Game.h"
#include "player.h"

static int num_clients;
static int myid;
static int sock;
static int num_sock;
static fd_set mask;
static CLIENT clients[MAX_CLIENTS];

void client_start();
void setup_client(char *, u_short);
int control_requests();
void terminate_client();


//static int input_command(void);
static int execute_command(void);
static void send_data(void *, int);
static int receive_data(void *, int);
void handle_error();


//ネットワーク接続の確立
void setup_client(char *server_name, u_short port) {
  struct hostent *server;
  struct sockaddr_in sv_addr;

  fprintf(stderr, "Trying to connect server %s (port = %d).\n", server_name, port);
  if ((server = gethostbyname(server_name)) == NULL) {
	  perror("gethostbyname()");
    handle_error();
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    handle_error();
  }

  sv_addr.sin_family = AF_INET;
  sv_addr.sin_port = htons(port);
  sv_addr.sin_addr.s_addr = *(u_int *)server->h_addr_list[0];

  if(connect(sock, (struct sockaddr *)&sv_addr, sizeof(sv_addr)) != 0) {
    handle_error();
  }

  fprintf(stderr, "Input your name: ");
  char user_name[MAX_LEN_NAME];
//  if(fgets(user_name, sizeof(user_name), stdin) == NULL) {
//    handle_error();
//  }
  user_name[0]='a';
  user_name[strlen(user_name) - 1] = '\0';
  send_data(user_name, MAX_LEN_NAME);

  fprintf(stderr, "Waiting for other clients...\n");
  receive_data(&num_clients, sizeof(int));
  fprintf(stderr, "Number of clients = %d.\n", num_clients);
  receive_data(&myid, sizeof(int));
  fprintf(stderr, "Your ID = %d.\n", myid);
  int i;
  for(i = 0; i < num_clients; i++) {
    receive_data(&clients[i], sizeof(CLIENT));
  }

  for(i=0;i<num_clients;i++){
	  printf("clients[%d] = %s \n",i,clients[i].name);
  }

  num_sock = sock + 1;
  FD_ZERO(&mask);
  FD_SET(0, &mask);
  FD_SET(sock, &mask);
}

//ネットワークのはじまり
void client_start(void){
	 u_short port = PORT;
	 char server_name[MAX_LEN_NAME];

	 sprintf(server_name,"clpc019");

	 setup_client(server_name,port);
}


//データの受け渡しコントロール
int control_requests () {
  fd_set read_flag = mask;

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 30;

  if(select(num_sock, (fd_set *)&read_flag, NULL, NULL, &timeout) == -1) {
    handle_error();
  }
  //printf("select():\n");
  int result = 1;
  //データが送られてきたなら実行
  if (FD_ISSET(sock, &read_flag)) {
    result = execute_command();
  }

  //データを送信
  C_CONTAINER cdata;
  static int A = 300;
  memset(&cdata,0,sizeof(C_CONTAINER));
  cdata.my_bullet.num = 1;
  cdata.my_bullet.bullet_info.count = A--;
  cdata.command = DATA;

  player me = player1;
  cdata.my_player.position.x = me.position.x;
  cdata.my_player.position.y = me.position.y;
  cdata.my_player.position.z = me.position.z;

  cdata.my_player.angles.x = me.angles.x;
  cdata.my_player.angles.y = me.angles.y;
  cdata.my_player.angles.z = me.angles.z;

  cdata.my_player.lookat.x = me.lookat.x;
  cdata.my_player.lookat.y = me.lookat.y;
  cdata.my_player.lookat.z = me.lookat.z;

  cdata.my_player.playerhead_collider.x = me.playerhead_collider.x;
  cdata.my_player.playerhead_collider.y = me.playerhead_collider.y;
  cdata.my_player.playerhead_collider.z = me.playerhead_collider.z;

  cdata.my_player.player_colider.x = me.player_collider.x;
  cdata.my_player.player_colider.y = me.player_collider.y;
  cdata.my_player.player_colider.z = me.player_collider.z;


  //printf("x=%f\n",me.position.x);
  send_data(&cdata,sizeof(cdata));

  return result;
}

//さーばーからのデータ受け取り
//データコマンドのチェック&データの処理
static int execute_command() {
  S_CONTAINER data;
  int result = 1;
  memset(&data, 0, sizeof(S_CONTAINER));//コンテナリセット
  receive_data(&data, sizeof(data));//データ受け取り

  switch (data.command) {
  case QUIT_GAME:
	  result=0;
	  break;
  case DATA://データを受信した.

	  //*****************ここで各オブジェクトの変数を書き換え
	  get_bulletdata(data);
	  get_playerdata(data);
	  break;
  default:
    fprintf(stderr, "execute_command(): %c is not a valid command.\n", data.command);
    exit(1);
  }
  return result;
}

static void send_data(void *data, int size) {
  if ((data == NULL) || (size <= 0)) {
        fprintf(stderr, "send_data(): data is illeagal.\n");
	exit(1);
  }

  if(write(sock, data, size) == -1) {
    handle_error();
  }
}

//データの受け取り
static int receive_data(void *data, int size) {
  if ((data == NULL) || (size <= 0)) {
        fprintf(stderr, "receive_data(): data is illeagal.\n");
	exit(1);
  }

  return(read(sock, data, size));
}


//エラー表示
void handle_error() {
  printf("エラーです...\n");
  fprintf(stderr, "%d\n", errno);
  exit(1);
}
