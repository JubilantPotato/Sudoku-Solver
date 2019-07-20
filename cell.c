#include <stdlib.h>
#include "cell.h"

Cell* createCell()
{
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    newCell->value = -1;
    newCell->possibles = createList();

    return newCell;
}

void removeCell(Cell* delCell)
{
    destroyList(delCell->possibles);
    free(delCell);
}
