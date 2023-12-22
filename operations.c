#include <stdio.h>
#include <inttypes.h>
#include "LC3.h"
#include "operations.h"


void op_ADD_register(LC3 *lc3, reg_t DEST, reg_t SRC1, reg_t SRC2)
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

void op_ADD_imm(LC3 *lc3, reg_t DEST, reg_t SRC1, int16_t imm5)
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

void op_AND_register(LC3 *lc3, reg_t DEST, reg_t SRC1, reg_t SRC2)
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

void op_AND_imm(LC3 *lc3, reg_t DEST, reg_t SRC1, int16_t imm5)
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

void op_NOT(LC3 *lc3, reg_t DEST, reg_t SRC)
{
    lc3->register_file[DEST] = ~lc3->register_file[SRC];
    
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

void op_LD(LC3 *lc3, reg_t DEST, int16_t pcoffset9)
{
    uint16_t ADDR = (lc3->program_counter) + pcoffset9;
    lc3->register_file[DEST] = lc3->memory[ADDR];
}

void op_ST(LC3 *lc3, reg_t SRC, int16_t pcoffset9) 
{
    uint16_t ADDR = (lc3->program_counter) + pcoffset9;
    lc3->memory[ADDR] = lc3->register_file[SRC];
}

void op_LDI(LC3 *lc3, reg_t DEST, int16_t pcoffset9) 
{
    uint16_t ADDR_i = (lc3->program_counter) + pcoffset9;
    uint16_t ADDR_d = lc3->memory[ADDR_i];
    lc3->register_file[DEST] = lc3->memory[ADDR_d];
}

void op_STI(LC3 *lc3, reg_t SRC, int16_t pcoffset9) 
{
    uint16_t ADDR_i = (lc3->program_counter) + pcoffset9;
    uint16_t ADDR_d = lc3->memory[ADDR_i];
    lc3->memory[ADDR_d] = lc3->register_file[SRC];
}

void op_LDR(LC3 *lc3, reg_t DEST, reg_t BASE, int16_t offset6) 
{
    uint16_t ADDR = lc3->register_file[BASE] + offset6;
    lc3->register_file[DEST] = lc3->memory[ADDR];
}

void op_STR(LC3 *lc3, reg_t SRC, reg_t BASE, int16_t offset6) 
{
    uint16_t ADDR = lc3->register_file[BASE] + offset6;
    lc3->memory[ADDR] = lc3->register_file[SRC];
}

void op_LEA(LC3 *lc3, reg_t DEST, int16_t pcoffset9) 
{
    uint16_t ADDR = (lc3->program_counter) + pcoffset9;
    lc3->register_file[DEST] = ADDR;
}
