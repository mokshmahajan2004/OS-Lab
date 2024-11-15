#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void fifo(int pages[], int n, int frames);
void lru(int pages[], int n, int frames);
void optimal(int pages[], int n, int frames);

int main() {
    int choice, n, frames, pages[MAX_PAGES];

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    while (1) {
        printf("\nMenu:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, n, frames);
                break;
            case 2:
                lru(pages, n, frames);
                break;
            case 3:
                optimal(pages, n, frames);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Function to implement FIFO
void fifo(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], front = 0, page_faults = 0;
    bool found;

    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            page_faults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

// Function to implement LRU
void lru(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], recent[MAX_FRAMES], page_faults = 0;
    bool found;

    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = true;
                recent[j] = i;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < frames; j++) {
                if (frame[j] == -1 || recent[j] < recent[lru_index]) {
                    lru_index = j;
                }
            }
            frame[lru_index] = pages[i];
            recent[lru_index] = i;
            page_faults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

// Function to implement Optimal
void optimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], page_faults = 0;
    bool found;

    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            int replace_index = -1, farthest = i;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replace_index = j;
                    break;
                }

                int next_use = n;
                for (int k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        next_use = k;
                        break;
                    }
                }

                if (next_use > farthest) {
                    farthest = next_use;
                    replace_index = j;
                }
            }
            frame[replace_index] = pages[i];
            page_faults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}
