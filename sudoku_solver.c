#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "sudoku.h" 

/* Sudoku* readSudoku(char* filename); */

int main(int argc, char** argv)
{
    int errCode = 0;

    printf("Sudoku Solver v1.0\n");

    if (argc == 2)
    {
        Sudoku* puzzle = readSudoku(argv[1]);
        
        if (puzzle != NULL)
        {
            printSudoku(puzzle);
            solveSudoku(puzzle);
            printf("\nSudoku solved:\n");
            printSudoku(puzzle);
            destroySudoku(puzzle); 
        }
    }
    else
    {
        printf("Incorrect number of arguments. Correct usage: %s <source file>.\n", argv[0]);
        errCode = 1;
    } 

    return errCode;
}