#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <LC3.h>
#include <operations.h>

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

