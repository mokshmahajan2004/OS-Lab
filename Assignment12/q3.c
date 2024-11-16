#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
void* philosopher(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 3; i++) {  // Each philosopher eats 3 times
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Simulate thinking
        // Pick up the chopsticks
        printf("Philosopher %d is hungry.\n", id);
        pthread_mutex_lock(&chopsticks[id]);                 // Pick up left chopstick
        pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]); // Pick up right chopstick
        // Eat
        printf("Philosopher %d is eating.\n", id);
        sleep(2); // Simulate eating
        // Put down the chopsticks
        pthread_mutex_unlock(&chopsticks[id]);                 // Put down left chopstick
        pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]); // Put down right chopstick
        printf("Philosopher %d finished eating.\n", id);
    }
    return NULL;
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    // Initialize the chopsticks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    // Wait for all threads to complete
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    // Destroy the mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    printf("Dining Philosophers simulation complete.\n");
    return 0;
}
