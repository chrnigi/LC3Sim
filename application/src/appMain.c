#include <LC3.h>
#include <operations.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
            printf("Register %d: %-5hi\tRegister %d: %-5hi\n", j, lc3.register_file[j], j+4, lc3.register_file[j+4]);
        }
        if (i == 7)
        {
            halt = 1;
        }
        i++;
        
    }

    return 0;   
}