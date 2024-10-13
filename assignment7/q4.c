#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
#define SHM_SIZE 1024  // Shared memory size 
void writer_process() { 
key_t key; 
int shmid; 
char *shm_addr; 
// Generate unique key for shared memory 
key = ftok("shmfile", 65); 
// Create a shared memory segment 
shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); 
if (shmid == -1) { 
perror("shmget failed"); 
exit(1); 
} 
// Attach shared memory segment to this process 
shm_addr = (char *) shmat(shmid, NULL, 0); 
if (shm_addr == (char *) -1) { 
perror("shmat failed"); 
exit(1); 
} 

// Write data to shared memory 
printf("Writer: Enter a message: "); 
fgets(shm_addr, SHM_SIZE, stdin); 
// Detach shared memory 
shmdt(shm_addr); 
printf("Writer: Message written to shared memory.\n"); 
} 
void reader_process() { 
key_t key; 
int shmid; 
char *shm_addr; 
// Generate unique key for shared memory 
key = ftok("shmfile", 65); 
// Locate the shared memory segment 
shmid = shmget(key, SHM_SIZE, 0666); 
if (shmid == -1) { 
perror("shmget failed"); 
exit(1); 
} 
// Attach shared memory segment to this process 
shm_addr = (char *) shmat(shmid, NULL, 0); 
if (shm_addr == (char *) -1) { 
perror("shmat failed"); 
exit(1); 
} 
// Read data from shared memory 
printf("Reader: Message read from shared memory: %s\n", shm_addr); 

// Detach and remove shared memory 
shmdt(shm_addr); 
shmctl(shmid, IPC_RMID, NULL); 
printf("Reader: Shared memory segment removed.\n"); 
} 
int main() { 
int choice; 
printf("Enter 1 for writer, 2 for reader: "); 
scanf("%d", &choice); 
getchar();  // Consume newline character left by scanf 
if (choice == 1) { 
writer_process(); 
} else if (choice == 2) { 
reader_process(); 
} else { 
printf("Invalid choice.\n"); 
} 
return 0; 
} 