CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = sudoku_solver.o cell.o sudoku.o
EXEC = sudoku_solver

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

sudoku_solver.o : sudoku_solver.c sudoku.h cell.h
	$(CC) $(CFLAGS) -c sudoku_solver.c

sudoku.o : sudoku.c sudoku.h cell.h util.h
	$(CC) $(CFLAGS) -c sudoku.c

cell.o : cell.c cell.h util.h
	$(CC) $(CFLAGS) -c cell.c

clean:
	rm -f $(EXEC) $(OBJ)
