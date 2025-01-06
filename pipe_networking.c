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
  if (from_client == -1){
    err();
  }
  char* buffer = calloc(256, sizeof(char));
  int bytesread;
  bytesread = read(from_client, buffer, 256);
  printf("5. read syn from pp\n");
  if (bytesread == -1){
    err();
  }
  /*
  else{
    printf("bytesread = %d\n", bytesread);
  }
  */
  char* ack = "bibimbop";
  *to_client = open(buffer, O_WRONLY, 0666);
  if (*to_client == -1){
    printf("length: %ld", strlen(buffer));
    printf("%s\n", buffer);
    err();
  }
  printf("6. open %s\n", buffer);
  int asdfjkl;
  asdfjkl = write(*to_client, ack, strlen(ack));
  if (asdfjkl == -1){
    err();
  }
  printf("7. sending bibimbop\n");
  bytesread = read(from_client, buffer, sizeof(buffer));
  if (bytesread == -1){
    printf("bytes read == bad");
    err();
  }
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
  char * private = "./private";
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
  //printf("strlen(%s) = %ld", private, strlen(private));
  if (w == -1){
    err();
  }
  /*
  else{
    printf("w = %d\n", w);
  }
  */
  printf("3. wrote %s to wkp\n", private);
  from_server = open(private, O_RDONLY, 0666);
  printf("3. open pp\n");
  if (from_server == -1){
    err();
  }
  int r;
  char buffer[100];
  r = read(from_server, buffer, sizeof(buffer));
  if (r == -1){
    err();
  }
  printf("8. read synack\n");
  //int him;
  //him = close(from_server);
  //printf("8. closed pp\n");
  int write1;
  write1 = write(*to_server, buffer, sizeof(buffer));
  printf("8. send back ack\n");
  if (write1 == -1){
    printf("asdfjklajdfl");
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
