#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the file for writing (create if it doesn't exist, truncate if it does)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Redirect stdout to the file descriptor
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return 1;
    }

    // Close the original file descriptor
    close(fd);

    // Print a message (will be written to the file)
    printf("This message will be written to the file 'output.txt'.\n");

    return 0;
}
