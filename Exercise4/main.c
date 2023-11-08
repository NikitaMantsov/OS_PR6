#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_CATALAN_NUMBERS 10

unsigned long long catalanNumbers[NUM_CATALAN_NUMBERS];

unsigned long long calculateCatalanNumber(int n) {
    if (n <= 1) {
        return 1;
    }

    unsigned long long result = 0;
    for (int i = 0; i < n; i++) {
        result += calculateCatalanNumber(i) * calculateCatalanNumber(n - i - 1);
    }

    return result;
}

int isPrime(unsigned long long num) {
    if (num <= 1) {
        return 0;
    }
    if (num <= 3) {
        return 1;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    }

    for (unsigned long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

void* calculateCatalanThread(void* arg) {
    for (int i = 0; i < NUM_CATALAN_NUMBERS; i++) {
        catalanNumbers[i] = calculateCatalanNumber(i);
    }
    pthread_exit(NULL);
}

void* calculatePrimesThread(void* arg) {
    for (int i = 0; i < NUM_CATALAN_NUMBERS; i++) {
        int primeCount = 0;
        for (unsigned long long num = 2; num < catalanNumbers[i]; num++) {
            if (isPrime(num)) {
                primeCount++;
            }
        }
        printf("Catalan Number: %llu, Total Primes: %d\n", catalanNumbers[i], primeCount);
    }
    pthread_exit(NULL);
}

pthread_t catalanThread, primesThread;

int main() {
    if (pthread_create(&catalanThread, NULL, calculateCatalanThread, NULL) != 0) {
        perror("pthread_create for catalanThread");
        exit(1);
    }

    if (pthread_create(&primesThread, NULL, calculatePrimesThread, NULL) != 0) {
        perror("pthread_create for primesThread");
        exit(1);
    }

    if (pthread_join(catalanThread, NULL) != 0) {
        perror("pthread_join for catalanThread");
        exit(1);
    }

    if (pthread_join(primesThread, NULL) != 0) {
        perror("pthread_join for primesThread");
        exit(1);
    }

    return 0;
}