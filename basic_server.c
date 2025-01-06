#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );


  printf("toclient is %d\n", to_client);
  printf("fromclient is %d\n", from_client);
  while (1){
    int random;
    int reading;
    reading = open("/dev/urandom", O_RDONLY, 0666);
    read(reading, &random, 4);
    //random = 500;
    //printf("random is: %d\n", random);
    int w;
    w = write(to_client, &random, 4);
    //printf("bytes wrote: %d\n", w);
    if (w == -1){
      err();
    }
    sleep(1);
  }
}
