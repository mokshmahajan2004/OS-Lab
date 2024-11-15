#include <stdio.h>
#include <stdbool.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

typedef struct {
    int size;
    bool occupied;
    int process_id;
} Partition;

typedef struct {
    int id;
    int size;
    int partition_index;
} Process;

Partition partitions[MAX_PARTITIONS];
int partition_count = 0;
Process processes[MAX_PROCESSES];
int process_count = 0;

void add_partition(int size) {
    if (partition_count < MAX_PARTITIONS) {
        partitions[partition_count].size = size;
        partitions[partition_count].occupied = false;
        partitions[partition_count].process_id = -1;
        partition_count++;
        printf("Partition of size %d added.\n", size);
    } else {
        printf("Maximum partitions reached.\n");
    }
}

int allocate_process(int method, int process_id, int process_size) {
    int selected_index = -1;

    for (int i = 0; i < partition_count; i++) {
        if (!partitions[i].occupied && partitions[i].size >= process_size) {
            if (selected_index == -1) {
                selected_index = i;
            } else {
                if (method == 1 && partitions[i].size < partitions[selected_index].size) { // Best Fit
                    selected_index = i;
                }
                if (method == 2 && partitions[i].size > partitions[selected_index].size) { // Worst Fit
                    selected_index = i;
                }
            }
            if (method == 0) { // First Fit
                selected_index = i;
                break;
            }
        }
    }

    if (selected_index == -1) {
        printf("No suitable partition found for Process %d.\n", process_id);
        return -1;
    }

    partitions[selected_index].occupied = true;
    partitions[selected_index].process_id = process_id;

    processes[process_count].id = process_id;
    processes[process_count].size = process_size;
    processes[process_count].partition_index = selected_index;
    process_count++;

    printf("Process %d allocated to Partition %d.\n", process_id, selected_index + 1);
    return selected_index;
}

void deallocate_process(int process_id) {
    for (int i = 0; i < process_count; i++) {
        if (processes[i].id == process_id) {
            int partition_index = processes[i].partition_index;
            partitions[partition_index].occupied = false;
            partitions[partition_index].process_id = -1;

            // Shift processes array
            for (int j = i; j < process_count - 1; j++) {
                processes[j] = processes[j + 1];
            }
            process_count--;

            printf("Process %d deallocated from Partition %d.\n", process_id, partition_index + 1);
            return;
        }
    }
    printf("Process %d not found.\n", process_id);
}

void display_partitions() {
    printf("\nCurrent Partition States:\n");
    for (int i = 0; i < partition_count; i++) {
        printf("Partition %d: Size=%d | Status=%s | Process=%d\n", 
               i + 1, 
               partitions[i].size, 
               partitions[i].occupied ? "Occupied" : "Free", 
               partitions[i].occupied ? partitions[i].process_id : -1);
    }
}

void menu() {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Partition\n");
        printf("2. Allocate Process (First Fit)\n");
        printf("3. Allocate Process (Best Fit)\n");
        printf("4. Allocate Process (Worst Fit)\n");
        printf("5. Deallocate Process\n");
        printf("6. Display Partitions\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int size;
            printf("Enter partition size: ");
            scanf("%d", &size);
            add_partition(size);
        } else if (choice >= 2 && choice <= 4) {
            int process_id, process_size;
            printf("Enter process ID: ");
            scanf("%d", &process_id);
            printf("Enter process size: ");
            scanf("%d", &process_size);
            int method = choice - 2;
            allocate_process(method, process_id, process_size);
        } else if (choice == 5) {
            int process_id;
            printf("Enter process ID to deallocate: ");
            scanf("%d", &process_id);
            deallocate_process(process_id);
        } else if (choice == 6) {
            display_partitions();
        } else if (choice == 7) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
