CFLAGS=-O3 -Wall -fopenmp -Wno-unused-but-set-variable -Wno-unused-result
CC=gcc
RM=rm -f
EXEC=himeno

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(CFLAGS) $(EXEC).o -o $(EXEC)

run:
	@./$(EXEC) < himeno.in

run10: clean all
	@for i in `seq 1 10`; do ./$(EXEC) < himeno.in; done

clean:
	@$(RM) $(EXEC).o $(EXEC)
