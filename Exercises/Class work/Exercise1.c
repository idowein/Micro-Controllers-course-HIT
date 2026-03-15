#include <stdio.h>

// Task 1
unsigned int inverBitsUsingXor(unsigned int value){
    unsigned int mask = 0xFFFFFFFF; // mask definition
    // Note: unsigned - MSB is not a sign bit. always positive value
    // int - 32 bits, 4 bytes, 2 words.
    // 0x - Exa
    // 8 * F = 32 * 1 = 1111 ... 11 (32 times)
    return value ^ mask; // ^ = XOR operation
}

// Task 1 - second way (using not gate)
// Note - not to check!! only for myself
unsigned int inverBitsUsingNot(unsigned int value){
    return ~value; // ~ filps each bit
}

