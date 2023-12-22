#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "LC3.h"
#include "operations.h"

// Cycle functions
void fetch(LC3* lc3);
uint16_t decode(LC3* lc3);
void evaluate_address(LC3* lc3, uint16_t opcode);

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
        
        printf("\nProgram counter: x%x:\n", lc3.program_counter);
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
            
            op_ADD_imm(lc3, DEST, SRC1, IMM);            
        } 
        // Else do register mode.
        else 
        {
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

            SRC2 = (lc3->instruction_register & 0b0000000000000111);

            op_ADD_register(lc3, DEST, SRC1, SRC2);

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

            op_AND_imm(lc3, DEST, SRC1, IMM);
        }
        // Else do register mode.
        else 
        {
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

            SRC2 = (lc3->instruction_register & 0b0000000000000111);
            
            op_AND_register(lc3, DEST, SRC1, SRC2);
        }
        

    default:
        break;
    }
}

