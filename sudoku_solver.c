#include <stdio.h>
#include <stdlib.h>
#include "sudoku_solver.h"

int main(int argc, char** argv)
{
    int errCode = 0;

    printf("Welcome to Sudoku Solver v1.0. By Tristan Lynass.\n\n");

    if (argc == 2)
    {
        Sudoku* puzzle = readSudoku(argv[1]);
        /* ASSERTION: puzzle will be a valid Sudoku*, with only values 1 - 9 and empty linked-lists */
        
        /* 0 = success, 1 = invalid */
        /*int result = solveSudoku(puzzle);*/
        int result = TRUE;
        if (result == TRUE)
        {
            printf("Sudoku solved:\n");
            printSudoku(puzzle);
        }
        else
        {
            printf("Could not solve sudoku.\n");
        }
        generatePossibilities(puzzle); 
        printSudoku(puzzle);
        destroySudoku(puzzle);
    }
    else
    {
        printf("Incorrect number of arguments. Correct usage: %s <source file>.\n", argv[0]);
        errCode = 1;
    }

    printf("Exiting.\n");

    return errCode;
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
            printf("|");
        }
        
        printf("\n+---+---+---+---+---+---+---+---+---+\n");

        if (ii != 8) { printf("|"); }
    }
    
}
Sudoku* readSudoku(char* filename)
{
    Sudoku* newPuzzle = createSudoku();
    
    newPuzzle->cells[0][0]->value = 1;
    newPuzzle->cells[0][3]->value = 9;
    newPuzzle->cells[0][5]->value = 4;
    newPuzzle->cells[0][7]->value = 3;
    newPuzzle->cells[0][8]->value = 7;
    newPuzzle->cells[1][2]->value = 7;
    newPuzzle->cells[1][3]->value = 5;
    newPuzzle->cells[1][5]->value = 1;
    newPuzzle->cells[1][6]->value = 2;
    newPuzzle->cells[1][8]->value = 4;
    newPuzzle->cells[2][4]->value = 3;
    newPuzzle->cells[2][7]->value = 5;
    newPuzzle->cells[3][0]->value = 7;
    newPuzzle->cells[3][7]->value = 6;
    newPuzzle->cells[3][8]->value = 5;
    newPuzzle->cells[4][2]->value = 1;
    newPuzzle->cells[4][3]->value = 2;
    newPuzzle->cells[4][5]->value = 6;
    newPuzzle->cells[4][6]->value = 8;
    newPuzzle->cells[5][0]->value = 3;
    newPuzzle->cells[5][1]->value = 9;
    newPuzzle->cells[5][8]->value = 2;
    newPuzzle->cells[6][1]->value = 7;
    newPuzzle->cells[6][4]->value = 2;
    newPuzzle->cells[7][0]->value = 6;
    newPuzzle->cells[7][2]->value = 9;
    newPuzzle->cells[7][3]->value = 3;
    newPuzzle->cells[7][5]->value = 5;
    newPuzzle->cells[7][6]->value = 7;
    newPuzzle->cells[8][0]->value = 2;
    newPuzzle->cells[8][1]->value = 5;
    newPuzzle->cells[8][3]->value = 1;
    newPuzzle->cells[8][5]->value = 8;
    newPuzzle->cells[8][8]->value = 6;

    return newPuzzle;
}

int solveSudoku(Sudoku* puzzle)
{
    int result = FALSE; /* Stores whether or not the puzzle has been solved so far */
    int keepGoing = TRUE;
    
    generatePossibilities(puzzle); /* Populate the Cell linked list 
                                 with all possibilities for that 
                                 cell. If there's only one
                                 possibility, the function will 
                                 assign that number to the cell. */
    
    /* Check to see if the initial pass solved it trivially */
    /*if (isSolved(puzzle))
    {
        result = TRUE;
    }*/

    /* So long as it's not solved, keep attempting to solve it  */
    while (keepGoing && !result)
    {
        keepGoing = FALSE;

    }

    return result;
}

