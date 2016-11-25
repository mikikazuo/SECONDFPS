/**********************
クライアント
ネットワーク設定と送受信
***********************/

#include <net_common.h>

#define MAX_LEN_NAME 256

static int num_clients;
static int myid;
static int sock;
static int num_sock;
static fd_set mask;
static CLIENT clients[MAX_NUM_CLIENTS];

void client_start();
void setup_client(char *, u_short);
int control_requests();
void terminate_client();


static int input_command(void);
static int execute_command(void);
static void send_data(void *, int);
static int receive_data(void *, int);
static void handle_error(char *);


//ネットワーク接続の確立
void setup_client(char *server_name, u_short port) {
  struct hostent *server;
  struct sockaddr_in sv_addr;

  fprintf(stderr, "Trying to connect server %s (port = %d).\n", server_name, port);
  if ((server = gethostbyname(server_name)) == NULL) {
    handle_error("gethostbyname()");
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    handle_error("socket()");
  }

  sv_addr.sin_family = AF_INET;
  sv_addr.sin_port = htons(port);
  sv_addr.sin_addr.s_addr = *(u_int *)server->h_addr_list[0];

  if(connect(sock, (struct sockaddr *)&sv_addr, sizeof(sv_addr)) != 0) {
    handle_error("connect()");
  }

  fprintf(stderr, "Input your name: ");
  char user_name[MAX_LEN_NAME];
  if(fgets(user_name, sizeof(user_name), stdin) == NULL) {
    handle_error("fgets()");
  }
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

  num_sock = sock + 1;
  FD_ZERO(&mask);
  FD_SET(0, &mask);
  FD_SET(sock, &mask);
}

//ネットワークのはじまり
void client_start(void){
	 u_short port = PORT;
	 char server_name[MAX_LEN_NAME];

	 sprintf(server_name,"local_host");

	 setup_client(port,server_name);
}


//データの受け渡しコントロール
int control_requests () {
  fd_set read_flag = mask;

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 30;

  if(select(num_sock, (fd_set *)&read_flag, NULL, NULL, &timeout) == -1) {
    handle_error("select()");
  }

  int result = 1;
  //データが送られてきたなら実行
  if (FD_ISSET(sock, &read_flag)) {
    result = execute_command();
  }

  //データを送信


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
    handle_error("write()");
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
static void handle_error(char *message) {
  perror(message);
  fprintf(stderr, "%d\n", errno);
  exit(1);
}
