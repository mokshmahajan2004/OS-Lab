#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main() {
    int fd;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];
    // Open the file using the open system call
    fd = open("q1.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    // Read the contents of the file using the read system call
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Write the contents to the console using the write system call
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to stdout");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    if (bytesRead == -1) {
        perror("Error reading the file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Close the file using the close system call
    close(fd);
    return 0;
}

