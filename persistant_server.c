#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  while(1){
    from_client = server_handshake( &to_client );
    printf("from_client is %d\n", from_client);

    //printf("toclient is %d\n", to_client);
    //printf("fromclient is %d\n", from_client);
    while (1){
      int random;
      int reading;
      reading = open("/dev/urandom", O_RDONLY, 0666);
      read(reading, &random, 4);
      //random = 500;
      if (random < 0){
        random = random * -1;
      }
      random %= 100;
      int w;
      printf("123");
      w = write(to_client, &random, 4);
      printf("123");
      if (w == -1){
        err();
      }
      printf("sent: %d\n", random);
      printf("123");
      sleep(1);
    }
  }
  printf("outside\n");
}
