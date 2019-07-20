#include "sudoku.h"

void printSudoku(Sudoku* puzzle);
Sudoku* readSudoku(char* filename);
int isSolved(Sudoku* puzzle);
void generatePossibilities(Sudoku* puzzle);
int* getNumbersInSubgrid(Sudoku* puzzle, int x, int y);
int* getNumbersInRow(Sudoku* puzzle, int x, int y);
int* getNumbersInColumn(Sudoku* puzzle, int x, int y);
void updatePossible(Sudoku* puzzle, int x, int y);
int solveSudoku(Sudoku* puzzle);
int* getQuadrant(int x, int y);
void wrapIncrement(int* num, int retVal, int max);
