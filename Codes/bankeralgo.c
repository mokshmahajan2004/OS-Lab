#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int n, m;
int allocation[10][10], max[10][10], need[10][10], available[10];

// Function to read from file
void readMatrix(int fd, int matrix[10][10], int rows, int cols) {
    char buffer[256];
    int index = 0;
    char ch;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            index = 0;
            while (read(fd, &ch, 1) > 0 && ch != ' ' && ch != '\n') {
                buffer[index++] = ch;
            }
            buffer[index] = '\0';  // Null-terminate the string
            matrix[i][j] = atoi(buffer);  // Convert string to integer
        }
    }
}

// Function to read array from file
void readArray(int fd, int array[10], int size) {
    char buffer[256];
    int index = 0;
    char ch;

    for (int i = 0; i < size; i++) {
        index = 0;
        while (read(fd, &ch, 1) > 0 && ch != ' ' && ch != '\n') {
            buffer[index++] = ch;
        }
        buffer[index] = '\0';  // Null-terminate the string
        array[i] = atoi(buffer);  // Convert string to integer
    }
}

bool isSafe(int fd) {
    int work[m], finish[n];
    int safeSequence[n];
    int count = 0;

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            write(fd, "System is not in a safe state.\n", 31);
            return false;
        }
    }

    write(fd, "System is in a safe state.\nSafe sequence is: ", 46);
    for (int i = 0; i < n; i++) {
        char buf[10];
        int len = snprintf(buf, sizeof(buf), "%d ", safeSequence[i]);
        write(fd, buf, len);
    }
    write(fd, "\n", 1);
    return true;
}

void requestResource(int fd, int process) {
    int request[m];
    char buf[256];
    
    if (process >= n || process < 0) {
        write(fd, "Invalid process number.\n", 24);
        return;
    }

    write(fd, "Enter request for process ", 26);
    int len = snprintf(buf, sizeof(buf), "%d (maximum of %d resources):\n", process, m);
    write(fd, buf, len);

    // Read request values from input
    for (int i = 0; i < m; i++) {
        // Normally this would read input dynamically from the file
        // Simulate reading request from user input (just enter some request values manually)
        request[i] = 1; // Hardcoding for testing purposes, replace with real input mechanism.

        if (request[i] > need[process][i]) {
            write(fd, "Error: Process has exceeded maximum claim.\n", 43);
            return;
        }
        if (request[i] > available[i]) {
            write(fd, "Resources are not available. Process must wait.\n", 49);
            return;
        }
    }

    // Temporarily allocate resources
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the state is still safe after allocation
    if (isSafe(fd)) {
        write(fd, "Resources allocated successfully to process.\n", 45);
    } else {
        write(fd, "System is not safe after allocating. Rolling back.\n", 52);
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main() {
    int fd_in, fd_out;

    // Open input and output files
    fd_in = open("input.txt", O_RDONLY);
    fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd_in < 0 || fd_out < 0) {
        write(fd_out, "Error opening files\n", 20);
        return 1;
    }

    // Read number of processes and resource types
    char buffer[256];
    read(fd_in, buffer, sizeof(buffer));
    n = atoi(buffer);  // Read number of processes
    read(fd_in, buffer, sizeof(buffer));
    m = atoi(buffer);  // Read number of resource types

    // Read the allocation matrix
    write(fd_out, "Reading allocation matrix...\n", 29);
    readMatrix(fd_in, allocation, n, m);

    // Read the max matrix
    write(fd_out, "Reading max matrix...\n", 23);
    readMatrix(fd_in, max, n, m);

    // Read available resources
    write(fd_out, "Reading available resources...\n", 31);
    readArray(fd_in, available, m);

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check if the system is in a safe state
    if (isSafe(fd_out)) {
        write(fd_out, "Enter process number to request resources: ", 44);
        read(fd_in, buffer, sizeof(buffer));
        int process = atoi(buffer);
        requestResource(fd_out, process);
    }

    // Close the files
    close(fd_in);
    close(fd_out);

    return 0;
}
