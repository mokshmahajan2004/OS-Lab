#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024
void xor_encrypt_decrypt(const char *input_file, const char *output_file, char key) {
    int fd_in, fd_out;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];
    // Open input file for reading
    fd_in = open(input_file, O_RDONLY);
    if (fd_in < 0) {
        perror("open input file");
        exit(EXIT_FAILURE);
    }
    // Open output file for writing
    fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        perror("open output file");
        close(fd_in);
        exit(EXIT_FAILURE);
    }
    // Process the file
    while ((bytes_read = read(fd_in, buffer, BUFFER_SIZE)) > 0) {
        // XOR each byte with the key
        for (ssize_t i = 0; i < bytes_read; ++i) {
            buffer[i] ^= key;
        }
        // Write the processed data to the output file
        bytes_written = write(fd_out, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(fd_in);
            close(fd_out);
            exit(EXIT_FAILURE);
        }
    }
    if (bytes_read < 0) {
        perror("read");
    }

    close(fd_in);
    close(fd_out);
}
int main(int argc, char *argv[]) {
    if (argc != 5) {
        write(STDERR_FILENO, "Usage: ./q5 <encrypt/decrypt> <input_file> <output_file> <key>\n", 64);
        return EXIT_FAILURE;
    }
    char *operation = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];
    char key = (char)atoi(argv[4]);  // Convert key from string to integer and then to char
    if (strcmp(operation, "encrypt") == 0 || strcmp(operation, "decrypt") == 0) {
        xor_encrypt_decrypt(input_file, output_file, key);
        write(STDOUT_FILENO, (strcmp(operation, "encrypt") == 0) ? "File encrypted successfully.\n" : "File decrypted successfully.\n", 35);
    } else {
        write(STDERR_FILENO, "Invalid operation. Use 'encrypt' or 'decrypt'.\n", 47);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
