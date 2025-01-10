#include "pipe_networking.h"

static int count = 0;
static void sighandler(int signo){

  if (signo == SIGINT){
    remove("known");
    exit(0);
  }
  if (signo == SIGPIPE){
    count++;
  }
}
int main() {
  int to_client;
  int from_client;
  while(1){
    from_client = server_handshake( &to_client );
    while (count == 0){
      signal(SIGINT, sighandler);
      signal(SIGPIPE, sighandler);
      int random;
      int reading;
      reading = open("/dev/urandom", O_RDONLY, 0666);
      int r;
      r = read(reading, &random, 4);
      random = abs(random) % 100;
      int w;
      w = write(to_client, &random, 4);
      if (count == 0){
        printf("sent: %d\n", random);
      }
      sleep(1);
    }
    count = 0;
  }
  
  printf("outside\n");
}
