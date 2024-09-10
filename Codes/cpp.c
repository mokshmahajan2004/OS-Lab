#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 4096

void copy_file(const char *source, const char *destination) {
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open the source file
    src_fd = open(source, O_RDONLY);
    if (src_fd < 0) {
        perror("open source file");
        exit(EXIT_FAILURE);
    }

    // Open or create the destination file
    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("open destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Copy the file
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            perror("write to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read < 0) {
        perror("read from source file");
    }

    // Close the file descriptors
    close(src_fd);
    close(dest_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    copy_file(argv[1], argv[2]);

    return EXIT_SUCCESS;
}

