#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}
int server_setup() {
  char * known = "./known";
  mkfifo(known, 0666);
  int from_client;
  from_client = open(known, O_RDONLY, 0666);
  remove(known);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  from_client = server_setup();
  if (from_client == -1){
    err();
  }
  char buffer[256];
  int bytesread;
  bytesread = read(from_client, buffer, sizeof(buffer));
  if (bytesread == -1){
    err();
  }
  int random = atoi(buffer);
  random++;
  char ack[100];
  sprintf(ack, "%d", random);
  *to_client = open(buffer, O_WRONLY, 0666);
  write(*to_client, ack, sizeof(ack));
  bytesread = read(from_client, buffer, sizeof(buffer));
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char * private = "./private";
  mkfifo(private, 0666);
  char * known = "./known";
  *to_server = open(known, O_WRONLY, 0666);
  if (*to_server == -1){
    err();
  }
  int w;
  w = write(*to_server, private, strlen(private));
  if (w == -1){
    err();
  }
  int pp;
  pp = open(private, O_RDONLY, 0666);
  int read1;
  int num;
  read1 = read(pp, &num, 4);
  if (readrandom == -1){
    err();
  }
  close(pp);
  num++;
  int sprint;
  char buffer[256];
  sprint = sprintf(buffer, "%d", num);
  if (sprint == -1){
    err();
  }
  from_server = open(known, O_WRONLY, 0666);
  if (from_server == -1){
    err();
  }
  int write1;
  write1 = write(from_server, buffer, sizeof(buffer));
  if (write1 == -1){
    err();
  }
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
