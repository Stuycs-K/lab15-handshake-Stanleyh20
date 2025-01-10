#include "pipe_networking.h"

static void sighandler(int signo){
  if (signo == SIGINT){
    close(4);
    close(3);
    exit(0);
  }
}
int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  printf("toserver is %d\n", to_server);
  printf("fromserver is %d\n", from_server);
  while (1){
    signal(SIGINT,sighandler);
    int random;
    int r;
    r = read(from_server, &random, 4);
    if (r == -1){
      printf("r == -1\n");
      err();
    }
    if (r == 0){
      printf("Didn't receive any integer. Breaking...\n");
      break;
    }
    //printf("r == %d\n", r);
    printf("Received integer: %d\n", random);
    sleep(1);
  }
}
