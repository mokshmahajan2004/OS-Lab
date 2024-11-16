#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_THREADS 4    // Number of threads
#define MAX_ACCESS 2     // Maximum threads allowed in the critical section at a time
sem_t semaphore;  // Semaphore to control access to the critical section
// Function for each thread
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d: Waiting to enter the critical section...\n", thread_id);
    sem_wait(&semaphore);  // Wait for access to the critical section
    // Critical Section
    printf("Thread %d: Entered the critical section.\n", thread_id);
    sleep(2);  // Simulate work in the critical section
    printf("Thread %d: Leaving the critical section.\n", thread_id);

    sem_post(&semaphore);  // Signal that the critical section is free

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the semaphore to allow MAX_ACCESS threads
    sem_init(&semaphore, 0, MAX_ACCESS);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    printf("All threads have completed.\n");
    return 0;
}
