#include <stdlib.h>
#include "util.h"
#include "cell.h"

Cell* createCell()
{
    int ii;
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    newCell->value = -1;
    /*newCell->possibles = {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};*/
    newCell->numPossibles = 9;
    
    newCell->possibles = (int*)malloc(sizeof(9*sizeof(int))); /*createList();*/
    
    for (ii = 0; ii < 9; ii++)
    {
        newCell->possibles[ii] = TRUE;
    }

    return newCell;
}

void removeCell(Cell* delCell)
{
    /*destroyList(delCell->possibles);*/
    free(delCell);
}

void updatePossible(Cell* cell, int number, int isPossible)
{
    if (cell->possibles[number - 1] != isPossible)
    {
        if (isPossible == TRUE) cell->numPossibles++;
        else cell->numPossibles--;
        
        cell->possibles[number - 1] = isPossible;
    }
}