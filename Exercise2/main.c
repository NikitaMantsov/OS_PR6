#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadParams {
    char* name;
    char* str;
    int num;
};

void* thread_function(void* args) {
    struct ThreadParams* params = (struct ThreadParams*)args;

    for (int i = 1; i <= params->num; i++) {
        printf("Thread %s. %s %d\n", params->name, params->str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    struct ThreadParams thread_params[4] = {
            {"Thread 1", "STR_1", 5},
            {"Thread 2", "STR_2", 3},
            {"Thread 3", "STR_3", 4},
            {"Thread 4", "STR_4", 6}
    };

    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, (void*)&thread_params[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}