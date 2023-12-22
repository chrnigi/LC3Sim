#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "LC3.h"
#include "operations.h"

// Cycle functions
void fetch(LC3* lc3);
uint16_t decode(LC3* lc3);
void evaluate_address(LC3* lc3, uint16_t opcode);

static int halt = 0;

int main(void)
{
    LC3 lc3;
    
    lc3.program_counter = 0x3000;
    lc3.register_file[2] = 3;
    lc3.memory[lc3.program_counter+0] = 0b0001000010111111;         // ADD R0, R2, #-1
    lc3.memory[lc3.program_counter+1] = 0b0001001010101001;         // ADD R1, R2, #9
    lc3.memory[lc3.program_counter+2] = 0b0001011001000010;         // ADD R3, R1, R2
    lc3.memory[lc3.program_counter+3] = 0b0101011011000010;         // AND R3, R3, R2
    lc3.memory[lc3.program_counter+4] = 0b0101000000100000;         // AND R0, R0, #0
    lc3.memory[lc3.program_counter+5] = 0b1001001001111111;         // NOT R1, R1
    lc3.memory[lc3.program_counter+6] = 0b0001001001100001;         // ADD R1, R1, #1
    lc3.memory[lc3.program_counter+7] = 0b0010011111111110;         // LD R3, #-2
    lc3.memory[lc3.program_counter+8] = 0b1111111111111111;         // .FILL #-1
    int i = 0;
    while (!halt)
    {
        
        printf("\nProgram counter: x%x:\n", lc3.program_counter);
        fetch(&lc3);
        evaluate_address(&lc3, decode(&lc3));
        
        for (int j = 0; j < 4; j++)
        {
            printf("Register %d: %hi\n", j, lc3.register_file[j]);
        }
        if (i == 7)
        {
            halt = 1;
        }
        i++;
        
    }

    return 0;   
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
    reg_t DEST;
    reg_t SRC1;
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
            
            // Sign extension
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
            // Destination register in bits 11 to 9.
            DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;
            // Source register in bits 8 to 6.
            SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;
            // IMM value in bits 4 to 0.
            IMM = lc3->instruction_register & 0b0000000000011111;
            
            if (IMM & 1 << 4)
            {
                IMM |= 0b1111111111100000;
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
        break;

    case NOT:
        DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

        SRC1 = (lc3->instruction_register & 0b0000000111000000) >> 6;

        op_NOT(lc3, DEST, SRC1);
        break;

    case LD:
        DEST = (lc3->instruction_register & 0b0000111000000000) >> 9;

        IMM = lc3->instruction_register & 0b0000000111111111;

        // Sign extension.
        if (IMM & (1 << 8))
        {
            IMM |= 0b1111111000000000;
        }

        op_LD(lc3, DEST, IMM);
        break;
        

    default:
        break;
    }
}

