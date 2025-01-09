#include "pipe_networking.h"

static void sighandler(int signo){
  if (signo == SIGINT){
    remove("known");
    exit(0);
  }
}
int main() {
  int to_client;
  int from_client;

  while(1){
    from_client = server_handshake( &to_client );
    while (1){
      printf("toclient is 4: %d\n", to_client == 4);
      printf("fromclient is 3: %d\n", from_client == 3);
      printf("toclient is %d\n", to_client);
      //printf("fromclient is %d\n", from_client);
      printf("sdfjkl");
      int random;
      int reading;
      reading = open("/dev/urandom", O_RDONLY, 0666);
      int r;
      r = read(reading, &random, 4);
      //random = 500;
      if (random < 0){
        random = random * -1;
      }
      random %= 100;
      int w;
      w = write(to_client, &random, 4);
      printf("w = %d\n", w);
      if (w == -1){
        err();
      }
      printf("sent: %d\n", random);
      sleep(1);
    }
    close(to_client);
    close(from_client);
  }
  signal(SIGINT, sighandler);
  printf("outside\n");
}
