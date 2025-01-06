#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1){
    int random;
    read(from_server, &random, 4);
    printf("Received integer: %d\n", random);
    sleep(1);
  }
}
