#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

typedef struct {
    int size;              // Size of the partition
    int isFree;            // 1 if free, 0 if allocated
    void *start;           // Start address of the partition
} Partition;

typedef struct {
    int size;              // Size of the process
    int allocatedPartition; // Index of the allocated partition
} Process;

void displayPartitions(Partition partitions[], int numPartitions) {
    printf("\nPartitions:\n");
    for (int i = 0; i < numPartitions; i++) {
        printf("Partition %d: Size = %d, Status = %s, Start Address = %p\n", 
                i + 1, 
                partitions[i].size, 
                partitions[i].isFree ? "Free" : "Allocated",
                partitions[i].start);
    }
}

void displayProcesses(Process processes[], int numProcesses) {
    printf("\nProcesses:\n");
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].allocatedPartition != -1) {
            printf("Process %d: Size = %d, Allocated to Partition %d\n", 
                    i + 1, 
                    processes[i].size, 
                    processes[i].allocatedPartition + 1);
        } else {
            printf("Process %d: Size = %d, Not Allocated\n", 
                    i + 1, 
                    processes[i].size);
        }
    }
}

void firstFitAllocation(Partition partitions[], int numPartitions, Process processes[], int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].allocatedPartition == -1) { // Only allocate if not already allocated
            for (int j = 0; j < numPartitions; j++) {
                if (partitions[j].isFree && partitions[j].size >= processes[i].size) {
                    partitions[j].isFree = 0; // Mark partition as allocated
                    processes[i].allocatedPartition = j; // Allocate partition to process
                    printf("Allocated Process %d to Partition %d\n", i + 1, j + 1);

                    // Check if there's remaining space in the partition
                    int remainingSize = partitions[j].size - processes[i].size;
                    if (remainingSize > 0) {
                        printf("Remaining space in Partition %d: %d\n", j + 1, remainingSize);
                    }
                    break;
                }
            }
        }
    }
}

void freeMemory(Partition partitions[], Process processes[], int processIndex) {
    int partitionIndex = processes[processIndex].allocatedPartition;
    if (partitionIndex != -1) {
        partitions[partitionIndex].isFree = 1; // Mark partition as free
        processes[processIndex].allocatedPartition = -1; // Mark process as not allocated
        printf("Freed Process %d from Partition %d\n", processIndex + 1, partitionIndex + 1);
    } else {
        printf("Process %d is not allocated to any partition.\n", processIndex + 1);
    }
}

int main() {
    Partition partitions[MAX_PARTITIONS];
    Process processes[MAX_PROCESSES];
    int numPartitions, numProcesses = 0;
    int choice;

    // Input number of partitions
    printf("Enter the number of partitions (max %d): ", MAX_PARTITIONS);
    scanf("%d", &numPartitions);
    
    for (int i = 0; i < numPartitions; i++) {
        printf("Enter size of Partition %d: ", i + 1);
        scanf("%d", &partitions[i].size);
        partitions[i].isFree = 1; // Initially, all partitions are free
        partitions[i].start = sbrk(partitions[i].size); // Allocate memory using sbrk
        if (partitions[i].start == (void *) -1) {
            perror("Failed to allocate memory using sbrk");
            return 1; // Exit if memory allocation fails
        }
    }

    do {
        printf("\nMenu:\n");
        printf("1. Display Partitions\n");
        printf("2. Enter Processes for Allocation\n");
        printf("3. Allocate Memory using First Fit\n");
        printf("4. Free Memory for a Process\n");
        printf("5. Display Processes\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayPartitions(partitions, numPartitions);
                break;

            case 2:
                printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
                scanf("%d", &numProcesses);
                for (int i = 0; i < numProcesses; i++) {
                    printf("Enter size of Process %d: ", i + 1);
                    scanf("%d", &processes[i].size);
                    processes[i].allocatedPartition = -1; // Initialize allocation status
                }
                break;

            case 3:
                firstFitAllocation(partitions, numPartitions, processes, numProcesses);
                break;

            case 4:
                {
                    int processIndex;
                    printf("Enter the process number to free (1-%d): ", numProcesses);
                    scanf("%d", &processIndex);
                    if (processIndex > 0 && processIndex <= numProcesses) {
                        freeMemory(partitions, processes, processIndex - 1);
                    } else {
                        printf("Invalid process number.\n");
                    }
                }
                break;

            case 5:
                displayProcesses(processes, numProcesses);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    // Deallocate memory for partitions (if needed)
    for (int i = 0; i < numPartitions; i++) {
        if (partitions[i].isFree == 0) {
            sbrk(-partitions[i].size); // This is a simplification; in practice, sbrk cannot free individual partitions.
        }
    }

    return 0;
}