/*
 * 1. Check to see if it's the only empty cell in its quad
 * 2. Check for uniquness in its own quad
 * 3. Check for uniqueness horiz
 * 4. Check for uniqueness vert
 */
/* Check to see if cell can be given a value */
/*int checkCell(Sudoku* puzzle, int x, int y)
{
    int valueFound = checkSubGrid(puzzle, x, y);

    if (valueFound == FALSE)
}*/

/*
 * IMPORTS:
 *  + puzzle (Sudoku*) - Pointer to new sudoku puzzle we need to generate possibilities for
 * PURPOSE:
 *  Populates the Cell struct's linked list with all possibilities for that cell in the puzzle. If there is only one possibility, the function will assign that number to the cell
 *  WRITTEN: NO
 *  TESTED: NO
 *  DOCUMENTED: NO
 */
void generatePossibilities(Sudoku* puzzle)
{
    int ii, jj, numFound;
    Cell* c;
    LinkedListNode* nextNode = NULL;
	numFound = 0;
	
    for (ii = 0; ii < 9; ii++)
    {
        for (jj = 0; jj < 9; jj++)
        { 
            c = puzzle->cells[ii][jj];
            
			/* Only test cells that have not yet been solved */
            if (c->value == -1)
            {
				/* Each of these arrays store a boolean, that 
				*  represents whether the number k, at index k - 1 
				*  is present in the row, column or subgrid
				*/
                int* gridNums = getNumbersInSubgrid(puzzle, ii, jj);
                int* rowNums = getNumbersInRow(puzzle, ii, jj);
                int* colNums = getNumbersInColumn(puzzle, ii, jj);
                int kk;
            
                for (kk = 0; kk < 9; kk++)
                {
					/* By checking to see if k is TRUE in any of these cases
					*  we only enter the if (ie. insert the number) when the number
					*  itself does not appear in the row, column or subgrid
					*/
                    if (!gridNums[kk] && !rowNums[kk] && !colNums[kk])
                    {
                        int foundDupe = FALSE;
						nextNode = c->possibles->head;
						
						while (nextNode != NULL && !foundDupe)
						{
							if (kk + 1 == nextNode->data)
							{
								foundDupe = TRUE;
							}
							
							nextNode = nextNode->next;
						}
						
						if (!foundDupe)
						{
							insertLast(c->possibles, kk + 1);
						}
                    }
                }
                free(gridNums);
                free(rowNums);
                free(colNums);
				
				/* If there is only one possibility, make that the cell's value */
                if (c->possibles->size == 1)
                {
                    int num = removeFirst(c->possibles);
                    c->value = num;
					numFound++;
                }
            }
        }
    }
	/* ??? */
	/*
    for (ii = 0; ii < 9; ii++)
    {
        c = puzzle->cells[1][ii];
        printf("%d: ", c->value);
        nextNode = c->possibles->head;

        while (nextNode != NULL)
        {
            printf("%d, ", nextNode->data);
            nextNode = nextNode->next;
        }

        printf("\n");
    }
	*/
	printf("Num found in first pass using generatePossibilities(): %d\n", numFound);
}   

int* getNumbersInSubgrid (Sudoku* puzzle, int x, int y)
{
    int* numbers = (int*)malloc(9 * sizeof(int));
    int* coords = getQuadrant(x, y);
    int ii, jj;

    for (ii = 0; ii < 9; ii++)
    {
        numbers[ii] = FALSE;
    }
    
    for (ii = 0; ii < 2; ii++)
    {
        for (jj = 0; jj < 2; jj++)
        {
            int realX = coords[0] * 3 + ii;
            int realY = coords[1] * 3 + jj;
            int cellNum = puzzle->cells[realX][realY]->value;
            if (cellNum != -1)
            {
                numbers[cellNum - 1] = TRUE;
            }
        }
    }
    free(coords);

    return numbers;
}

