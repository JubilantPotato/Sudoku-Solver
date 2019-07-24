#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "cell.h"
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

void printSudoku(Sudoku* puzzle)
{
    int ii, jj;
    
    printf("+---+---+---+---+---+---+---+---+---+\n|");
    
    for (ii = 0; ii < 9; ii++)
    {
        for (jj = 0; jj < 9; jj++)
        {
            int val = puzzle->cells[ii][jj]->value;

            if (val >= 1 && val <= 9)
            {
                printf(" %d ", val);
            }
            else
            {
                printf("   ");
            }
            if ((jj+1) % 3 == 0) printf("|"); 
            else printf(" ");
            
        }
        
        if ((ii+1) % 3 == 0) printf("\n+---+---+---+---+---+---+---+---+---+\n");
        else printf("\n+   .   .   +   .   .   +   .   .   +\n");

        if (ii != 8) { printf("|"); }
    }
    
}

void solveSudoku(Sudoku* puzzle)
{
    int cellsUpdated;

    do 
    {
        int ii, jj;
        cellsUpdated = FALSE;

        for (ii = 0; ii < 9; ii++)
        {
            for (jj = 0; jj < 9; jj++)
            { 
                Cell* currCell = puzzle->cells[ii][jj];
                
                if (currCell->value == -1) /*Cell isn't set*/
                {
                    if (updateCellVertical(puzzle, ii, jj))   cellsUpdated = TRUE;
                    if (updateCellHorizontal(puzzle, ii, jj)) cellsUpdated = TRUE;
                    if (updateCellSubgrid(puzzle, ii, jj))    cellsUpdated = TRUE;

                    if (currCell->numPossibles == 1)
                    {
                        int kk;

                        for (kk = 0; kk < 9; kk++)
                        {
                            if (currCell->possibles[kk] == TRUE) break;
                        }

                        currCell->value = kk + 1;
                    }
                }
            }
        }
    } while (cellsUpdated);
}

int updateCellVertical(Sudoku* puzzle, int x, int y)
{
    int ii, isUpdated = FALSE;
    Cell* cell = puzzle->cells[x][y];

    for (ii = 0; ii < 9; ii++)
    {
        Cell* currCell = puzzle->cells[ii][y];

        if (currCell->value != -1)
        {
            updatePossible(cell, currCell->value, FALSE);
            isUpdated = TRUE;
        }
    }

    return isUpdated;
}

int updateCellHorizontal(Sudoku* puzzle, int x, int y)
{
    int ii, isUpdated = FALSE;
    Cell* cell = puzzle->cells[x][y];

    for (ii = 0; ii < 9; ii++)
    {
        Cell* currCell = puzzle->cells[x][ii];

        if (currCell->value != -1)
        {
            updatePossible(cell, currCell->value, FALSE);
            isUpdated = TRUE;
        }
    }

    return isUpdated;
}

int updateCellSubgrid(Sudoku* puzzle, int x, int y)
{
    int ii, jj, isUpdated = FALSE, xOffset = x / 3, yOffset = y / 3;
    Cell* cell = puzzle->cells[x][y];

    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 3; jj++)
        {
            Cell* currCell = puzzle->cells[ii + xOffset*3][jj + yOffset*3];
            
            if (currCell->value != -1)
            {
                updatePossible(cell, currCell->value, FALSE);
                isUpdated = TRUE;
            }
        }
    }

    return isUpdated;
}

Sudoku* readSudoku(char* filename)
{
    Sudoku* newPuzzle = createSudoku();
    FILE* file = fopen(filename, "r");

    while(fscanf())

    fclose(file);

    return newPuzzle;
}