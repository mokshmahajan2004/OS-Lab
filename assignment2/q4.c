#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./count_words <filename>\n", 32);
        return EXIT_FAILURE;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int word_count = 0;
    int in_word = 0;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; ++i) {
            if (isspace(buffer[i])) {
                if (in_word) {
                    in_word = 0;
                    ++word_count;
                }
            } else {
                in_word = 1;
            }
        }
    }
    if (in_word) ++word_count;  // Count the last word if necessary
    if (bytes_read < 0) {
        perror("read");
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);
    // Print the word count
    char result[50];
    int len = snprintf(result, sizeof(result), "Word count: %d\n", word_count);
    write(STDOUT_FILENO, result, len);
    return EXIT_SUCCESS;
}
