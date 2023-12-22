#include "LC3.h"

#ifndef OPERATIONS_H
#define OPERATIONS_H

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

// Instruction functions
void op_ADD_register(LC3* lc3, reg_t DEST, reg_t SRC1, reg_t SRC2);
void op_ADD_imm(LC3* lc3, reg_t DEST, reg_t SRC1, int16_t imm5);

void op_AND_register(LC3* lc3, reg_t DEST, reg_t SRC1, reg_t SRC2);
void op_AND_imm(LC3* lc3, reg_t DEST, reg_t SRC1, int16_t imm5);

void op_NOT(LC3* lc3, reg_t DEST, reg_t SRC);

void op_LD(LC3* lc3, reg_t DEST, int16_t pcoffset9);
void op_ST(LC3* lc3, reg_t SRC, int16_t pcoffset9);

void op_LDI(LC3* lc3, reg_t DEST, int16_t pcoffset9);
void op_STI(LC3* lc3, reg_t SRC, int16_t pcoffset9);

void op_LDR(LC3* lc3, reg_t DEST, reg_t BASE, int16_t offset6);
void op_STR(LC3* lc3, reg_t SRC, reg_t BASE, int16_t offset6);

void op_LEA(LC3* lc3, reg_t DEST, int16_t pcoffset9);

#endif
