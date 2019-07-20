#include <stdlib.h>
#include "sudoku.h"

Sudoku* createSudoku()
{
    Sudoku* newSudoku = (Sudoku*)malloc(sizeof(Sudoku));
    int ii, jj;

    newSudoku->cells = (Cell***)malloc(9 * sizeof(Cell**));
    
    for (ii = 0; ii < 9; ii++)
    {
        newSudoku->cells[ii] = (Cell**)malloc(9 * sizeof(Cell*));
        
        for (jj = 0; jj < 9; jj++)
        {
            newSudoku->cells[ii][jj] = createCell();
        }
    }

    return newSudoku;
}

void destroySudoku(Sudoku* delSudoku)
{
    int ii, jj;
    
    for (ii = 0; ii < 9; ii++)
    {
        for (jj = 0; jj < 9; jj++)
        {
            removeCell(delSudoku->cells[ii][jj]);
        }
        
        free(delSudoku->cells[ii]);
    }

    free(delSudoku->cells);
    
    free(delSudoku);
}
