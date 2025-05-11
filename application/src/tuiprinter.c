#include "tuiprinter.h"
#include <stdbool.h>
#include <stdio.h>

static uint8_t flags_set;
static uint8_t user_choice;
static bool quit = false;

enum userNext {
    NEXT = 'k',
    PREV = 'j',
    RUN = 'l',
    EXIT = 'q',
    INVALID = 0,
};


void startPrint(LC3 *lc3, uint8_t flags)
{
    // Check flags
    switch (UINT8_MAX & flags)
    {
    case 0b00000001:
        /* code */
        break;
    
    default:
        break;
    }


    while (!quit)
    {
        printFrame(lc3);
        
        while ((user_choice = getUserNext()) == INVALID)
        {
            // Clear bottom line
            printf("Not a valid option. Try again.\n");
        }

        switch (user_choice)
        {
        case EXIT:
            quit = true;
            break;
        case NEXT:
            // Advance program counter
            break;
        case PREV:
            // Restore prev state of lc3 with PC - 1
            break;
        case RUN:
            // Let the lc3 run till halt
            break;
        default:
            // Should not be possible to get here. Exit with error.
            exit(1);
            break;
        }

        
       
    }
    
    
}

void printFrame(LC3 *lc3)
{
}

uint8_t getUserNext()
{
    uint8_t in = getchar();

    switch (in)
    {
    case 'k':
    case 'j':
    case 'l':
    case 'q':
        break;
    
    default:
        in = INVALID;
        break;
    }
    
    return in;
}
