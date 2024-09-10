#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("open source file");
        return EXIT_FAILURE;
    }

    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("open destination file");
        close(src_fd);
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("write");
            close(src_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }
    }

    if (bytes_read < 0) {
        perror("read");
    }

    close(src_fd);
    close(dest_fd);

    if (bytes_read < 0) {
        return EXIT_FAILURE;
    }

    printf("File '%s' copied to '%s'.\n", argv[1], argv[2]);
    return EXIT_SUCCESS;
}
