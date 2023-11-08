#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define NUM_ITERATIONS 10
#define SLEEP_TIME 2
#define TARGET_NUMBER 2

void *childThreadFunction(void* arg) {
    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(SLEEP_TIME);
    }
    pthread_exit(NULL);
}

void *randomThreadFunction(void* arg) {

    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        int randomValue = rand() % 10;
        printf("Random Thread. Iteration: %d, Random Value: %d\n", i, randomValue);

        if (randomValue == TARGET_NUMBER) {
            printf("Random Thread: Found the target number %d. Exiting.\n", TARGET_NUMBER);
            pthread_exit(NULL);
        }

        sleep(SLEEP_TIME);
    }

    printf("Random Thread: Did not find the target number %d in any iteration.\n");
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t childThread, randomThread;

    if (pthread_create(&childThread, NULL, childThreadFunction, NULL) != 0) {
        perror("pthread_create for childThread");
        exit(1);
    }

    if (pthread_create(&randomThread, NULL, randomThreadFunction, NULL) != 0) {
        perror("pthread_create for randomThread");
        exit(1);
    }

    if (pthread_join(childThread, NULL) != 0) {
        perror("pthread_join for childThread");
        exit(1);
    }

    if (pthread_join(randomThread, NULL) != 0) {
        perror("pthread_join for randomThread");
        exit(1);
    }

    printf("Main Thread: All child threads have finished.\n");

    return 0;
}
