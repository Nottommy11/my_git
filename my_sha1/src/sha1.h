#ifndef SHA1_H
#define SHA1_H

#include <stdint.h>

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
    shaSuccess = 0,
    shaNull,            // Null pointer parameter
    shaInputTooLong,    // Input data too long
    shaStateError       // Called Input after Result
};
#endif
#define SHA1HashSize 20

typedef struct SHA1_Context{
    uint32_t Intermediate_Hash[SHA1HashSize/4]; // Message Digest

    uint32_t Length_Low;                        // Message length in bits
    uint32_t Length_High;                       // Message length in bits


    int_least16_t Message_Block_Index;          // Index into message block array
    uint8_t Message_Block[64];                  // 512-bit message blocks

    int Computed;                               // Is the digest computed?
    int Corrupted;                              // Is the message digest corrupted?
} SHA1_Context;

int SHA1_Reset(SHA1_Context *context);
int SHA1_Input(SHA1_Context *context, const uint8_t *message_array, unsigned length);
int SHA1_Result( SHA1_Context *context, uint8_t Message_Digest[SHA1HashSize]);

#endif
