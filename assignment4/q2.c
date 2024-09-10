#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

// Function to list contents of a directory
void list_directory() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);
}

int main() {
    const char *dir_name = "delete_me";

    // Create the directory
    if (mkdir(dir_name, 0755) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    // List contents before removal
    printf("Before removal:\n");
    list_directory();

    // Remove the directory
    if (rmdir(dir_name) == -1) {
        perror("rmdir");
        exit(EXIT_FAILURE);
    }

    // List contents after removal
    printf("\nAfter removal:\n");
    list_directory();

    return 0;
}
