#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  while (1){
    int random;
    int reading;
    reading = open("/dev/urandom", O_RDONLY, 0666);
    read(reading, &random, 4);
    printf("random is: %d\n", random);
    write(from_client, &random, 4);
    sleep(1);
  }
}
