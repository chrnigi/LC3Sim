#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MEM_SIZE 65536

enum Operations {
    ADD =   0b0001000000000000,
    AND =   0b0101000000000000,
    BR =    0b0000000000000000,
    JMP =   0b1100000000000000,
    JSR =   0b0100000000000000,
    JSRR =  0b0100000000000000,
    LD =    0b0010000000000000,
    LDI =   0b1010000000000000,
    LDR =   0b0110000000000000,
    LEA =   0b1110000000000000,
    NOT =   0b1001000000000000,
    RET =   0b1100000000000000,
    RTI =   0b1000000000000000,
    ST =    0b0011000000000000,
    STI =   0b1011000000000000,
    STR =   0b0111000000000000,
    TRAP =  0b1111000000000000,

};

typedef struct LC3
{
    uint16_t register_file[8];
    uint16_t instruction_register;
    uint16_t memory[MEM_SIZE];
    uint16_t program_counter;
    uint8_t n;
    uint8_t z;
    uint8_t p;

} LC3;

// Cycle functions
void fetch(LC3* lc3);
uint16_t decode(LC3* lc3);
void evaluate_address(LC3* lc3, uint16_t opcode);

// Instruction functions
void ADD_register(LC3* lc3, char DEST, char SRC1, char SRC2);
void ADD_imm(LC3* lc3, char DEST, char SRC1, uint16_t imm5);

void AND_register(LC3* lc3, char DEST, char SRC1, char SRC2);
void AND_imm(LC3* lc3, char DEST, char SRC1, uint16_t imm5);

void not(LC3* lc3, char DEST, char SRC);

void ld(LC3* lc3, char DEST, int16_t pcoffset9);
void st(LC3* lc3, char SRC, int16_t pcoffset9);

void ldi(LC3* lc3, char DEST, int16_t pcoffset9);
void sti(LC3* lc3, char SRC, int16_t pcoffset9);

void ldr(LC3* lc3, char DEST, char BASE, char offset6);
void str(LC3* lc3, char SRC, char BASE, char offset6);

void lea(LC3* lc3, char DEST, int16_t pcoffset9);

int main(void)
{
    LC3 lc3;
    int halt = 0;
    lc3.program_counter = 0x3000;
    lc3.register_file[2] = 3;
    lc3.memory[lc3.program_counter+0] = 0b0001000010111111;         // ADD R0, R2, #-1
    lc3.memory[lc3.program_counter+1] = 0b0001001010101001;         // ADD R1, R2, #9
    lc3.memory[lc3.program_counter+2] = 0b0001011001000010;         // ADD R3, R1, R2
    lc3.memory[lc3.program_counter+3] = 0b0101011011000010;         // AND R3, R3, R2
    lc3.memory[lc3.program_counter+4] = 0b0101000000100000;         // AND R0, R0, #0
    int i = 0;
    while (!halt)
    {
        
        printf("\nProgram counter: x%x\n", lc3.program_counter);
        fetch(&lc3);
        evaluate_address(&lc3, decode(&lc3));
        
        for (int i = 0; i < 4; i++)
        {
            printf("Register %d: %d\n", i, lc3.register_file[i]);
        }
        if (i == 4)
        {
            halt = 1;
        }
        i++;
        
    }
    
}

void fetch(LC3* lc3)
{
    lc3->instruction_register = lc3->memory[lc3->program_counter++];
}

uint16_t decode(LC3* lc3)
{
    uint16_t opcode = lc3->instruction_register & 0b1111000000000000;
    return opcode;
}

void evaluate_address(LC3 *lc3, uint16_t opcode)
{
    uint8_t DEST;
    uint8_t SRC1;
    uint16_t SRC2;
    uint16_t IMM;
    switch (opcode)
    {
    case ADD:
        // Check for immediate mode.
        if (lc3->instruction_register & (1 << 5))
        {
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

            IMM = lc3->instruction_register & 0b0000000000011111;
            
            
            if (IMM & 1 << 4)
            {
                IMM |= 0b1111111111100000;
            }
            
            ADD_imm(lc3, DEST, SRC1, IMM);            
        } 
        // Else do register mode.
        else 
        {
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

            SRC2 = (lc3->instruction_register & 0b0000000000000111);

            ADD_register(lc3, DEST, SRC1, SRC2);

        }
        break;
    
    case AND:
        // Check for immediate mode.
        if (lc3->instruction_register & (1 << 5))
        {
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

            IMM = lc3->instruction_register & 0b0000000000011111;
            
            if (IMM & 1 << 4)
            {
                IMM ^= 0b1111111111100000;
            }

            AND_imm(lc3, DEST, SRC1, IMM);
        }
        // Else do register mode.
        else 
        {
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

            SRC2 = (lc3->instruction_register & 0b0000000000000111);
            
            AND_register(lc3, DEST, SRC1, SRC2);
        }
        

    default:
        break;
    }
}

void ADD_register(LC3 *lc3, char DEST, char SRC1, char SRC2)
{
    lc3->register_file[DEST] = lc3->register_file[SRC1] + lc3->register_file[SRC2];

    // Set condition codes.
    if (lc3->register_file[DEST] & 0b1000000000000000)
    {
        lc3->n = 1;
        lc3->z = 0;
        lc3->p = 0;
    } else if (lc3->register_file[DEST] == 0)
    {
        lc3->n = 0;
        lc3->z = 1;
        lc3->p = 0;
    } else {
        lc3->n = 0;
        lc3->z = 0;
        lc3->p = 1;
    }
}

void ADD_imm(LC3 *lc3, char DEST, char SRC1, uint16_t imm5)
{
    lc3->register_file[DEST] = lc3->register_file[SRC1] + imm5;
    
    // Set condition codes.
    if (lc3->register_file[DEST] & 0b1000000000000000)
    {   
        lc3->n = 1;
        lc3->z = 0;
        lc3->p = 0;
    } else if (lc3->register_file[DEST] == 0)
    {
        lc3->n = 0;
        lc3->z = 1;
        lc3->p = 0;
    } else {
        lc3->n = 0;
        lc3->z = 0;
        lc3->p = 1;
    }
    

}

void AND_register(LC3 *lc3, char DEST, char SRC1, char SRC2)
{
    lc3->register_file[DEST] = lc3->register_file[SRC1] & lc3->register_file[SRC2];

    // Set condition codes.
    if (lc3->register_file[DEST] & 0b1000000000000000)
    {
        lc3->n = 1;
        lc3->z = 0;
        lc3->p = 0;
    } else if (lc3->register_file[DEST] == 0)
    {
        lc3->n = 0;
        lc3->z = 1;
        lc3->p = 0;
    } else {
        lc3->n = 0;
        lc3->z = 0;
        lc3->p = 1;
    }
}

void AND_imm(LC3 *lc3, char DEST, char SRC1, uint16_t imm5)
{
    lc3->register_file[DEST] = lc3->register_file[SRC1] & imm5;

    // Set condition codes.
    if (lc3->register_file[DEST] & 0b1000000000000000)
    {
        lc3->n = 1;
        lc3->z = 0;
        lc3->p = 0;
    } else if (lc3->register_file[DEST] == 0)
    {
        lc3->n = 0;
        lc3->z = 1;
        lc3->p = 0;
    } else {
        lc3->n = 0;
        lc3->z = 0;
        lc3->p = 1;
    }
}
