#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;  // Semaphore for synchronization

// Function executed by the first thread
void* task1(void* arg) {
    printf("Thread 1: Starting task...\n");
    sleep(2);  // Simulate task completion with a delay
    printf("Thread 1: Task completed. Signaling Thread 2.\n");
    sem_post(&semaphore);  // Signal Thread 2 to proceed
    return NULL;
}

// Function executed by the second thread
void* task2(void* arg) {
    printf("Thread 2: Waiting for Thread 1 to complete its task...\n");
    sem_wait(&semaphore);  // Wait for Thread 1 to signal
    printf("Thread 2: Resuming after Thread 1's completion.\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the semaphore with an initial value of 0
    sem_init(&semaphore, 0, 0);

    // Create the threads
    pthread_create(&thread1, NULL, task1, NULL);
    pthread_create(&thread2, NULL, task2, NULL);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    printf("Thread synchronization complete.\n");
    return 0;
}
