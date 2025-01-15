#include<pthread.h>
#include<stdio.h>

#define THREAD_COUNT 10

#define OUTPUT_LEN THREAD_COUNT * 10
char output[OUTPUT_LEN];

void *thread_fn(void *vargp) {
  int id = (int) vargp;

  while(1) {
    for(int i = id * 10; i < id * 10 + 10; i++) {
      output[i] = id + '0';
    }

    for(int i = id * 10; i < id * 10 + 10; i++) {
      output[i] = ' ';
    }
  }
  
  for(int i = 0; i < id; i++) {
    printf(" ");
  }
  printf("hi I am a thread\n");

  return NULL;
}

int main() {
  pthread_t threads[THREAD_COUNT];

  for(int i = 0; i < THREAD_COUNT; i++) {
    pthread_create(&threads[i], NULL, thread_fn, (void *) i);
  }

  while(1) {
    printf("\r");
    for(int i = 0; i < OUTPUT_LEN; i++) {
      printf("%c", output[i]);
    }
    //printf("\n");
  }

  for(int i = 0; i < THREAD_COUNT; i++) {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}
