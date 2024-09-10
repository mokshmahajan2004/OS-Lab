#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void list_directory(const char *path, int depth) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%*s%s\n", depth * 4, "", entry->d_name);

        if (entry->d_type == DT_DIR) {
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            list_directory(new_path, depth + 1);
        }
    }

    closedir(dir);
}

int main() {
    printf("Listing files and directories from the current directory:\n");
    list_directory(".", 0);
    return 0;
}
