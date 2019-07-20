CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = sudoku_solver.o linked_list.o cell.o sudoku.o
EXEC = sudoku_solver


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

sudoku_solver.o : sudoku_solver.c sudoku_solver.h sudoku.h
	$(CC) $(CFLAGS) -c sudoku_solver.c

sudoku.o : sudoku.c sudoku.h cell.h
	$(CC) $(CFLAGS) -c sudoku.c

cell.o : cell.c cell.h linked_list.h
	$(CC) $(CFLAGS) -c cell.c

linked_list.o : linked_list.c linked_list.h util.h
	$(CC) $(CFLAGS) -c linked_list.c

clean:
	rm -f $(EXEC) $(OBJ)
