#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main() {
    const char *filename = "user_file.txt";
    char user_input[BUFFER_SIZE];
    int fd;
    ssize_t bytes_written, bytes_read;
    char buffer[BUFFER_SIZE];
    // Prompt the user for input
    write(STDOUT_FILENO, "Enter a string to write to the file: ", 37);
    ssize_t len = read(STDIN_FILENO, user_input, sizeof(user_input) - 1);
    if (len < 0) {
        perror("read");
        return EXIT_FAILURE;
    }
    // Remove newline character if present
    user_input[len - 1] = '\0';
    // Open file for writing
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    // Write the user input to the file
    bytes_written = write(fd, user_input, len - 1);
    if (bytes_written < 0) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);
    // Open file for reading
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    // Read and display the file contents
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    if (bytes_read < 0) {
        perror("read");
    }
    close(fd);
    return EXIT_SUCCESS;
}
