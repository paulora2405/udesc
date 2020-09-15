%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	long int ival;
	float fval;
	int bool;
	char *str;
}

/* Declaração dos tokens... */

%token<ival> T_INT
%token<fval> T_REAL


%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_DIVIDE_INT T_EXPOENT
%token T_ATRIBUICAO T_EQUALS T_NOTEQUALS T_MENOR_QUE T_MAIOR_QUE T_MENOR_IGUAL_QUE T_MAIOR_IGUAL_QUE 
%token T_PONTO_VIRGULA T_DOIS_PONTOS T_VIRGULA  
%token T_PRINT T_READ T_FOR T_IF T_ELSE T_MAIN T_WHILE T_DO T_RETURN
%token T_TRUE T_FALSE T_COL_ESQ T_COL_DIR T_CHA_ESQ T_CHA_DIR T_PAR_ESQ T_PAR_DIR 
%token T_COMENTARIO
%token T_IDENT T_TEXT T_ASPAS
%token T_TIPO_INT T_TIPO_REAL T_TIPO_BOOL
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_DIVIDE_INT 
%left T_EXPOENT
%left T_AND
%left T_OR

%nonassoc THEN
%nonassoc THEN_MULTILINE
%nonassoc T_ELSE

/*%type<ival> expr*/
/*%type<fval> mixed_expr*/

%start algoritmo

%%

algoritmo: var_global funcao_main outras_funcoes {printf("Variaveis Globais; Funcao main; Outras funcoes\n");}
	| var_global funcao_main {printf("Variaveis Globais; Funcao main\n");}
	| funcao_main outras_funcoes {printf("Funcao main; Outras funcoes\n");}
	| funcao_main {printf("Funcao main\n");}
	;

var_global: var_global init_vars
	| init_vars
	;

outras_funcoes: outras_funcoes funcao
	| funcao
	;

funcao: tipo_var nome_func T_PAR_ESQ argumentos T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR
	;

argumentos: tipo_var valor
	| tipo_var valor T_VIRGULA argumentos
	;

funcao_main: tipo_var T_MAIN T_PAR_ESQ T_PAR_DIR T_CHA_ESQ codigo T_CHA_DIR
	;

codigo: codigo linha
	| linha
	;

linha: variaveis
	| lacos
	| io
	| condicional
	;

condicional: ifelse
	| if
	;

ifelse: T_IF T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR T_ELSE T_CHA_ESQ codigo T_CHA_DIR
	| T_IF T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS linha T_ELSE linha
	| T_IF T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS linha T_ELSE T_CHA_ESQ codigo T_CHA_DIR
	| T_IF T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR T_ELSE linha
	;

if: T_IF T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR %prec THEN_MULTILINE
	| T_IF T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS linha %prec THEN
	;

io: read
	| print
	;

read: T_READ nome_var T_PONTO_VIRGULA
	;

print: T_PRINT print2 T_PONTO_VIRGULA
	;

print2: print2 T_ASPAS T_TEXT T_ASPAS
	| print2 nome_var
	| T_ASPAS T_TEXT T_ASPAS
	| nome_var
	;

lacos: do
	| while
	| for
	;

do: T_DO T_CHA_ESQ codigo T_CHA_DIR T_WHILE T_PAR_ESQ condicao T_PAR_DIR T_PONTO_VIRGULA
	;

while: T_WHILE T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR T_PONTO_VIRGULA 
	| T_WHILE T_PAR_ESQ condicao T_PAR_DIR T_DOIS_PONTOS linha T_PONTO_VIRGULA
	;

for: T_FOR T_PAR_ESQ nome_var T_DOIS_PONTOS valor T_VIRGULA valor T_VIRGULA valor T_PAR_DIR 
		T_DOIS_PONTOS T_CHA_ESQ codigo T_CHA_DIR T_PONTO_VIRGULA 
	| T_FOR T_PAR_ESQ nome_var T_DOIS_PONTOS valor T_VIRGULA valor T_VIRGULA valor T_PAR_DIR T_DOIS_PONTOS 
		linha T_PONTO_VIRGULA
	;

condicao: condicao T_OR condicao
	| condicao T_AND condicao
	| expr_cond
	;

expr_cond: expressao op_logico expressao
	;

op_logico: T_ATRIBUICAO
	| T_EQUALS
	| T_NOTEQUALS
	| T_MAIOR_QUE
	| T_MENOR_QUE
	| T_MAIOR_IGUAL_QUE
	| T_MENOR_IGUAL_QUE
	;

variaveis: init_vars
	| atribuir_var
	;

atribuir_var: nome_var T_ATRIBUICAO expressao T_PONTO_VIRGULA
	;

init_vars: tipo_var nome_var T_ATRIBUICAO expressao T_PONTO_VIRGULA {printf("Var com atribuicao\n");}
	| tipo_var nome_var T_PONTO_VIRGULA {printf("Var\n");}
	;

expressao: term T_PLUS expressao
	| term T_MINUS expressao
	| term
	;

term: factor T_MULTIPLY term
	| factor T_DIVIDE term
	| factor
	;

factor: expo T_EXPOENT factor
	| expo
	;

expo: T_PAR_ESQ expressao T_PAR_DIR
	| valor
	| chamada_func
	;

chamada_func: nome_func T_PAR_ESQ parametros T_PAR_DIR
	| nome_func T_PAR_ESQ T_PAR_DIR
	;

parametros: valor
	| valor T_VIRGULA parametros
	;

tipo_var: T_TIPO_BOOL
	| T_TIPO_INT
	| T_TIPO_REAL
	;

valor: valor_inteiro
	| valor_float
	;

valor_inteiro: T_INT
	;

valor_float: T_REAL
	;

nome_var: T_IDENT
	;

nome_func: T_IDENT
	;

%%

int main() {
	yyin = stdin;

	do {
		yyparse();
		
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Erro de análise (sintática): %s\n", s);
	exit(1);
}
