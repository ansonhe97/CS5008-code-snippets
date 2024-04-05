#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int globalCounter = 0;

// locks
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void* task() {
    pthread_mutex_lock(&mutex1);
    globalCounter++;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

#define NUM_THREAD 10000

int main() {
    pthread_t threadIDs[NUM_THREAD];

    for (int i=0; i<NUM_THREAD; i++) {
        pthread_create(&threadIDs[i], NULL, task, NULL);
    }
    for (int i=0; i<NUM_THREAD; i++) {
        pthread_join(threadIDs[i], NULL);
    }
    printf("%d\n", globalCounter);
    return 0;
}