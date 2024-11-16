#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0;               // Producer index
int out = 0;              // Consumer index

sem_t empty;  // Semaphore to track empty slots in the buffer
sem_t full;   // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex;  // Mutex for critical section

// Function for the producer
void* producer(void* arg) {
    for (int i = 1; i <= 10; i++) {  // Produce 10 items
        sem_wait(&empty);           // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Lock the critical section

        // Add item to the buffer
        buffer[in] = i;
        printf("Producer produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&full);              // Signal that a slot is filled

        sleep(1); // Simulate production time
    }
    return NULL;
}

// Function for the consumer
void* consumer(void* arg) {
    for (int i = 1; i <= 10; i++) {  // Consume 10 items
        sem_wait(&full);            // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock the critical section
        // Remove item from the buffer
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&empty);             // Signal that a slot is empty

        sleep(2); // Simulate consumption time
    }
    return NULL;
}
int main() {
    pthread_t producer_thread, consumer_thread;
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Buffer starts empty
    sem_init(&full, 0, 0);            // No items initially
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Producer-Consumer simulation complete.\n");
    return 0;
}
