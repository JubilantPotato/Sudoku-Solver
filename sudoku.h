typedef struct
{
    Cell*** cells;
    int numFound;
} Sudoku;

Sudoku* createSudoku();
void destroySudoku(Sudoku* delSudoku);
void printSudoku(Sudoku* puzzle);
void solveSudoku(Sudoku* puzzle);
int updateCellVertical(Sudoku* puzzle, int x, int y);
int updateCellHorizontal(Sudoku* puzzle, int x, int y);
int updateCellSubgrid(Sudoku* puzzle, int x, int y);
Sudoku* readSudoku(char* filename);