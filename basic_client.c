#include "pipe_networking.h"

static void sighandler(int signo){
  if (signo == SIGINT){
    close(4);
    close(3);
    char buffer[100];
    sprintf(buffer, "./%d", getpid());
    remove(buffer);
    exit(0);
  }
}
int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while (1){
    signal(SIGINT,sighandler);
    int random;
    int r;
    r = read(from_server, &random, 4);
    if (r == 0){
      printf("Didn't receive any integer. Breaking...\n");
      char buffer[100];
      sprintf(buffer, "./%d", getpid());
      remove(buffer);
      break;
    }
    printf("Received integer: %d\n", random);
    sleep(1);
  }
}
