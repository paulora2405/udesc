projeto=trab

all: $(projeto)

$(projeto): compiladoBizon compiladoFlex
	gcc $(projeto).tab.c lex.yy.c -o $(projeto) -lm

compiladoBizon:
	bison -d $(projeto).y -g --verbose
compiladoFlex:
	flex $(projeto).lex

graphViz:
	dot -Tpdf $(projeto).dot -o $(projeto).pdf -v

compiladoC:
	gcc lex.yy.c -o $(projeto) -lfl

clean:
	rm lex.yy.c $(projeto) $(projeto).dot $(projeto).tab.c $(projeto).tab.h 
	##--$(projeto).pdf

run:
	./$(projeto)

runF:
	./$(projeto) < main.tfk


