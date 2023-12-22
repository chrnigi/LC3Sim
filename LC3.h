#ifndef MEM_SIZE
#define MEM_SIZE 65536
#endif

#include <stdint.h>

#ifndef LC3_H
#define LC3_H
struct LC3
{
    uint16_t register_file[8];
    uint16_t instruction_register;
    uint16_t memory[MEM_SIZE];
    uint16_t program_counter;
    uint8_t n;
    uint8_t z;
    uint8_t p;

};

typedef struct LC3 LC3;

// Register indexing type.
typedef uint8_t reg_t;

#endif
