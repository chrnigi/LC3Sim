#include <stdio.h>
#include <inttypes.h>
#include "LC3.h"
#include "operations.h"


void op_ADD_register(LC3 *lc3, char DEST, char SRC1, char SRC2)
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

void op_ADD_imm(LC3 *lc3, char DEST, char SRC1, uint16_t imm5)
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

void op_AND_register(LC3 *lc3, char DEST, char SRC1, char SRC2)
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

void op_AND_imm(LC3 *lc3, char DEST, char SRC1, uint16_t imm5)
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
