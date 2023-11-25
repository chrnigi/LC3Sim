
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