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

/*
let counter = 0;

for (let ii = 0; ii < 9; ii++)
{
    let str = "";
    for (let jj = 0; jj < 9; jj++)
    {
        str += (counter<10?" ":"") + counter + " ";
        // str += ((counter%9)<10?" ":"") + counter%9 + " ";
        // str += (Math.floor(counter/9)<10?" ":"") + Math.floor(counter/9) + " ";
		counter++;
    }
    console.log(str);
}

     0  1  2  3  4  5  6  7  8
     9 10 11 12 13 14 15 16 17
    18 19 20 21 22 23 24 25 26
    27 28 29 30 31 32 33 34 35
    36 37 38 39 40 41 42 43 44
    45 46 47 48 49 50 51 52 53
    54 55 56 57 58 59 60 61 62
    63 64 65 66 67 68 69 70 71
    72 73 74 75 76 77 78 79 80
 */

Sudoku* readSudoku(char* filename)
{
    Sudoku* newPuzzle = NULL;
    FILE* file = fopen(filename, "r");

    if (file == NULL || ferror(file)) perror("There was an error opening the file");
    else
    {
        int counter = 0;

        char currChar = ' ';
        int currNum = -1;
        int prevNum = -1;
        newPuzzle = createSudoku();

        while(!feof(file) && counter < 81)
        {
            if (fscanf(file, "%d", &currNum))
            {
                currChar = fgetc(file);
                if (currChar == '?') counter += currNum;
                else if (currChar == ',') 
                {
                    newPuzzle->cells[(counter) / 9][(counter) % 9]->value = currNum;
                    counter++;
                }
                else prevNum = currNum; 

                currNum = -1;
            }
            else
            {
                currChar = fgetc(file);
                if (currChar == '?') /* Previous char was ?*/
                {
                    if (prevNum == -1) counter++;
                    else
                    {
                        counter += prevNum;
                        prevNum = -1;
                    }
                } 
                else if (currChar == ',')
                {
                    if (prevNum != -1)
                    {
                        newPuzzle->cells[(counter) / 9][(counter) % 9]->value = prevNum;
                        counter++;
                        prevNum = -1;
                    }
                }
            }
        }
    } 

    fclose(file);

    return newPuzzle;
}