parametrosCompilacao=-Wall -lm -pthread

all: questao2 

questao2: questao2.o 
	gcc -o questao2 questao2.o $(parametrosCompilacao)

questao2.o: questao2.c
	gcc -c questao2.c $(parametrosCompilacao)

clean:
	rm *.o questao2
