#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdint.h>
#include <stddef.h>

/**
 * Reads an entire file into a heap-allocated buffer.
 * * @param path The path to the file to read.
 * @param out_len A pointer to a variable where the file size will be stored.
 * @return A pointer to the buffer (caller must free), or NULL on error.
 */
uint8_t* read_file(const char* path, size_t* out_len);

/**
 * Writes a buffer to a file (overwriting if it exists).
 * * @param path The path to write to.
 * @param data The buffer to write.
 * @param len The number of bytes to write.
 * @return 0 on success, non-zero on error.
 */
int write_file(const char* path, const uint8_t* data, size_t len);

#endif
