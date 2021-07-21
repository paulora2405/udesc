CFLAGS=-O3 -Wall -fopenmp
CC=gcc
RM=rm -f
EXEC=quick

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(CFLAGS) $(EXEC).o -o $(EXEC).out

clean:
	@$(RM) $(EXEC).o $(EXEC)
