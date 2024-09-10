#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Get source and destination file paths
    const char *source = argv[1];
    const char *destination = argv[2];

    // Use the rename() function to move/rename the file
    if (rename(source, destination) != 0) {
        perror("Error renaming/moving file");
        return EXIT_FAILURE;
    }

    printf("File moved/renamed successfully.\n");
    return EXIT_SUCCESS;
}

