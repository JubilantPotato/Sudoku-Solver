#include "cell.h"

typedef struct
{
    Cell*** cells;
    int numFound;
} Sudoku;

Sudoku* createSudoku();
void destroySudoku(Sudoku* delSudoku);


