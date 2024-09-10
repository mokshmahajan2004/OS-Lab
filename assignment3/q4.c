#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "tempfile.txt";

    // Create and open a temporary file
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    close(fd);

    // Delete the file
    if (unlink(filename) < 0) {
        perror("unlink");
        return 1;
    }

    // Attempt to open the file again
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error: File '%s' still exists.\n", filename);
        close(fd);
    }

    return 0;
}
