#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
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
  server_setup();
  int synack;
  char * known = "./known";
  char * private = "./private";
  synack = open(known, O_RDONLY, 0666);
  char buffer[256];
  read(synack, buffer, sizeof(buffer));
  close(synack);
  int random = atoi(buffer);
  random++
  char* ack;
  sprintf(ack, "%d", random);
  int joe;
  joe = open(private, O_WRONLY, 0666);
  write(joe, ack, sizeof(ack));
  int from_client;
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
  int syn;
  char * known = "./known";
  char * pid;
  sprintf(pid, getpid());
  syn = open(known, O_WRONLY, 0666);
  to_server = &syn;
  int w = write(syn, pid, strlen(pid));
  remove(known);
  int from_server;
  char * private = "./private";
  mkfifo(private, 0666);
  char buffer[256];
  int random;
  int * num;
  random = open("/dev/urandom", num, sizeof(num));
  sprintf(buffer, "%d", num)
  from_server = read(private, buffer, sizeof(buffer));
  remove(private);
  close(random);
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
