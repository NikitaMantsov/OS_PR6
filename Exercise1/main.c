#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_ITERATIONS 10
#define SLEEP_TIME 2

void *childThreadFunction(void *arg) {
    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(SLEEP_TIME);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t childThread;

    if (pthread_create(&childThread, NULL, childThreadFunction, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(SLEEP_TIME);
    }

    if (pthread_join(childThread, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    return 0;
}
