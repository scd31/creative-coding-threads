#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define THREAD_COUNT 10

#define OUTPUT_LEN (THREAD_COUNT * 9 * 10)
char *output[OUTPUT_LEN];

char *emojis[] = {"🪡", "🧵", "🧷", "🧶", "🐑", "🦙", "🐪", "👕", "👚", "🌈" };
char *space = "  ";

void *thread_fn(void *vargp) {
  int id = (int) vargp;

  while(1) {
    // Writing to the buffer
    int i = rand() % OUTPUT_LEN;
    output[i] = emojis[id];
    int delay = rand() % 100;
    usleep(delay*1000);

    // Randomly erasing a block of the buffer
    int will_we_wipe = rand() % 10;
    if(will_we_wipe < 1){
      int wipe_location = rand() % OUTPUT_LEN;
      for (int i = wipe_location; i < wipe_location+10 && i  < OUTPUT_LEN; ++i){
        output[i] = space;
      }
    }

    // for(int i = id * 10; i < id * 10 + 10; i++) {
    //   output[i] = ' ';
    // }
  }

  return NULL;
}

int main() {
  pthread_t threads[THREAD_COUNT];
  srand(time(NULL));

  for(int i = 0; i < OUTPUT_LEN; i++){
    output[i] = space;
  }

  for(int i = 0; i < THREAD_COUNT; i++) {
    pthread_create(&threads[i], NULL, thread_fn, (void *) i);
  }

  while(1) {
    // printf("\r");
    usleep(16*1000);
    printf("\e[1;1H\e[2J");
    for(int i = 0; i < OUTPUT_LEN; i++) {
      printf("%s", output[i]);
      if(i%(OUTPUT_LEN/10) == 0) {
        printf("\n");
      }
    }
    printf("\n");
  }

  for(int i = 0; i < THREAD_COUNT; i++) {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}
