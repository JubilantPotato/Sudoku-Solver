typedef struct
{
    int value;
    int possibles [9];
    int numPossibles;
} Cell;

Cell* createCell();
void removeCell(Cell* delCell);
void updatePossible(Cell* cell, int number, int isPossible);
