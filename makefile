CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
EXECUTABLE = math_matrix

all : $(EXECUTABLE)

$(EXECUTABLE) : math_matrix.o functions.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) math_matrix.c 

math_matrix.o : math_matrix.c functions.h
	$(CC) $(CFLAGS) -c math_matrix.c 

functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean :
	rm -f $(EXECUTABLE)
	rm -f math_matrix.o
	rm -f functions.o
