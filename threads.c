#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task1(void* arg) {
    if (arg == NULL)
        return NULL;
    int* array = (int*)arg;
    // arg is an array with two values
    int numToRun = array[0];
    int sleepTime = array[1];

    for (int i=0; i<numToRun; i++) {
        sleep(sleepTime);
        printf("%p: Running task1: %d\n", (void*)pthread_self(), i);
    }
    return "Task1 done!";
}

void* task2(void* arg) {
    if (arg == NULL)
        return NULL;
    int* array = (int*)arg;
    // arg is an array with two values
    int numToRun = array[0];
    int sleepTime = array[1];

    for (int i=0; i<numToRun; i++) {
        sleep(sleepTime);
        printf("%p: Running task2: %d\n", (void*)pthread_self(), i);
    }
    return "Task2 done!";
}

int main() {
    pthread_t threadIDs[2];
    int t1[2] = {10, 1};
    int t2[2] = {5, 2};

    pthread_create(&threadIDs[0], NULL, task1, t1);
    pthread_create(&threadIDs[1], NULL, task2, t2);


    void* task1Results;
    void* task2Results;
    pthread_join(threadIDs[0], &task1Results);
    pthread_join(threadIDs[1], &task2Results);

    printf("Task1: %s\n", (char*)task1Results);
    printf("Task2: %s\n", (char*)task2Results);

    return 0;
}