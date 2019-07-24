#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "sudoku.h"
#include "sudoku_solver.h"

int main(int argc, char** argv)
{
    int errCode = 0;

    printf("Sudoku Solver v1.0\n");

    if (argc == 2)
    {
        Sudoku* puzzle = readSudoku(argv[1]);
        
        printSudoku(puzzle);
        solveSudoku(puzzle);
        printf("\nSudoku solved:\n");
        printSudoku(puzzle);
        destroySudoku(puzzle);
    }
    else
    {
        printf("Incorrect number of arguments. Correct usage: %s <source file>.\n", argv[0]);
        errCode = 1;
    } 

    return errCode;
}

Sudoku* readSudoku(char* filename)
{
    Sudoku* newPuzzle = createSudoku();
    
    newPuzzle->cells[0][0]->value = 1;
    newPuzzle->cells[0][3]->value = 9;
    newPuzzle->cells[0][5]->value = 4;
    newPuzzle->cells[0][7]->value = 3;
    newPuzzle->cells[0][8]->value = 7;
    newPuzzle->cells[1][2]->value = 7;
    newPuzzle->cells[1][3]->value = 5;
    newPuzzle->cells[1][5]->value = 1;
    newPuzzle->cells[1][6]->value = 2;
    newPuzzle->cells[1][8]->value = 4;
    newPuzzle->cells[2][4]->value = 3;
    newPuzzle->cells[2][7]->value = 5;
    newPuzzle->cells[3][0]->value = 7;
    newPuzzle->cells[3][7]->value = 6;
    newPuzzle->cells[3][8]->value = 5;
    newPuzzle->cells[4][2]->value = 1;
    newPuzzle->cells[4][3]->value = 2;
    newPuzzle->cells[4][5]->value = 6;
    newPuzzle->cells[4][6]->value = 8;
    newPuzzle->cells[5][0]->value = 3;
    newPuzzle->cells[5][1]->value = 9;
    newPuzzle->cells[5][8]->value = 2;
    newPuzzle->cells[6][1]->value = 7;
    newPuzzle->cells[6][4]->value = 2;
    newPuzzle->cells[7][0]->value = 6;
    newPuzzle->cells[7][2]->value = 9;
    newPuzzle->cells[7][3]->value = 3;
    newPuzzle->cells[7][5]->value = 5;
    newPuzzle->cells[7][6]->value = 7;
    newPuzzle->cells[8][0]->value = 2;
    newPuzzle->cells[8][1]->value = 5;
    newPuzzle->cells[8][3]->value = 1;
    newPuzzle->cells[8][5]->value = 8;
    newPuzzle->cells[8][8]->value = 6;

    return newPuzzle;
}