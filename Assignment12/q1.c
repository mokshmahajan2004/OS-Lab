#include <stdio.h>
#include <pthread.h>

#define NUM_ITERATIONS 100

// Shared counter
int counter = 0;

// Mutex for synchronization
pthread_mutex_t counter_mutex;

// Function executed by each thread
void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Lock the mutex before modifying the counter
        pthread_mutex_lock(&counter_mutex);

        // Critical section
        counter++;

        // Unlock the mutex after modifying the counter
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

    // Create two threads
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    // Print the final counter value
    printf("Final Counter Value: %d\n", counter);

    return 0;
}
