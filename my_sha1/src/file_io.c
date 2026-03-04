#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

uint8_t* read_file(const char* path, size_t* out_len) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);   // Move to the end of the file
    long length = ftell(file);  // Get the byte offset from beginning
    fseek(file, 0, SEEK_SET);   // Reset back to the beginning

    if (length < 0) {
        fclose(file);
        return NULL;
    }

    uint8_t *buffer = malloc(length + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    size_t read_count = fread(buffer, 1, length, file);
    if (read_count != (size_t)length) {
        fprintf(stderr, "Error reading file: expected %ld bytes, got %zu\n", length, read_count);
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file);

    if (out_len) {
        *out_len = (size_t)length;
    }

    return buffer;
}

int write_file(const char* path, const uint8_t* data, size_t len) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    size_t written = fwrite(data, 1, len, file);
    fclose(file);

    if (written != len) {
        fprintf(stderr, "Write error: expected %zu, wrote %zu\n", len, written);
        return 1;
    }

    return 0;
}
