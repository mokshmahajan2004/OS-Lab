#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h> 
#define MAX 100 
// Structure for the message queue 
struct message { 
long msg_type; 
char msg_text[MAX]; 
}; 
// Producer process (sends message to the queue) 
void producer() { 
key_t key; 
int msgid; 
// Generate unique key 
key = ftok("progfile", 65); 
// Create a message queue and return the identifier 
msgid = msgget(key, 0666 | IPC_CREAT); 
// Message to be sent 
struct message msg; 
msg.msg_type = 1; 
printf("Enter the message to send: "); 
fgets(msg.msg_text, MAX, stdin); 
// Send message to the queue 
msgsnd(msgid, &msg, sizeof(msg), 0); 
printf("Producer: Message sent: %s\n", msg.msg_text); 
} 
// Consumer process (reads message from the queue) 
void consumer() { 
key_t key; 
int msgid; 
struct message msg; 
// Generate the same unique key 

key = ftok("progfile", 65); 
// Get the message queue identifier 
msgid = msgget(key, 0666 | IPC_CREAT); 
// Receive the message from the queue 
msgrcv(msgid, &msg, sizeof(msg), 1, 0); 
// Display the message received 
printf("Consumer: Message received: %s\n", msg.msg_text); 
// Clean up: remove the message queue 
msgctl(msgid, IPC_RMID, NULL); 
} 
int main() { 
int choice; 
printf("Enter 1 for producer, 2 for consumer: "); 
scanf("%d", &choice); 
getchar(); // Consume newline character left by scanf 
if (choice == 1) { 
producer(); 
} else if (choice == 2) { 
consumer(); 
} else { 
printf("Invalid choice.\n"); 
} 
return 0; 
} 