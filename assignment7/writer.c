// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "my_fifo"

int main() {
    int fd;
    const char *message = "Hello from FIFO writer!";

    // Open FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the message to the FIFO
    write(fd, message, strlen(message) + 1); // +1 for null terminator

    printf("Message written: %s\n", message);

    // Close the FIFO
    close(fd);
    return 0;
}
