#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "sha1.h"
#include "file_io.h"

// Reference: https://www.rfc-editor.org/rfc/rfc3174#page-6

// argv[0] is program name
// argv[1] is the first argument (filename)
int main(int argc, char *argv[]) {
    if(argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    }

    const char *filename = argv[1];

    size_t file_len;
    uint8_t *data = read_file(filename, &file_len);

    if(!data){
        return 1;
    }

    SHA1_Context context;
    uint8_t message_digest[20];
    int err;

    err = SHA1_Reset(&context);
    if(err){
        fprintf(stderr, "SHA1 Reset Error: %d\n", err);
        free(data);
        return 1;
    }

    err = SHA1_Input(&context, data, (unsigned)file_len);
    if(err){
        fprintf(stderr, "SHA1 Input Error: %d\n", err);
        free(data);
        return 1;
    }

    err = SHA1_Result(&context, message_digest);
    if(err){
        fprintf(stderr, "SHA1 Result Error: %d\n", err);
        free(data);
        return 1;
    }

    for(int i = 0; i < 20; i++){
        printf("%02x", message_digest[i]);
    }

    printf(" %s\n", filename);

    free(data);
    return 0;
}
