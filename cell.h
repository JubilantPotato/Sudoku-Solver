#include "linked_list.h"

typedef struct
{
    int value;
    LinkedList* possibles;
} Cell;

Cell* createCell();
void removeCell(Cell* delCell);
