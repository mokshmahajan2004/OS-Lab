#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *filename = "file_test.txt";
    const char *data1 = "Hello, this is the original descriptor.\n";
    const char *data2 = "And this is from the duplicated descriptor.\n";
    char buffer[256];
    int fd, fd_dup;

    // Open the file
    if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1 ||
        (fd_dup = dup(fd)) == -1) {
        perror("Error opening or duplicating file descriptor");
        exit(EXIT_FAILURE);
    }

    // Write to both file descriptors
    if (write(fd, data1, strlen(data1)) == -1 || write(fd_dup, data2, strlen(data2)) == -1) {
        perror("Error writing to file");
        close(fd);
        close(fd_dup);
        exit(EXIT_FAILURE);
    }

    // Close file descriptors
    close(fd);
    close(fd_dup);

    // Reopen file and read contents
    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror("Error reopening file");
        exit(EXIT_FAILURE);
    }

    printf("File contents:\n");
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
    }

    close(fd);
    return 0;
}
