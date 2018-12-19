#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <stdint.h>


#define SIZE 100000000
#define NUM_TESTS 100

double very_long_array[SIZE];
double result = 1;

uint64_t getTime(void) {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return ((uint64_t) (time.tv_sec) * 1000000000 + (uint64_t) (time.tv_nsec));
}

void populate() {
    int i, n = 1;
    for (i = 0; i <	SIZE; i++) {
    	very_long_array[i] = n++;
    }
}

void get_work() {
    int i, j;

    #pragma omp parallel for
    for (i = 0; i < SIZE; i++) {
    	result /= very_long_array[i] / 2;
    }
}

int main() {
	int i;
    uint64_t start, finish, time;
    populate();

    for (i = 0; i < NUM_TESTS; i++) {
    	start = getTime();
	    get_work();
	    finish = getTime();
	    time += (finish - start);
    }
    
    printf("Tempo medio: %ld nanossegundos para %d testes e %d processadores\n", 
    							time/NUM_TESTS, NUM_TESTS, omp_get_num_procs());
    return 0;
}
