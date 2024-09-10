#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *dir_name = "test_dir";
    char cwd[1024];

    if (mkdir(dir_name, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    if (chdir(dir_name) == -1) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    const char *last_part = strrchr(cwd, '/');
    if (last_part != NULL && strcmp(last_part + 1, dir_name) == 0) {
        printf("Successfully changed to directory: %s\n", cwd);
    } else {
        printf("Failed to change directory. Current directory is: %s\n", cwd);
    }

    return 0;
}
