#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <original_file> <hard_link>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Create a hard link
    if (link(argv[1], argv[2]) == -1) {
        perror("link");
        return EXIT_FAILURE;
    }

    // Check inode numbers of original file and hard link
    struct stat orig_stat, link_stat;
    if (stat(argv[1], &orig_stat) == -1 || stat(argv[2], &link_stat) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    // Verify and print result
    if (orig_stat.st_ino == link_stat.st_ino) {
        printf("Hard link created successfully!\n");
        printf("Inode of original file: %lu\n", (unsigned long)orig_stat.st_ino);
        printf("Inode of hard link: %lu\n", (unsigned long)link_stat.st_ino);
    } else {
        fprintf(stderr, "Error: Inode numbers do not match.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