int* getNumbersInRow(Sudoku* puzzle, int x, int y)
{
    int* numbers = (int*)malloc(9 * sizeof(int));
    int ii;
    
    for (ii = 0; ii < 9; ii++)
    {
        numbers[ii] = FALSE;
    }
    
    ii = x;
    wrapIncrement(&ii, 0, 8);

    while (ii != x)
    {
        int cellNum = puzzle->cells[ii][y]->value;

        if (cellNum != -1)
        {
            numbers[cellNum - 1] = TRUE;
        }

        wrapIncrement(&ii, 0, 8);
    }

    return numbers;
}

int* getNumbersInColumn(Sudoku* puzzle, int x, int y)
{
    int* numbers = (int*)malloc(9 * sizeof(int));
    int jj;
    
    for (jj = 0; jj < 9; jj++)
    {
        numbers[jj] = FALSE;
    }

    jj = y;
    wrapIncrement(&jj, 0, 8);

    while (jj != y)
    {
        int cellNum = puzzle->cells[x][jj]->value;

        if (cellNum != -1)
        {
            numbers[cellNum - 1] = TRUE;
        }

        wrapIncrement(&jj, 0, 8);
    }

    return numbers;
}
/* When num reaches max, it gets wrapped back around to equal retVal, keeping it within those bounds */
void wrapIncrement(int* num, int retVal, int max)
{
    (*num)++;
    if (*num > max)
    {
        *num = retVal;
    }
}
/*
 * IMPORTS:
 *  + puzzle (Sudoku*) - Pointer to sudoku puzzle we're trying to solve
 *  + x (int) - Row of subgrid we're checking
 *  + y (int) - Column of subgrid we're checking
 * PURPOSE:
 *  Checks the 3x3 subgrid containing the coordinates of x and y for new values 
 * STATUS:
 *  Not finished
 */
/*int checkSubGrid(Sudoku* puzzle, int x, int y)
{
    int[2] coords = getQuadrant(&x, &y);
    int foundNegs = FALSE;

*/   /* Stores all values in the 3x3 square that aren't the one we're inspecting */
  /*  int[8] valuesFound; *//* If this contains one or more -1's then we can't use it */

    /* If exactly one of these is FALSE, then the (index+1) of that FALSE value will be
      the value which fits into our cell at (x, y) */
   /* int[9] possibles = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
    int ii, jj, kk = 0;

    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 3; jj++)
        {
            if (ii != x && jj != y)
            {
                int actualX = coords[0] * 3 + ii;
                int actualY = coords[1] * 3 + jj;
                Cell* currCell = puzzle->cells[actualX][actualY];
                
                valuesFound[kk] = currCell->value;
                kk++;

                LinkedListNode* nextNode = currCell->possibles->head;

                while (nextnode != NULL)
                {
                    possibles[nextNode->data - 1] = TRUE;
                }
            }
        }
    }
    
    ii = 0;
    foundNegs = FALSE;
    while (!foundNegs && ii < 8)
    {
        if (valuesFound[ii] == -1)
        {
            foundNegs = TRUE;
        }
    }
    
    if (!foundNegs)
    {
        int nextPossible = 1;
        int found = FALSE;
        ii = 0;

        while (!found && nextPossible <= 9)
        {   
            while (!foundInValues && ii < 8)
            {
                if (nextPossible == valuesFound[ii])
                {
                    foundInValues = TRUE;
                }
                else
                {
                    ii++;
                }
            }

            if (!foundInValues)
            {
                found = TRUE;
            }
            else
            {
                nextPossible++;
            }
        }

        if (found)
        {
 */           /* If we get here then nextPossible is the correct answer */
   /*     
        }
}
*/
/* Get the coordinates of the primary cell/quadrant the cell is in
 * and reduce the cell coords to the primary ones */
int* getQuadrant(int x, int y)
{
    int* coords = (int*)malloc(2 * sizeof(int));
    coords[0] = 0;
    coords[1] = 0;


    while (x > 2)
    {
        x -= 3;
        coords[0]++;
    }

    while (y > 2)
    {
        y -= 3;
        coords[1]++;
    }

    return coords;
}
