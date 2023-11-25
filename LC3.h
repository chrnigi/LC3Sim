#define MEM_SIZE 65536

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