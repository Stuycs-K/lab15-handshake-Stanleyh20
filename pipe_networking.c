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
  printf("1. make wkp\n");
  int from_client;
  from_client = open(known, O_RDONLY, 0666);
  if (from_client == -1){
    printf("fromclient\n");
    err();
  }
  printf("2. open wkp\n");
  remove(known);
  printf("4. remove wkp\n");
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
  char* buffer = calloc(256, sizeof(char));
  int bytesread;
  bytesread = read(from_client, buffer, 256);
  printf("5. read syn from pp\n");
  char* ack = "bibimbop";
  *to_client = open(buffer, O_WRONLY, 0666);
  printf("6. open %s\n", buffer);
  int asdfjkl;
  asdfjkl = write(*to_client, ack, strlen(ack));
  printf("7. sending bibimbop\n");
  bytesread = read(from_client, buffer, sizeof(buffer));
  printf("9. received response\n");
  free(buffer);
  return from_client;
}
int server_handshake_half(int *to_client, int from_client){
  char* buffer = calloc(256, sizeof(char));
  int bytesread;
  bytesread = read(from_client, buffer, 256);
  printf("5. read syn from pp\n");
  char* ack = "bibimbop";
  *to_client = open(buffer, O_WRONLY, 0666);
  printf("6. open %s\n", buffer);
  int asdfjkl;
  asdfjkl = write(*to_client, ack, strlen(ack));
  printf("7. sending bibimbop\n");
  bytesread = read(from_client, buffer, sizeof(buffer));
  printf("9. received response\n");
  free(buffer);
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
  int from_server;
  char private[100];
  sprintf(private, "./%d", getpid());
  mkfifo(private, 0666);
  printf("3. make pp\n");
  char * known = "./known";
  *to_server = open(known, O_WRONLY, 0666);
  printf("3. open wkp\n");
  if (*to_server == -1){
    err();
  }
  int w;
  w = write(*to_server, private, strlen(private));
  printf("3. wrote private pipe to wkp\n");
  from_server = open(private, O_RDONLY, 0666);
  printf("3. open pp\n");
  int r;
  char buffer[100];
  r = read(from_server, buffer, sizeof(buffer));
  printf("8. read synack\n");
  int write1;
  write1 = write(*to_server, buffer, sizeof(buffer));
  printf("8. send back ack\n");
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
