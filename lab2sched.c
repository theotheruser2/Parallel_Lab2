#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#if defined(_OPENMP)
#include <omp.h>
#define SCHED_TYPE dynamic
#define CHUNK_SIZE 20
#else
int omp_get_thread_num() { return 0; }
#endif

double minArr(double array[], int size) {
    double min = array[0];
    int i;
    #if defined(CHUNK_SIZE)
    #pragma omp parallel for private(i) shared(size, array) reduction(min: min) schedule(SCHED_TYPE, CHUNK_SIZE)
    #elif defined (SCHED_TYPE)
    #pragma omp parallel for private(i) shared(size, array) reduction(min: min) schedule(SCHED_TYPE)
    #endif
    for (i = 0; i < size - 1; i++) {
        if (array[i] < min){
            min = array[i];
        }
    }
    return min;
}

int main(int argc, char *argv[]) {
    #if defined(_OPENMP)
    omp_set_num_threads(16);
    #endif
    int i, N, j;
    unsigned int seed = 1;
    double delta_ms;
    N = atoi(argv[1]); // N равен первому параметру командной строки
    double start; 
    double end; 
    start = omp_get_wtime(); 
    for (i = 0; i < 100; i++) { // 100 экспериментов
        srand(seed);
        // Этап 1
        double M1[N], M2[N/2], M2Copy[N/2];
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(seed, N, M1) schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(seed, N, M1) schedule(SCHED_TYPE)
        #endif

        for (j = 0; j < N; j++) {
            M1[j] = rand_r(&seed) % 240 + 1;
        }
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(seed, N, M2) schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(seed, N, M2) schedule(SCHED_TYPE)
        #endif
        for (j = 0; j < N/2; j++) {
            M2[j] = rand_r(&seed) % 2160 + 240;
        }
        // Этап 2
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(N, M1)  schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(N, M1)  schedule(SCHED_TYPE)
        #endif
        for (j = 0; j < N; j++) {
            M1[j] = cbrt(M1[j]/ exp(1));
        }
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(N, M2, M2Copy) schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(N, M2, M2Copy) schedule(SCHED_TYPE)
        #endif
        for (j = 0; j < N/2; j++) {
            M2Copy[j] = M2[j];
        }
        M2[0] = pow(log10(M2[0]), exp(1));
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(N, M2, M2Copy) schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(N, M2, M2Copy) schedule(SCHED_TYPE)
        #endif
        for (j = 1; j < N/2; j++) {
            M2[j] = pow(log10(M2[j] + M2Copy[j-1]), exp(1));
        }
        // Этап 3
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(N, M2, M1) schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(N, M2, M1) schedule(SCHED_TYPE)
        #endif
        for (j = 0; j < N/2; j++) {
            M2[j] = fabs(M1[j] - M2[j]);
        }
        // Этап 4
        // Этап 5
        double minM2 = minArr(M2, N/2);
        double X = 0;
        j = 0;
        #if defined(CHUNK_SIZE)
        #pragma omp parallel for private(j) shared(N, M2, minM2) reduction(+: X) schedule(SCHED_TYPE, CHUNK_SIZE)
        #elif defined (SCHED_TYPE)
        #pragma omp parallel for private(j) shared(N, M2, minM2) reduction(+: X) schedule(SCHED_TYPE)
        #endif
        for (j = 0; j < N/2; j++) {
            if (fmod(floor(M2[j]/minM2), 2) == 0){
                X += sin(M2[j]);
            }
        }
        printf("%f, ", X);
    }
    end = omp_get_wtime(); 
    delta_ms = (end - start) * 1000;
    printf("%f\n", delta_ms);
    return 0;
}


