CFLAGS=-O3 -Wall -fopenmp
CC=gcc
RM=rm -f
EXEC=quick2
VECSIZE=20000000

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(CFLAGS) $(EXEC).o -o $(EXEC).out

run:
	@./$(EXEC).out $(VECSIZE)

run10:
	@for i in `seq 1 10`; do ./$(EXEC).out $(VECSIZE); done

clean:
	@$(RM) $(EXEC).o $(EXEC)
