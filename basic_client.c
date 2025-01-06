#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  //printf("toserver is %d\n", to_server);
  //printf("fromserver is %d\n", from_server);
  while (1){
    int random;
    int r;
    r = read(from_server, &random, 4);
    if (r == -1){
      printf("r == -1\n");
      err();
    }
    printf("Received integer: %d\n", random);
    sleep(1);
  }
}
